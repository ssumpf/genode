#ifndef _DIRECTORY_TREE_H_
#define _DIRECTORY_TREE_H_

#include <util/avl_string.h>

#include "session_label.h"

namespace Vfs {
	class Directory_tree;
	template <typename> class Object_tree;

	class String_node;
	class Trace_node;

	typedef Genode::Avl_string<32> Label;
}

namespace Genode {
	template <typename> class Avl_node_tree;
}

template <typename NT>
class Genode::Avl_node_tree : public NT
{
	protected:

		using Tree = Avl_tree<NT>;
		using Node = NT;

		Tree _tree;

	public:

		using NT::NT;

		void insert(Node *node) { _tree.insert(node); }

		Tree &tree() { return _tree; }
};

class Vfs::Trace_node : public Vfs::Label
{
	private:

		Trace::Subject_id const _id;

	public:

		Trace_node(Trace::Subject_id const id, char const *name)
		: Avl_string(name),
		  _id(id) { }
};


class Vfs::String_node : public Avl_node_tree<Vfs::Label>
{
	private:

		Allocator &_alloc;

		String_node *_find_by_name(char const *name)
		{
			if (!_tree.first()) return nullptr;

			Avl_string_base *node = _tree.first()->find_by_name(name);
			if (!node) return nullptr;

			return static_cast<String_node *>(node);
		}

	public:

		String_node(Genode::Allocator &alloc, Session_label const &label)
		: Avl_node_tree(label.string()),
		  _alloc(alloc) { Genode::warning("NEW node: ", label); }

		String_node &insert(Session_label const &label)
		{
			if (!label.valid()) { log("NOT VALID"); return *this; }

			String_node *node = _find_by_name(label.first_element().string());
			Genode::warning("search: ", label.first_element(), " node: ", node, " node name: ", node ? node->name() : "<empty>");
			if (!node) {
				node = new(_alloc) String_node(_alloc, label.first_element());
				Avl_node_tree::insert(node);
				Genode::log("insert: ", label.first_element());
			}

			Genode::error("suffix: ", label.suffix(), " node: ", node->name());
			return node->insert(label.suffix());
		}
};


class Vfs::Directory_tree
{
	private:

		Allocator     &_alloc;
		String_node    _root { _alloc, Session_label() };

	public:

		Directory_tree(Genode::Allocator &alloc)
		: _alloc(alloc) { }

		void insert(Trace::Subject_info const &info, Trace::Subject_id const id)
		{
			String_node &leaf = _root.insert(info.session_label());

			Trace_node *node = new (_alloc) Trace_node(id, info.thread_name().string());
			Genode::warning("insert leaf tree: ", &leaf.tree(), " thread: ", info.thread_name());
			leaf.insert(node);
			Genode::warning("leaf done");
		}

		void xml()
		{
			_root.tree().for_each([&] (Genode::Avl_string_base const &node) {
				Genode::warning("node ", &node);
				Genode::warning("for: ", node.name());
			});
		}
};

#if 0
template <typename OBJECT>
class Vfs::Object_tree : public Genode::Avl_tree<Genode::Avl_string_base>
{

};

class Vfs::Directory_tree : public Genode::Avl_tree<Avl_string_base>,
                            public Genode::Avl_string_base
{
	private:

		using Node = Genode::Avl_string_base;
		using Tree = Genode::Avl_tree<Avl_string_base>;

		Allocator     &_alloc;

		Directory_tree *_find_by_name(char const *name)
		{
			if (!first()) return nullptr;

			Node *node = first()->find_by_name(name);
			if (!node) return nullptr;

			return static_cast<Directory_tree *>(node);
		}

		Directory_tree *_insert(Session_label const &name)
		{
			Directory_tree *next_level = _find_by_name(name.string());

			if (next_level) return next_level;

			next_level = new (_alloc) Directory_tree(_alloc, name);
			Tree::insert(static_cast<Node *>(next_level));

			return next_level;
		}

	public:

		Directory_tree(Genode::Allocator &alloc, Session_label const &name)

		: Avl_string_base(name.string()),
		  _alloc(alloc) { }

		void insert(Vfs::Session_label const &label)
		{
			Directory_tree *next_level    = this;
			Session_label   current       = label;

			do {
				next_level = next_level->_insert(current.first_element());
				current = current.suffix();
			} while (current.valid());
		}
};
#endif
#endif /* _DIRECTORY_TREE_H_ */
