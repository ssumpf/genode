/*
 * \brief  Platform session capability type
 * \author Stefan Kalkowski
 * \date   2026-05-05
 */

/*
 * Copyright (C) 2026 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__DMA_SESSION__CAPABILITY_H_
#define _INCLUDE__DMA_SESSION__CAPABILITY_H_

#include <base/capability.h>
#include <dma_session/dma_session.h>

namespace Dma { using Session_capability = Genode::Capability<Session>; }

#endif /* _INCLUDE__DMA_SESSION__CAPABILITY_H_ */
