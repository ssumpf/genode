#ifndef _INCLUDE__DRM__SERIALIZE_
#define _INCLUDE__DRM__SERIALIZE_

namespace Drm {
class Gem_execbuffer2;
}


class Drm::Gem_execbuffer2
{
	private:

		drm_i915_gem_execbuffer2 *_buffer = nullptr;
		char                     *_packet = nullptr;
		unsigned                  _offset = 0;


	template <typename FUNC>
	void for_each_object(drm_i915_gem_execbuffer2 const *buffer, FUNC const &func)
	{
		for (unsigned i = 0; i < buffer->buffer_count; i++) {
			drm_i915_gem_exec_object2 *obj =  &((drm_i915_gem_exec_object2 *)buffer->buffers_ptr)[i];
			func(obj);
		}
	}

	void _cpy(void *dst, void *src, Genode::size_t size)
	{
		Genode::memcpy(dst, src,size);
		_offset += size;
	}


	public:

		Gem_execbuffer2(drm_i915_gem_execbuffer2 *buffer) : _buffer(buffer) { }
		Gem_execbuffer2(drm_i915_gem_execbuffer2 *buffer, void *packet) : _buffer(buffer), _packet((char *)packet) { }
		Gem_execbuffer2(void *packet) : _packet((char *)packet) { }

		Genode::size_t size()
		{
			Genode::size_t size = sizeof(drm_i915_gem_execbuffer2) 
			                     + (sizeof(drm_i915_gem_exec_object2) * _buffer->buffer_count);

			auto lambda = [&](drm_i915_gem_exec_object2 *obj) {
				size += sizeof(drm_i915_gem_relocation_entry) * obj->relocation_count;
			};

			for_each_object(_buffer, lambda);

			return size;
		}

		void copy_out()
		{
			_offset  = 0;
			_cpy(_packet, _buffer, sizeof(drm_i915_gem_execbuffer2));
			_cpy(_packet + _offset, (void *)_buffer->buffers_ptr,
			     sizeof(drm_i915_gem_exec_object2) * _buffer->buffer_count);
			
			if (_buffer->num_cliprects)
				_cpy(_packet + _offset, (void *)_buffer->cliprects_ptr,
				     sizeof(drm_clip_rect) * _buffer->num_cliprects);

			auto lambda = [&](drm_i915_gem_exec_object2 *obj) {
				_cpy(_packet + _offset, (void *)obj->relocs_ptr, 
				     sizeof(drm_i915_gem_relocation_entry) * obj->relocation_count);
			};

			for_each_object(_buffer, lambda);
		}

		drm_i915_gem_execbuffer2 * adjust()
		{
			_buffer = (drm_i915_gem_execbuffer2 *)_packet;
			_offset = sizeof(drm_i915_gem_execbuffer2);
			_buffer->buffers_ptr = (unsigned long long)(_packet + _offset);
			_offset += _buffer->buffer_count * sizeof(drm_i915_gem_exec_object2);

			if (_buffer->num_cliprects) {
				_buffer->cliprects_ptr = (unsigned long long)(_packet + _offset);
				_offset += _buffer->num_cliprects * sizeof(drm_clip_rect);
			}

			auto lambda = [&](drm_i915_gem_exec_object2 *obj) {
				obj->relocs_ptr = (unsigned long long)(_packet + _offset);
				_offset += obj->relocation_count * sizeof(drm_i915_gem_relocation_entry);
			};

			for_each_object(_buffer, lambda);

			return _buffer;
		}

		void copy_in()
		{
			_offset = sizeof(drm_i915_gem_execbuffer2) +
			          _buffer->buffer_count * sizeof(drm_i915_gem_exec_object2) +
			          _buffer->num_cliprects * sizeof(drm_clip_rect);

			auto lambda = [&](drm_i915_gem_exec_object2 *obj) {
				_cpy((void *)obj->relocs_ptr, _packet + _offset,
				     sizeof(drm_i915_gem_relocation_entry) * obj->relocation_count);
			};

			for_each_object(_buffer, lambda);

			_offset = sizeof(drm_i915_gem_execbuffer2);
			auto lambda2 = [&](drm_i915_gem_exec_object2 *obj) {
				unsigned long long relocs_ptr = obj->relocs_ptr;
				_cpy((void *)obj, _packet + _offset, sizeof(drm_i915_gem_exec_object2));
				obj->relocs_ptr = relocs_ptr;
			};

			for_each_object(_buffer, lambda2);
		}
};



#endif /* _INCLUDE__DRM__SERIALIZE_ */
