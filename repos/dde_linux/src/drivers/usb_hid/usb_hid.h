
#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long genode_usb_device;

genode_usb_device genode_register_device(void *device_descriptor, void *controller,
                                         unsigned num, unsigned speed);

#ifdef __cplusplus
} /* extern "C" */
#endif


