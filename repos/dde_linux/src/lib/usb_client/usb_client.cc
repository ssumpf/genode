
#include <base/id_space.h>
#include <usb_session/connection.h>
#include <base/heap.h>
#include "usb_client.h"

using namespace Genode;

struct Usb_client;
using Usb_id_space = Id_space<Usb_client>;


struct Usb_client : Usb::Connection
{
	Usb_id_space::Element const elem;

	Usb_client(Env &env, Usb_id_space &space, char const *label,
	           Range_allocator *alloc,
	           Signal_context_capability state_changed)
	: Usb::Connection(env, alloc, label, 512*1024, state_changed),
	  elem(*this, space)
	{ }

	genode_usb_client_handle_t handle() const { return elem.id().value; }
};

static Usb_id_space _usb_space { };

template <typename FUNC>
int usb_client_apply(genode_usb_client_handle_t handle, FUNC const &fn)
{
	Usb_id_space::Id id { .value = handle };
	try {
		_usb_space.apply<Usb_client>(id, fn);
	} catch (Usb_id_space::Id_space::Unknown_id) {
		error("Invalid handle: ", handle);
		return -1;
	}
	return 0;
}


genode_usb_client_handle_t
genode_usb_client_create(struct genode_env             *env,
                         struct genode_allocator       *md_alloc,
                         struct genode_range_allocator *alloc,
                         char const                    *label,
                         struct genode_signal_handler  *handler)
{
	Env             &_env      = *static_cast<Env *>(env);
	Range_allocator *_alloc    = static_cast<Range_allocator*>(alloc);
	Allocator       *_md_alloc = static_cast<Allocator *>(md_alloc);

	Usb_client *client = new (_md_alloc) Usb_client(_env, _usb_space, label,
	                                                _alloc, cap(handler));
	return client->handle();
}


void genode_usb_client_sigh_ack_avail(genode_usb_client_handle_t handle,
                                      struct genode_signal_handler *handler)
{
	usb_client_apply(handle, [&] (Usb_client &usb) {
		usb.tx_channel()->sigh_ack_avail(cap(handler)); });
}


int genode_usb_client_config_descriptor(genode_usb_client_handle_t handle,
                                        genode_usb_device_descriptor *device_descr,
                                        genode_usb_config_descriptor *config_descr)
{
	auto lambda = [&] (Usb_client &usb) {
		Usb::Device_descriptor dev_descr;
		Usb::Config_descriptor conf_descr;
		usb.config_descriptor(&dev_descr, &conf_descr);

		memcpy(device_descr, &dev_descr,    sizeof(*device_descr));
		memcpy(config_descr, &config_descr, sizeof(*config_descr));
	};

	return usb_client_apply(handle, lambda);
}


bool genode_usb_client_plugged(genode_usb_client_handle_t handle)
{
	bool plugged = false;
	usb_client_apply(handle, [&] (Usb_client &usb) {
		plugged = usb.plugged(); });
	
	return plugged;
}
