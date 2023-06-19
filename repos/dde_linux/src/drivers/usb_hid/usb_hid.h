#include <usb_client.h>

#ifdef __cplusplus
extern "C" {
#endif


unsigned long lx_usb_register_device(genode_usb_client_handle_t handle);

struct task_struct;

int                 lx_user_main_task(void *);
struct task_struct *lx_user_new_usb_task(int (*func)(void*), void *args);
void                lx_user_destroy_usb_task(struct task_struct*);



#ifdef __cplusplus
} /* extern "C" */
#endif


