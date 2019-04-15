#ifndef _DIRECTORY_TREE_H_
#define _DIRECTORY_TREE_H_

#include <util/avl_string.h>

#include "session_label.h"

namespace Vfs {
	class  Directory_tree;
	class  Trace_node;
	struct Label;
}

namespace Genode {
	template <typename> class Avl_node_tree;
}

template <typename NT>
class Genode::Avl_node_tree : public NT
{
	protected:

		using Tree = Avl_tree<NT>;
		using Node = Avl_node<NT>;

		Tree _tree;

	public:

		using NT::NT;

		void insert(Node *node) { _tree.insert(node); }

		Tree &tree() { return _tree; }

		Node *find_by_name(char const *name)
		{
			if (!_tree.first()) return nullptr;

			Node *node = _tree.first()->find_by_name(name);
			return node;
		}
};

struct Vfs::Label : Genode::String<32>
{
	using String::String;
};

class Vfs::Trace_node : public Vfs::Label,
                         public Avl_node_tree<Genode::Avl_string_base>
{
	private:

		Allocator              &_alloc;
		Trace::Subject_id const _id;

		Trace_node *_find_by_name(char const *name)
		{
			Node *node = find_by_name(name);
			return node ? static_cast<Trace_node *>(node) : nullptr;
		}

	public:

		Trace_node(Genode::Allocator &alloc, Session_label const &label,
		            Trace::Subject_id const id = 0)
		: Vfs::Label(label), Avl_node_tree(string()),
		  _alloc(alloc), _id(id)
		{ }

		Trace_node &insert(Session_label const &label)
		{
			if (!label.valid()) return *this;

			Trace_node *node = _find_by_name(label.first_element().string());
			if (!node) {
				node = new(_alloc) Trace_node(_alloc, label.first_element());
				Avl_node_tree::insert(node);
			}

			return node->insert(label.suffix());
		}

		void xml(unsigned level)
		{
			_tree.for_each([&] (Genode::Avl_string_base const &node) {
				Trace_node &n = const_cast<Trace_node &>(static_cast<Trace_node const &>(node));
				Genode::warning("(", level, ") xml: ", node.name(), " id: ", n._id.id);
				n.xml(level + 1);});
		}
};

class Vfs::Directory_tree : public Genode::Avl_tree<Trace_node>
{
	private:

		Allocator     &_alloc;
		Trace_node    _root { _alloc, Session_label() };

	public:

		Directory_tree(Genode::Allocator &alloc)
		: _alloc(alloc) { }

		void insert(Trace::Subject_info const &info, Trace::Subject_id const id)
		{
			Trace_node &leaf = _root.insert(info.session_label());
			Trace_node *node  = new (_alloc) Trace_node(_alloc, info.thread_name(), id);
			leaf.Avl_node_tree::insert(node);
		}

		void xml()
		{
			_root.xml(0);
		}
};

#endif /* _DIRECTORY_TREE_H_ */
