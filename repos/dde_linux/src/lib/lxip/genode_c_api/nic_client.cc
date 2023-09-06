/*
 * \brief  C interface to Genode's nic_client session
 * \author Norman Feske
 * \date   2021-07-06
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/registry.h>
#include <base/log.h>
#include <base/session_label.h>
#include <nic_session/connection.h>
#include <nic/packet_allocator.h>
#include <genode_c_api/nic_client.h>

using namespace Genode;

static Env                                *_env_ptr;
static Allocator                          *_alloc_ptr;
static Signal_context_capability           _sigh { };
static Registry<Registered<genode_nic_client>> _nic_clients { };


struct genode_nic_client : private Noncopyable, private Interface
{
	private:

		Env       &_env;
		Allocator &_alloc;

		Nic::Packet_allocator _packet_alloc { &_alloc };

		static constexpr size_t
			PACKET_SIZE = Nic::Packet_allocator::DEFAULT_PACKET_SIZE,
			BUF_SIZE    = Nic::Session::QUEUE_SIZE * PACKET_SIZE;

		Session_label const _session_label;

		Nic::Connection _connection { _env, &_packet_alloc,
		                              BUF_SIZE, BUF_SIZE,
		                              _session_label.string() };

	public:

		genode_nic_client(Env &env, Allocator &alloc, Signal_context_capability sigh,
		              Session_label    const &session_label)
		:
			_env(env), _alloc(alloc),
			_session_label(session_label)
		{
			_connection.rx_channel()->sigh_ready_to_ack   (sigh);
			_connection.rx_channel()->sigh_packet_avail   (sigh);
			_connection.tx_channel()->sigh_ack_avail      (sigh);
			_connection.tx_channel()->sigh_ready_to_submit(sigh);

			///* trigger signal handling once after construction */
			//Signal_transmitter(sigh).submit();
		}

		void notify_peer()
		{
			_connection.rx()->wakeup();
			_connection.tx()->wakeup();
		}

		template <typename FN>
		bool tx_one_packet(FN const &fn)
		{
			bool progress = false;

			Nic::Session::Tx::Source &tx_source = *_connection.tx();

			/*
			 * Process acknowledgements
			 */

			while (tx_source.ack_avail()) {
				tx_source.release_packet(tx_source.try_get_acked_packet());
				progress = true;
			}

			/*
			 * Submit packet
			 */

			if (!tx_source.ready_to_submit(1))
				return progress;

			typedef Nic::Packet_descriptor Packet_descriptor;

			Packet_descriptor packet { };
			size_t const max_bytes = Nic::Packet_allocator::OFFSET_PACKET_SIZE;


			tx_source.alloc_packet_attempt(max_bytes).with_result(
				[&] (Packet_descriptor packet)
				{
					char * const dst_ptr = tx_source.packet_content(packet);
					size_t const payload_bytes = min(max_bytes, fn(dst_ptr, max_bytes));

					/* imprint payload size into packet descriptor */
					packet = Packet_descriptor(packet.offset(), payload_bytes);

					tx_source.try_submit_packet(packet);
					progress = true;
				},
				[] (auto) {}
			);

			return progress;
		}

		template <typename FN>
		bool for_each_rx_packet(FN const &fn)
		{
			/*
			 * Implementation mirrored from (commented) block/request_stream.h
			 */
			bool overall_progress = false;

			Nic::Session::Rx::Sink &rx_sink = *_connection.rx();

			for (;;) {

				if (!rx_sink.packet_avail() || !rx_sink.ack_slots_free())
					break;

				typedef Nic::Packet_descriptor Packet_descriptor;

				Packet_descriptor const packet = rx_sink.peek_packet();

				bool const packet_valid = rx_sink.packet_valid(packet)
				                       && (packet.offset() >= 0);

				char const *content = rx_sink.packet_content(packet);

				genode_nic_client_rx_result_t const
					response = packet_valid
					         ? fn(content, packet.size())
					         : GENODE_NIC_CLIENT_RX_REJECTED;

				bool progress = false;

				switch (response) {

				case GENODE_NIC_CLIENT_RX_ACCEPTED:
				case GENODE_NIC_CLIENT_RX_REJECTED:

					(void)rx_sink.try_get_packet();
					rx_sink.try_ack_packet(packet);
					progress = true;
					break;

				case GENODE_NIC_CLIENT_RX_RETRY:
					break;
				}

				if (progress)
					overall_progress = true;

				if (!progress)
					break;
			}
			return overall_progress;
		}
};


void genode_nic_client_init(genode_env            *env_ptr,
                            genode_allocator      *alloc_ptr,
                            genode_signal_handler *sigh_ptr)
{
	_env_ptr   = env_ptr;
	_alloc_ptr = alloc_ptr;
	_sigh      = cap(sigh_ptr);
}


void genode_nic_client_notify_peers()
{
	_nic_clients.for_each([&] (genode_nic_client &nic_client) {
		nic_client.notify_peer(); });
}


bool genode_nic_client_tx_packet(struct genode_nic_client *nic_client_ptr,
                                 genode_nic_client_tx_packet_content_t tx_packet_content_cb,
                                 struct genode_nic_client_tx_packet_context *ctx_ptr)
{
	return nic_client_ptr->tx_one_packet([&] (char *dst, size_t len) {
		return tx_packet_content_cb(ctx_ptr, dst, len); });
}


bool genode_nic_client_rx(struct genode_nic_client *nic_client_ptr,
                          genode_nic_client_rx_one_packet_t rx_one_packet_cb,
                          struct genode_nic_client_rx_context *ctx_ptr)
{
	return nic_client_ptr->for_each_rx_packet([&] (char const *ptr, size_t len) {
		return rx_one_packet_cb(ctx_ptr, ptr, len); });
}


struct genode_nic_client *genode_nic_client_create(char const *label)
{
	if (!_env_ptr || !_alloc_ptr) {
		error("genode_nic_client_create: missing call of genode_nic_client_init");
		return nullptr;
	}

	return new (*_alloc_ptr)
		Registered<genode_nic_client>(_nic_clients, *_env_ptr, *_alloc_ptr, _sigh,
		                              Session_label(label));
}


void genode_nic_client_destroy(struct genode_nic_client *nic_client_ptr)
{
	destroy(*_alloc_ptr, nic_client_ptr);
}
