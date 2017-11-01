/*
 * \brief  Input-event source that emulates a wheel from motion events
 * \author Norman Feske
 * \date   2017-11-01
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INPUT_FILTER__BUTTON_SCROLL_SOURCE_H_
#define _INPUT_FILTER__BUTTON_SCROLL_SOURCE_H_

/* Genode includes */
#include <input/keycodes.h>

/* local includes */
#include <source.h>
#include <key_code_by_name.h>

namespace Input_filter { class Button_scroll_source; }


class Input_filter::Button_scroll_source : public Source, Source::Sink
{
	private:

		struct Wheel
		{
			Input::Keycode const _button;

			static Key_name _button_attribute(Xml_node node)
			{
				return node.attribute_value("button", Key_name("BTN_MIDDLE"));
			}

			/**
			 * Factor to scale motion events in percent
			 */
			int const _factor;
			int const _factor_sign    = (_factor < 0) ? -1 : 1;
			int const _factor_percent = _factor_sign*_factor;

			/**
			 * True while user holds the configured button
			 */
			bool _active = false;

			/**
			 * Sum of motion in current direction
			 *
			 * The value is reset whenever '_active' becomes true or the
			 * direction changes.
			 */
			int _accumulated_motion = 0;

			void _reset() { _accumulated_motion = 0; }

			Wheel(Xml_node config)
			:
				_button(key_code_by_name(_button_attribute(config).string())),
				_factor(config.attribute_value("speed_percent", 0L))
			{ }

			void handle_activation(Input::Event const &event)
			{
				if (event.keycode() != _button) return;

				if (event.type() == Input::Event::PRESS)   _active = true;
				if (event.type() == Input::Event::RELEASE) _active = false;

				if (event.type() == Input::Event::PRESS)
					_reset();
			}

			void apply_relative_motion(int motion)
			{
				if (!_active) return;

				/* reset if motion direction changes */
				if (motion*_accumulated_motion < 0)
					_reset();

				_accumulated_motion += motion*_factor_percent;
			}

			/**
			 * Return pending wheel motion
			 */
			int pending_motion()
			{
				int const quantizized = _accumulated_motion/100;

				if (quantizized != 0)
					_accumulated_motion -= quantizized*100;

				return _factor_sign*quantizized;
			}

			/**
			 * True if the given event must be filtered out from the event
			 * stream
			 */
			bool suppressed(Input::Event const event)
			{
				return _active && event.relative_motion();
			}
		};

		Wheel _vertical_wheel, _horizontal_wheel;

		Owner _owner;

		Source &_source;

		Source::Sink &_destination;

		/**
		 * Sink interface
		 */
		void submit_event(Input::Event const &event) override
		{
			using Input::Event;

			_vertical_wheel  .handle_activation(event);
			_horizontal_wheel.handle_activation(event);

			if (event.relative_motion()) {
				_vertical_wheel  .apply_relative_motion(event.ry());
				_horizontal_wheel.apply_relative_motion(event.rx());
			}

			/* emit artificial wheel event */
			int const wheel_x = _horizontal_wheel.pending_motion(),
			          wheel_y = _vertical_wheel  .pending_motion();

			if (wheel_x || wheel_y)
				_destination.submit_event(Event(Event::WHEEL, 0, 0, 0,
				                                wheel_x, wheel_y));

			/* hide consumed relative motion events */
			if (_vertical_wheel  .suppressed(event)) return;
			if (_horizontal_wheel.suppressed(event)) return;

			/* forward unrelated events */
			_destination.submit_event(event);
		}

		static Xml_node _sub_node(Xml_node node, char const *type)
		{
			return node.has_sub_node(type) ? node.sub_node(type)
			                               : Xml_node("<ignored/>");
		}

	public:

		static char const *name() { return "button-scroll"; }

		Button_scroll_source(Owner &owner, Xml_node config, Source::Sink &destination,
		                     Source::Factory &factory)
		:
			Source(owner),
			_vertical_wheel  (_sub_node(config, "vertical")),
			_horizontal_wheel(_sub_node(config, "horizontal")),
			_owner(factory),
			_source(factory.create_source(_owner, input_sub_node(config), *this)),
			_destination(destination)
		{
			log("Button_scroll_source created");
		}

		void generate() override { _source.generate(); }
};

#endif /* _INPUT_FILTER__BUTTON_SCROLL_SOURCE_H_ */
