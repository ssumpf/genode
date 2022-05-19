#include <genode_c_api/base.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace Audio_out {

	enum Channel_number { LEFT, RIGHT, MAX_CHANNELS, INVALID = MAX_CHANNELS };
}

struct genode_packet
{
	short        *data;
	unsigned long size;
};

void   genode_audio_init(struct genode_env *env_ptr,
                         struct genode_allocator *alloc_ptr);

struct genode_packet genode_play_packet(void);

#ifdef __cplusplus
}
#endif

