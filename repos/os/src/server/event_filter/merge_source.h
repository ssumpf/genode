/*
 * \brief  Input-event source that merges other sources
 * \author Norman Feske
 * \date   2017-02-01
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _EVENT_FILTER__MERGE_SOURCE_H_
#define _EVENT_FILTER__MERGE_SOURCE_H_

/* local includes */
#include <include_accessor.h>
#include <source.h>

namespace Event_filter { class Merge_source; }


class Event_filter::Merge_source : public Source
{
	private:

		Owner _owner;

		Include_accessor &_include_accessor;

		void _apply_config(Node const &config, unsigned const max_recursion = 4)
		{
			config.for_each_sub_node([&] (Node const &node) {
				_apply_sub_node(node, max_recursion); });
		}

		void _apply_sub_node(Node const &node, unsigned const max_recursion)
		{
			if (max_recursion == 0) {
				warning("too deeply nested includes");
				throw Invalid_config();
			}

			/*
			 * Handle includes
			 */
			if (node.type() == "include") {
				try {
					Include_accessor::Name const rom =
						node.attribute_value("rom", Include_accessor::Name());

					_include_accessor.apply_include(rom, name(), [&] (Node const &inc) {
						_apply_config(inc, max_recursion - 1); });
					return;
				}
				catch (Include_accessor::Include_unavailable) {
					throw Invalid_config(); }
			}

			/*
			 * Handle input nodes
			 */
			if (input_node(node))
				_owner._factory.create_source(_owner, node);
		}

	public:

		static char const *name() { return "merge"; }

		Merge_source(Owner &owner, Node const &config, Source::Factory &factory,
		             Include_accessor &include_accessor)
		:
			Source(owner), _owner(factory), _include_accessor(include_accessor)
		{
			_apply_config(config);
		}

		void generate(Sink &destination) override
		{
			_owner.for_each([&] (Source &source) {
				source.generate(destination); });
		}
};

#endif /* _EVENT_FILTER__REMAP_SOURCE_H_ */
