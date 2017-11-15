include $(REP_DIR)/lib/mk/rump2.inc

LIBS        += rump2 rump2tools
SHARED_LIB   = yes
RUMP_FS_BASE = $(BUILD_BASE_DIR)/var/libcache/rump2_fs
NBCONFIG     = $(BUILD_BASE_DIR)/var/libcache/rump2tools/bin/nbconfig


#
# librumpdev.a
#
SRC_C = autoconf.c kern_pmf.c rump_dev.c subr_autoconf.c

INC_DIR += $(RUMP_BASE) \
           $(RUMP_FS_BASE) \
           $(RUMP_PORT_DIR)/src/common/include \
           $(RUMP_PORT_DIR)/src/sys \
           $(RUMP_PORT_DIR)/src/sys/rump/librump/rumpkern \
           $(RUMP_PORT_DIR)/src/sys/rump/librump/rumpdev/opt \
           $(RUMP_PORT_DIR)/src/sys/rump/include \
           $(RUMP_PORT_DIR)/src/sys/sys

ioconf.c:
	$(NBCONFIG) -b $(RUMP_FS_BASE) -s $(RUMP_PORT_DIR)/src/sys \
		$(RUMP_PORT_DIR)/src/sys/rump/librump/rumpdev/MAINBUS.ioconf

autoconf.o: ioconf.c


vpath %.c $(RUMP_PORT_DIR)/src/sys/kern
vpath %.c $(RUMP_PORT_DIR)/src/sys/rump/librump/rumpdev


#
# librumpdev_disk.a
#
SRC_C += dk.c dksubr.c subr_disk.c subr_disk_mbr.c subr_disk_open.c

vpath %.c $(RUMP_PORT_DIR)/src/sys/dev
vpath %.c $(RUMP_PORT_DIR)/src/sys/dev/dkwedge


#
# librumpvfs.a
#
SRC_C += bufq_disksort.c compat.c devnull.c genfs_vfsops.c \
         kern_physio.c rumpfs.c rumpvnode_if.c sync_subr.c \
         vfs_cache.c vfs_hooks.c vfs_mount.c vfs_syscalls.c vfs_wapbl.c \
         bufq_fcfs.c dead_vfsops.c firmload.c genfs_vnops.c \
         mfs_miniroot.c rumpvfs_if_wrappers.c spec_vnops.c sync_vnops.c vfs_cwd.c \
         vfs_init.c vfs_quotactl.c vfs_trans.c vfs_xattr.c \
         bufq_priocscan.c dead_vnops.c genfs_io.c kern_ktrace_vfs.c \
         quota1_subr.c rump_vfs.c subr_bufq.c uvm_vnode.c \
         vfs_dirhash.c vfs_lockf.c vfs_subr.c vfs_vnode.c vm_vfs.c \
         bufq_readprio.c devnodes.c genfs_rename.c kern_module_vfs.c rumpblk.c \
         rumpvfs_syscalls.c subr_kobj_vfs.c vfs_bio.c vfs_getcwd.c \
         vfs_lookup.c vfs_syscalls_50.c vfs_vnops.c


INC_DIR += $(RUMP_PORT_DIR)/src/sys/rump/librump/rumpkern/opt

vpath %.c $(RUMP_PORT_DIR)/src/sys/compat/common
vpath %.c $(RUMP_PORT_DIR)/src/sys/rump/librump/rumpvfs
vpath %.c $(RUMP_PORT_DIR)/src/sys/miscfs/deadfs
vpath %.c $(RUMP_PORT_DIR)/src/sys/miscfs/genfs
vpath %.c $(RUMP_PORT_DIR)/src/sys/miscfs/specfs
vpath %.c $(RUMP_PORT_DIR)/src/sys/miscfs/syncfs
vpath %.c $(RUMP_PORT_DIR)/src/sys/ufs/mfs
vpath %.c $(RUMP_PORT_DIR)/src/sys/ufs/ufs
vpath %.c $(RUMP_PORT_DIR)/src/sys/uvm

#
# librump_ufs.a
#
SRC_C += ufs_bmap.c ufs_inode.c ufs_lookup.c ufs_vfsops. ufs_vnops


#
# librumpfs_ext2fs.a
#
SRC_C += ext2fs_alloc.c ext2fs_balloc.c ext2fs_bmap.c ext2fs_bswap.c ext2fs_inode.c \
         ext2fs_lookup.c ext2fs_readwrite.c ext2fs_rename.c ext2fs_subr.c \
         ext2fs_vfsops.c ext2fs_vnops

vpath %.c $(RUMP_PORT_DIR)/src/sys/ufs/ext2fs
