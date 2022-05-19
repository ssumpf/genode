#include <genode_c_api/base.h>

#ifdef __cplusplus
extern "C" {
#endif

struct genode_packet
{
	short        *data;
	unsigned long size;
};

void   genode_audio_init(struct genode_env *env_ptr,
                         struct genode_allocator *alloc_ptr);

struct genode_packet genode_play_packet(void);

unsigned long genode_audio_period(void);

#ifdef __cplusplus
}
#endif

