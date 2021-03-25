/*
 * \brief  DRM session capability type
 * \author Sebastian Sumpf
 * \date   2010-07-07
 */

/*
 * Copyright (C) 2010-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__GPU__CAPABILITY_H_
#define _INCLUDE__GPU__CAPABILITY_H_

#include <base/capability.h>
#include <gpu/drm_session.h>

namespace Drm { typedef Genode::Capability<Session> Session_capability; }

#endif /* _INCLUDE__GPU__CAPABILITY_H_ */
