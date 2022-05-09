
#ifdef __cplusplus
extern "C" {
#endif
	void *lx_vmap_create(unsigned size);
	void  lx_vmap_destroy(void *vmap);
	int   lx_vmap_attach(void *vmap, void *virt_addr, unsigned long offset);
	void *lx_vmap_address(void *vmap);
#ifdef __cplusplus
}
#endif

