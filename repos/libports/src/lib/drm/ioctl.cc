extern "C" {
#include <drm.h>
#include <i915_drm.h>
}

#include <base/heap.h>
#include <base/log.h>
#include <base/debug.h>

#include <gpu/connection.h>
#include <drm/serialize.h>

#include <os/backtrace.h>
enum { verbose_ioctl = false };

long driver_nr(long request) { return (request & 0xff) - DRM_COMMAND_BASE; }
constexpr long drm_nr(long request) { return request & 0xff; }
bool driver_ioctl(long request) { return drm_nr(request) >= DRM_COMMAND_BASE && drm_nr(request) < DRM_COMMAND_END; }
/**
 * Return name of DRM command
 */
const char *command_name(long request)
{
	if (IOCGROUP(request) != DRM_IOCTL_BASE)
		return "<non-DRM>";


	if (!driver_ioctl(request)) {
		switch (drm_nr(request)) {
			case drm_nr(DRM_IOCTL_GEM_CLOSE): return "DRM_IOCTL_GEM_CLOSE";
			case drm_nr(DRM_IOCTL_GEM_FLINK): return "DRM_IOCTL_GEM_FLINK";
			default:                          return "<unknown drm>";
		}
	}

	switch (driver_nr(request)) {
	case DRM_I915_INIT:                  return "DRM_I915_INIT";
	case DRM_I915_FLUSH:                 return "DRM_I915_FLUSH";
	case DRM_I915_FLIP:                  return "DRM_I915_FLIP";
	case DRM_I915_BATCHBUFFER:           return "DRM_I915_BATCHBUFFER";
	case DRM_I915_IRQ_EMIT:              return "DRM_I915_IRQ_EMIT";
	case DRM_I915_IRQ_WAIT:              return "DRM_I915_IRQ_WAIT";
	case DRM_I915_GETPARAM:              return "DRM_I915_GETPARAM";
	case DRM_I915_SETPARAM:              return "DRM_I915_SETPARAM";
	case DRM_I915_ALLOC:                 return "DRM_I915_ALLOC";
	case DRM_I915_FREE:                  return "DRM_I915_FREE";
	case DRM_I915_INIT_HEAP:             return "DRM_I915_INIT_HEAP";
	case DRM_I915_CMDBUFFER:             return "DRM_I915_CMDBUFFER";
	case DRM_I915_DESTROY_HEAP:          return "DRM_I915_DESTROY_HEAP";
	case DRM_I915_SET_VBLANK_PIPE:       return "DRM_I915_SET_VBLANK_PIPE";
	case DRM_I915_GET_VBLANK_PIPE:       return "DRM_I915_GET_VBLANK_PIPE";
	case DRM_I915_VBLANK_SWAP:           return "DRM_I915_VBLANK_SWAP";
	case DRM_I915_HWS_ADDR:              return "DRM_I915_HWS_ADDR";
	case DRM_I915_GEM_INIT:              return "DRM_I915_GEM_INIT";
	case DRM_I915_GEM_EXECBUFFER:        return "DRM_I915_GEM_EXECBUFFER";
	case DRM_I915_GEM_PIN:               return "DRM_I915_GEM_PIN";
	case DRM_I915_GEM_UNPIN:             return "DRM_I915_GEM_UNPIN";
	case DRM_I915_GEM_BUSY:              return "DRM_I915_GEM_BUSY";
	case DRM_I915_GEM_THROTTLE:          return "DRM_I915_GEM_THROTTLE";
	case DRM_I915_GEM_ENTERVT:           return "DRM_I915_GEM_ENTERVT";
	case DRM_I915_GEM_LEAVEVT:           return "DRM_I915_GEM_LEAVEVT";
	case DRM_I915_GEM_CREATE:            return "DRM_I915_GEM_CREATE";
	case DRM_I915_GEM_PREAD:             return "DRM_I915_GEM_PREAD";
	case DRM_I915_GEM_PWRITE:            return "DRM_I915_GEM_PWRITE";
	case DRM_I915_GEM_MMAP:              return "DRM_I915_GEM_MMAP";
	case DRM_I915_GEM_SET_DOMAIN:        return "DRM_I915_GEM_SET_DOMAIN";
	case DRM_I915_GEM_SW_FINISH:         return "DRM_I915_GEM_SW_FINISH";
	case DRM_I915_GEM_SET_TILING:        return "DRM_I915_GEM_SET_TILING";
	case DRM_I915_GEM_GET_TILING:        return "DRM_I915_GEM_GET_TILING";
	case DRM_I915_GEM_GET_APERTURE:      return "DRM_I915_GEM_GET_APERTURE";
	case DRM_I915_GEM_MMAP_GTT:          return "DRM_I915_GEM_MMAP_GTT";
	case DRM_I915_GET_PIPE_FROM_CRTC_ID: return "DRM_I915_GET_PIPE_FROM_CRTC_ID";
	case DRM_I915_GEM_MADVISE:           return "DRM_I915_GEM_MADVISE";
	case DRM_I915_OVERLAY_PUT_IMAGE:     return "DRM_I915_OVERLAY_PUT_IMAGE";
	case DRM_I915_OVERLAY_ATTRS:         return "DRM_I915_OVERLAY_ATTRS";
	case DRM_I915_GEM_EXECBUFFER2:       return "DRM_I915_GEM_EXECBUFFER2";
	case DRM_I915_REG_READ:              return "DRM_I915_REG_READ";
	case DRM_I915_GET_RESET_STATS:       return "DRM_I915_GET_RESET_STATS";
	case DRM_I915_GEM_CONTEXT_CREATE:    return "DRM_I915_GEM_CONTEXT_CREATE";
	default:
		Genode::backtrace();
		return "<unknown driver>";
	}
}

static void dump_ioctl(long request)
{
	using namespace Genode;

	log("ioctl(request=", Hex(request),
	    (request & 0xe0000000) == IOC_OUT   ? " out"   :
	    (request & 0xe0000000) == IOC_IN    ? " in"    :
	    (request & 0xe0000000) == IOC_INOUT ? " inout" : " void",
	    " len=", IOCPARM_LEN(request),
	    " cmd=",command_name(request), " (", Hex(drm_nr(request)), ")");
}


class Drm_call
{
	private:

		Genode::Env          &_env;
		Genode::Heap          _heap { _env.ram(), _env.rm() };
		Genode::Allocator_avl _drm_alloc { &_heap };
		Drm::Connection       _drm_session { _env, &_drm_alloc };

		bool _fixup_packet(unsigned long request, void *arg, void *content)
		{
			if (driver_nr(request) == DRM_I915_GEM_EXECBUFFER2) {
				drm_i915_gem_execbuffer2 *buffer = (drm_i915_gem_execbuffer2 *)arg;

				Drm::Gem_execbuffer2(buffer, content).copy_out();
				return true;
			}

			if (driver_nr(request) == DRM_I915_GEM_PWRITE) {
				drm_i915_gem_pwrite *target = (drm_i915_gem_pwrite *)arg;
				Genode::memcpy(content, arg, sizeof(*target));
				Genode::memcpy((char *)content + sizeof(*target), (void *)target->data_ptr, target->size);
				return true;
			}

			return false;
		}

		bool _fixup_i915_ioctl(unsigned long request, void *target, void *result)
		{
			if (driver_nr(request) == DRM_I915_GETPARAM) {
				drm_i915_getparam_t *t = (drm_i915_getparam_t *)target;
				drm_i915_getparam_t *r = (drm_i915_getparam_t *)result;
				*t->value = ((long)r->value & ~0U);
				return true;
			}

			if (driver_nr(request) == DRM_I915_GEM_EXECBUFFER2) {
				drm_i915_gem_execbuffer2 *buffer = (drm_i915_gem_execbuffer2 *)target;

				Drm::Gem_execbuffer2(buffer, result).copy_in();
				return true;
			}

			return false;
		}

		int _gem_mmap(void *arg)
		{
			//TODO: ERROR handling
			drm_i915_gem_mmap *data = (drm_i915_gem_mmap *)arg;

			Genode::Ram_dataspace_capability ds = _drm_session.object_dataspace(data->handle);
			data->addr_ptr = (__u64)_env.rm().attach(ds);
			return 0;
		}

		int _gem_mmap_gtt(void *arg)
		{
			//TODO: ERROR handling
			drm_i915_gem_mmap_gtt *data = (drm_i915_gem_mmap_gtt *)arg;

			Genode::Dataspace_capability ds = _drm_session.object_dataspace_gtt(data->handle);
			data->offset = (__u64)_env.rm().attach(ds);
			return 0;
		}

	public:

		Drm_call(Genode::Env &env) : _env(env) { }

		int ioctl(unsigned long request, void *arg)
		{
			size_t size = IOCPARM_LEN(request);

			using namespace Drm;

			if (driver_nr(request) == DRM_I915_GEM_MMAP) {
				return _gem_mmap(arg);
			}

			if (driver_nr(request) == DRM_I915_GEM_MMAP_GTT) {
				return _gem_mmap_gtt(arg);
			}

			if (driver_nr(request) == DRM_I915_GEM_EXECBUFFER2) {
				size = Drm::Gem_execbuffer2((drm_i915_gem_execbuffer2 *)arg).size();
			}

			/* submit */
			Session::Tx::Source &src = *_drm_session.tx();
			Packet_descriptor pkt(src.alloc_packet(size), drm_nr(request));


			if(!_fixup_packet(request, arg, src.packet_content(pkt))) {
				Genode::memcpy(src.packet_content(pkt), arg, size);
			}

			src.submit_packet(pkt);

			/* receive */
			pkt = src.get_acked_packet();

			if (!_fixup_i915_ioctl(request, arg, src.packet_content(pkt))) {
				Genode::memcpy(arg, src.packet_content(pkt), size);
			}

			src.release_packet(pkt);

			return pkt.error();
		}
};

Genode::Constructible<Drm_call> drm;


void drm_init(Genode::Env &env)
{
	drm.construct(env);
}


extern "C" int genode_ioctl(int fd, unsigned long request, void *arg)
{
	if (verbose_ioctl)
		dump_ioctl(request);

	int ret = drm->ioctl(request, arg);

	if (verbose_ioctl)
		Genode::log("returned ", ret);

	return ret;
}
