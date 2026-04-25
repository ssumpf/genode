/*
 * \brief  Framebuffer driver that uses a framebuffer supplied by the core rom.
 * \author Johannes Kliemann
 * \author Norman Feske
 * \date   2017-06-12
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>
#include <base/attached_rom_dataspace.h>
#include <base/attached_io_mem_dataspace.h>
#include <dataspace/capability.h>
#include <capture_session/connection.h>
#include <timer_session/connection.h>
#include <os/reporter.h>

namespace Framebuffer {
	using namespace Genode;
	struct Main;
}


struct Framebuffer::Main
{
	using Area  = Capture::Area;
	using Pixel = Capture::Pixel;

	Env &_env;

	Attached_rom_dataspace _config        { _env, "config" };
	Attached_rom_dataspace _platform_info { _env, "platform_info" };
	Expanding_reporter     _reporter      { _env, "connectors", "connectors" };

	struct Info
	{
		addr_t   addr;
		Area     size;
		unsigned bpp;
		unsigned pitch;
		unsigned type;

		static Info from_platform_info(Node const &node)
		{
			Info result { };
			node.with_optional_sub_node("boot", [&] (Node const &boot) {
				boot.with_optional_sub_node("framebuffer", [&] (Node const &fb) {
					result = {
						.addr   = fb.attribute_value("phys",  0UL),
						.size = { fb.attribute_value("width",  0U),
						          fb.attribute_value("height", 0U) },
						.bpp    = fb.attribute_value("bpp",    0U),
						.pitch  = fb.attribute_value("pitch",  0U),
						.type   = fb.attribute_value("type",   0U)
					};
				});
			});
			return result;
		}

		Area phys_area() const
		{
			auto const sanitized_bpp = bpp ? : 1;
			auto const width = pitch ? pitch * 8 / sanitized_bpp : size.w;

			return { width, size.h };
		}

		enum { TYPE_RGB_COLOR = 1 };

		void print(Output &out) const
		{
			Genode::print(out, size, "x", bpp, " @ ", (void*)addr, " "
			              "type=", type, " pitch=", pitch, " -> ", phys_area());
		}

		Area size_in_mm() const { return { }; }
	};

	Info const _info = Info::from_platform_info(_platform_info.node());

	void _check_info() const
	{
		if (_info.bpp != 32 || _info.type != Info::TYPE_RGB_COLOR ) {
			error("unsupported resolution (bpp or/and type), platform info:\n",
			      _platform_info.node());
			throw Exception();
		}
	}

	bool const _checked_info = ( _check_info(), true );

	Attached_io_mem_dataspace _fb_ds { _env, _info.addr,
	                                   _info.pitch*_info.size.h, true };

	Constructible<Capture::Connection>         _capture { };
	Constructible<Capture::Connection::Screen> _screen  { };

	Blit::Flip   _flip   { };
	Blit::Rotate _rotate { Blit::Rotate::R0 };

	Timer::Connection _timer { _env };

	Signal_handler<Main> _timer_handler  { _env.ep(), *this, &Main::_handle_timer };
	Signal_handler<Main> _config_handler { _env.ep(), *this, &Main::_handle_config };

	void _handle_config();
	void _rotate_flip();

	void _handle_timer()
	{
		Surface<Pixel> surface(_fb_ds.local_addr<Pixel>(), _info.phys_area());

		_screen->apply_to_surface(surface);
	}

	void report_connectors(Generator &g, unsigned width, unsigned height)
	{
		g.node("merge", [&]() {
			g.attribute("name", "mirror");

			g.node("connector", [&] () {
				g.attribute("connected", true);
				g.attribute("enabled"  , true);
				g.attribute("name"     , "Boot");
				g.attribute("rotate"   , _rotate == Blit::Rotate::R90  ? "90"  :
				                         _rotate == Blit::Rotate::R180 ? "180" :
				                         _rotate == Blit::Rotate::R270 ? "270" : "0");
				g.attribute("flip"     , _flip.enabled);

				g.node("mode", [&] () {
					g.attribute(    "id", 1);
					g.attribute( "width", width);
					g.attribute("height", height);
					g.attribute(  "name", String<32>(width, "x", height));
					g.attribute(  "used", true);
				});
			});
		});
	}

	Main(Env &env) : _env(env)
	{
		log("using boot framebuffer: ", _info);

		_config.sigh(_config_handler);
		_timer .sigh(_timer_handler);

		using Attr = Capture::Connection::Screen::Attr;

		_capture.construct(env);
		_screen.construct(*_capture, env.rm(),
		                  Attr { .px       = _info.phys_area(),
		                         .mm       = { },
		                         .viewport = { { }, _info.size },
		                         .rotate   = { },
		                         .flip     = { } } );

		_timer.trigger_periodic(20 * 1000);

		_reporter.generate([&] (Generator &g) {
			report_connectors(g, _info.size.w, _info.size.h);
		});
	}
};


void Framebuffer::Main::_handle_config()
{
	_config.update();

	if (!_config.valid())
		return;

	auto const &config    = _config.node();
	auto const  period_ms = config.attribute_value("period_ms", 20UL);
	bool        changed   = false;

	_timer.trigger_periodic(period_ms * 1000);

	config.with_optional_sub_node("merge", [&] (auto const &merge) {
		merge.with_optional_sub_node("connector", [&] (auto const &conn) {
			auto const rotate = conn.attribute_value("rotate" , 0U);
			auto const flip   = conn.attribute_value("flip"   , false);

			auto before_rotate = _rotate;
			auto before_flip   = _flip;

			_flip  = { .enabled = flip };
			_rotate = (rotate ==  90) ? Blit::Rotate::R90  :
			          (rotate == 180) ? Blit::Rotate::R180 :
			          (rotate == 270) ? Blit::Rotate::R270 :
			                            Blit::Rotate::R0;

			changed = before_flip.enabled != _flip.enabled ||
			          before_rotate       != _rotate;

			if (changed)
				_rotate_flip();
		});
	});

	if (changed)
		_reporter.generate([&] (Generator &g) {
			report_connectors(g, _info.size.w, _info.size.h);
		});
}


void Framebuffer::Main::_rotate_flip()
{

	_screen .destruct();
	_capture.destruct();

	auto const r_ps = Blit::transformed(_info.phys_area(), _rotate);
	auto const r_vs = Blit::transformed(_info.size,        _rotate);

	Point const p_90  = { .x = 0, .y = int(r_ps.h - r_vs.h) };
	Point const p_180 = { .x = int(r_ps.w - r_vs.w),
	                      .y = int(r_ps.h - r_vs.h) };
	Point const p_270 = { .x = int(r_ps.w - r_vs.w), .y = 0 };

	Point po = { };

	switch (_rotate) {
		case Blit::Rotate::R0  : po = !_flip.enabled ? po    : p_270; break;
		case Blit::Rotate::R90 : po = !_flip.enabled ? p_90  : po;    break;
		case Blit::Rotate::R180: po = !_flip.enabled ? p_180 : p_90;  break;
		case Blit::Rotate::R270: po = !_flip.enabled ? p_270 : p_180; break;
	}

	using Attr = Capture::Connection::Screen::Attr;

	Attr attr = { .px       = r_ps,
	              .mm       = Blit::transformed(_info.size_in_mm(), _rotate),
	              .viewport = { .at = po, .area = r_vs },
	              .rotate   = _rotate,
	              .flip     = _flip };

	_capture.construct(_env);
	_screen .construct(*_capture, _env.rm(), attr);
}


void Component::construct(Genode::Env &env) { static Framebuffer::Main inst(env); }
