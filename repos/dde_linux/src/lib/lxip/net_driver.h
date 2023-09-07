#ifndef _NET_DRIVER_H_
#define _NET_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif
	struct task_struct;
	struct task_struct *lx_nic_client_rx_task(void);
#ifdef __cplusplus
}
#endif

#endif /* _NET_DRIVER_H_ */
