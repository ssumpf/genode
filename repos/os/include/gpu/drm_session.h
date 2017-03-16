#ifndef _INCLUDE__GPU__DRM_SESSION_H_
#define _INCLUDE__GPU__DRM_SESSION_H_

#include <os/packet_stream.h>
#include <packet_stream_tx/packet_stream_tx.h>
#include <session/session.h>

namespace Drm {
	class Packet_descriptor;
	class Session;
}

int lx_ioctl(int request, void *arg);

class Drm::Packet_descriptor : public Genode::Packet_descriptor
{
	private:

		unsigned long _request = 0;
		int           _error   = 0;

	public:

		Packet_descriptor(Genode::off_t offset= 0, Genode::size_t size = 0)
		:
			Genode::Packet_descriptor(offset, size) { }

		Packet_descriptor(Packet_descriptor p, unsigned long request)
		:
			Genode::Packet_descriptor(p.offset(), p.size()), _request(request) { }

		int  error() const { return _error; }
		int  request() const { return _request; }

		void error(int error_code) { _error = error_code; }
};

class Drm::Session : public Genode::Session
{
	protected:

		enum { TX_QUEUE_SIZE = 16 };

		using Tx_policy = Genode::Packet_stream_policy<Drm::Packet_descriptor,
	                                                 TX_QUEUE_SIZE, TX_QUEUE_SIZE,
	                                                 char>;
	public:

		using Tx = Packet_stream_tx::Channel<Tx_policy>;

		virtual ~Session() { }

		/**
		 * Request packet-transmission channel
		 */
		virtual Tx *tx_channel() { return 0; }

		/**
		 * Request client-side packet-stream interface of tx channel
		 */
		virtual Tx::Source *tx() { return 0; }

		static const char *service_name() { return "Drm"; }

		GENODE_RPC(Rpc_tx_cap, Genode::Capability<Tx>, _tx_cap);
		GENODE_RPC_INTERFACE(Rpc_tx_cap);
};

#endif /* _INCLUDE__GPU__DRM_SESSION_H_ */
