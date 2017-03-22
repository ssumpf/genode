#include <drivers/dri/i965/intel_image.h>


void *genode_map_image(__DRIimage *image)
{
	/* map read only */
	drm_intel_bo_map(image->bo, false);
	return image->bo->virtual;
}


void genode_unmap_image(__DRIimage *image)
{
	drm_intel_bo_unmap(image->bo);
}
