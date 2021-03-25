/**
 * \brief  Shadow copy of drm/drm_atomic_uapi.h
 * \author Josef Soentgen
 * \date   2021-03-19
 */

#pragma once

/*
 * The DRM header uses the `__mustcheck` macro.
 */
#include      <linux/compiler_types.h>
#include_next <drm/drm_atomic_uapi.h>
