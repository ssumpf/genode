#include <genode_c_api/usb_client.h>

#ifdef __cplusplus
extern "C" {
#endif

void *lx_emul_usb_client_register_device(genode_usb_client_handle_t handle, char const *label);
void  lx_emul_usb_client_unregister_device(genode_usb_client_handle_t handle, void *data);

#ifdef __cplusplus
} /* extern "C" */
#endif
