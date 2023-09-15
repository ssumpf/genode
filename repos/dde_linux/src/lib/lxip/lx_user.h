#ifdef __cplusplus
extern "C" {
#endif

struct task_struct;

int lx_user_startup_complete(void *);

void  *lx_socket_dispatch_queue(void);
int    lx_socket_dispatch(void *arg);
struct task_struct *lx_socket_dispatch_root(void);

struct task_struct *lx_user_new_task(int (*func)(void*), void *args);
void                lx_user_destroy_task(struct task_struct *task);

#ifdef __cplusplus
}
#endif
