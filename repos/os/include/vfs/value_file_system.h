/*
 * \brief  File system for providing a read-only value as a file
 * \author Norman Feske
 * \date   2018-03-27
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__VFS__VALUE_FILE_SYSTEM_H_
#define _INCLUDE__VFS__VALUE_FILE_SYSTEM_H_

/* Genode includes */
#include <util/xml_generator.h>
#include <vfs/single_file_system.h>

namespace Vfs {
	template <typename, unsigned BUF_SIZE = 128>
	class Value_file_system;
}


template <typename T, unsigned BUF_SIZE>
class Vfs::Value_file_system : public Vfs::Single_file_system
{
	public:

		typedef Genode::String<64> Name;

	private:

		typedef Genode::String<BUF_SIZE + 1> Buffer;

		Name const _file_name;

		Buffer _out_buffer { };
		char   _in_buffer[BUF_SIZE+1]  { };
		Genode::Signal_context_capability _notify { };

		struct Vfs_handle : Single_vfs_handle
		{
			Buffer const &_out_buffer;
			char         *_in_buffer;
			Genode::Signal_context_capability _notify { };

			Vfs_handle(Directory_service &ds,
			           File_io_service   &fs,
			           Allocator         &alloc,
			           Buffer      const &out_buffer,
			           char              *in_buffer,
			           Genode::Signal_context_capability notify)
			:
				Single_vfs_handle(ds, fs, alloc, 0),
				_out_buffer(out_buffer), _in_buffer(in_buffer), _notify(notify)
			{ }

			Read_result read(char *dst, file_size count,
			                 file_size &out_count) override
			{
				out_count = 0;

				if (seek() > _out_buffer.length())
					return READ_ERR_INVALID;

				char const *   const src = _out_buffer.string() + seek();
				Genode::size_t const len = min(_out_buffer.length() - seek(), count);
				Genode::memcpy(dst, src, len);

				out_count = len;
				return READ_OK;
			}

			Write_result write(char const *src, file_size count, file_size &out_count) override
			{
				out_count = 0;
				if (seek() > BUF_SIZE)
					return WRITE_ERR_INVALID;

				// char       *   const dst = _in_buffer.string() + seek();
				// Genode::size_t const len = min(_in_buffer.length() - seek(), count);
				char * const dst = _in_buffer;
				Genode::size_t const len = min(BUF_SIZE- seek(), count);
				Genode::memcpy(dst, src, len);

				out_count = len;

				if (_notify.valid())
					Genode::Signal_transmitter(_notify).submit();
				return WRITE_OK;
			}

			bool read_ready() override { return true; }

			private:

			Vfs_handle(Vfs_handle const &); 
			Vfs_handle &operator = (Vfs_handle const &); 
		};

		typedef Genode::String<200> Config;
		Config _config(Name const &name) const
		{
			char buf[Config::capacity()] { };
			Genode::Xml_generator xml(buf, sizeof(buf), type_name(), [&] () {
				xml.attribute("name", name); });
			return Config(Genode::Cstring(buf));
		}

		struct Watch_handle;
		using Watch_handle_registry = Genode::Registry<Watch_handle>;

		struct Watch_handle : Vfs_watch_handle
		{
			typename Watch_handle_registry::Element elem;

			Watch_handle(Watch_handle_registry &registry,
			                     Vfs::File_system      &fs,
			                     Allocator             &alloc)
			: Vfs_watch_handle(fs, alloc), elem(registry, *this) { }
		};

		Watch_handle_registry _watch_handle_registry { };

		Watch_response_handler &_watch_handler;

	public:

		Value_file_system(Vfs::Env &env, Name const &name, T const &initial_value,
		                  Genode::Signal_context_capability notify_sigh)
		:
			Single_file_system(NODE_TYPE_CHAR_DEVICE, type(),
			                   Xml_node(_config(name).string())),
			_file_name(name), _notify(notify_sigh),
			_watch_handler(env.watch_handler())
		{
			value(initial_value);
		}

		static char const *type_name() { return "value"; }

		char const *type() override { return type_name(); }

		void value(T const &value)
		{
			_out_buffer = Buffer(value);

			_watch_handle_registry.for_each([&] (Watch_handle &wh) {
				_watch_handler.handle_watch_response(wh.context());
			});
		}

		char const *buffer() const { return _in_buffer; }

		bool matches(Xml_node node) const
		{
			return node.has_type(type_name()) &&
			       node.attribute_value("name", Name()) == _file_name;
		}

		/*********************************
		 ** Directory-service interface **
		 *********************************/

		Open_result open(char const  *path, unsigned,
		                 Vfs::Vfs_handle **out_handle,
		                 Allocator   &alloc) override
		{
			if (!_single_file(path))
				return OPEN_ERR_UNACCESSIBLE;

			try {
				*out_handle = new (alloc)
					Vfs_handle(*this, *this, alloc, _out_buffer, _in_buffer, _notify);

				return OPEN_OK;
			}
			catch (Genode::Out_of_ram)  { return OPEN_ERR_OUT_OF_RAM; }
			catch (Genode::Out_of_caps) { return OPEN_ERR_OUT_OF_CAPS; }
		}

		Stat_result stat(char const *path, Stat &out) override
		{
			Stat_result result = Single_file_system::stat(path, out);
			out.mode |= 0444;
			out.size = _out_buffer.length();
			return result;
		}

		Watch_result watch(char const      *path,
		                   Vfs_watch_handle **handle,
		                   Allocator        &alloc) override
		{
			if (!_single_file(path))
				return WATCH_ERR_UNACCESSIBLE;

			try {
				Watch_handle *wh = new (alloc)
					Watch_handle(_watch_handle_registry, *this, alloc);
				*handle = wh;
				return WATCH_OK;
			}
			catch (Genode::Out_of_ram)  { return WATCH_ERR_OUT_OF_RAM;  }
			catch (Genode::Out_of_caps) { return WATCH_ERR_OUT_OF_CAPS; }
		}

		void close(Vfs_watch_handle *handle) override
		{
			if (handle && (&handle->fs() == this))
				destroy(handle->alloc(), handle);
		}
};

#endif /* _INCLUDE__VFS__VALUE_FILE_SYSTEM_H_ */
