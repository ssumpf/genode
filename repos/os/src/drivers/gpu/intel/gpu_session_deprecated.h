#ifndef _GPU_SESSION_DEPRECATED_H_
#define _GPU_SESSION_DEPRECATED_H_

#include <gpu_session/gpu_session.h>

namespace Gpu {
	struct Session_deprecated;
}


struct Gpu::Session_deprecated : public Gpu::Session
{
	Gpu::Sequence_number exec_buffer(Buffer_id, Genode::size_t) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return Sequence_number();
	}

	Genode::Dataspace_capability alloc_buffer(Buffer_id, Genode::size_t) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return Genode::Dataspace_capability();
	}

	void free_buffer(Buffer_id) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
	}

	Buffer_capability export_buffer(Buffer_id) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return Buffer_capability();
	}

	void import_buffer(Buffer_capability, Buffer_id) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
	}

	Genode::Dataspace_capability map_buffer(Buffer_id, bool,
	                                        Mapping_attributes) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return Genode::Dataspace_capability();
	}

	void unmap_buffer(Buffer_id) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
	}

	bool map_buffer_ppgtt(Buffer_id, Gpu::addr_t) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return false;
	}

	void unmap_buffer_ppgtt(Buffer_id, Gpu::addr_t) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
	}

	Gpu::addr_t query_buffer_ppgtt(Buffer_id) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return 0;
	}

	bool set_tiling(Buffer_id, unsigned) final
	{
		Genode::error(__PRETTY_FUNCTION__, " deprecated disabled function called");
		return false;
	}
};

#endif /* _GPU_SESSION_DEPRECATED_H_ */
