#include <lx_emul/usb_client.h>

#ifdef __cplusplus
extern "C" {
#endif

struct task_struct;

int                 lx_user_main_task(void *);
struct task_struct *lx_user_new_usb_task(int (*func)(void*), void *args);


#ifdef __cplusplus
} /* extern "C" */
#endif


