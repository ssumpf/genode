/**
 * \brief  Manage object dependencies
 * \author Sebastian Sumpf
 * \date   2015-03-12
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <linker.h>
#include <dynamic.h>
#include <init.h>


/**
 * Dependency node
 */
Linker::Dependency::Dependency(Env &env, Allocator &md_alloc,
                               char const *path, Root_object *root,
                               Fifo<Dependency> &deps,
                               Keep keep)
:
	_obj(load(env, md_alloc, path, *this, keep)),
	_root(root),
	_md_alloc(&md_alloc)
{
	Genode::error(__func__, ":", __LINE__, " path: '", path, "'");
	deps.enqueue(this);
	Genode::error(__func__, ":", __LINE__, " path: '", path, "'");
	load_needed(env, *_md_alloc, deps, keep);
	Genode::error(__func__, ":", __LINE__, " path: '", path, "'");
}


Linker::Dependency::~Dependency()
{
	if (!_obj.unload())
		return;

	// if (verbose_loading)
		log("Destroy: ", _obj.name());

	destroy(_md_alloc, &_obj);
}


bool Linker::Dependency::in_dep(char const *file, Fifo<Dependency> const &dep)
{
	for (Dependency const *d = dep.head(); d; d = d->next()) {
		Genode::error(__func__, ":", __LINE__, " file: '", file, "' dep: '", d->obj().name(), "'");
		if (!strcmp(file, d->obj().name()))
			return true;
	}

	Genode::error(__func__, ":", __LINE__, " file: '", file, "' not found");
	return false;
}


void Linker::Dependency::load_needed(Env &env, Allocator &md_alloc,
                                     Fifo<Dependency> &deps, Keep keep)
{
	_obj.dynamic().for_each_dependency([&] (char const *path) {

		Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");

		if (!in_dep(Linker::file(path), deps)) {
			Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");
			new (md_alloc) Dependency(env, md_alloc, path, _root, deps, keep);
			Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");
		} else {

			/* re-order initializer list, if needed object has been already added */

			try {
				Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");

				Object *o = Init::list()->contains(Linker::file(path));
				if (o) {
					Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");
					try {
						Init::list()->reorder(o);
					} catch (...) {
						Genode::error("le fsck is tis");
						throw;
					}
					Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");
				}
				Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");
			} catch (...) {
				Genode::error("le foo is dat");
				throw;
			}
		}

		Genode::error("load_needed", ":", __LINE__, " path: '", path, "'");
	});
}


Linker::Dependency const &Linker::Dependency::first() const
{
	return _root ? *_root->first_dep() : *this;
}


Linker::Root_object::Root_object(Env &env, Allocator &md_alloc,
                                 char const *path, Bind bind, Keep keep)
:
	_md_alloc(md_alloc)
{
	/*
	 * The life time of 'Dependency' objects is managed via reference
	 * counting. Hence, we don't need to remember them here.
	 */
	Genode::error(__func__, ":", __LINE__);
	Dependency *d1 = new (md_alloc) Dependency(env, md_alloc, path, this, _deps, keep);

	Genode::error(__func__, ":", __LINE__);
	/* provide Genode base library access */
	Dependency *d2 = new (md_alloc) Dependency(env, md_alloc, linker_name(), this, _deps, DONT_KEEP);

	Genode::error(__func__, ":", __LINE__);
	/* relocate and call constructors */
	try {
		Init::list()->initialize(bind, STAGE_SO);
	} catch (...) {
		destroy(md_alloc, d1);
		destroy(md_alloc, d2);
		throw;
	}
	Genode::error(__func__, ":", __LINE__);
}
