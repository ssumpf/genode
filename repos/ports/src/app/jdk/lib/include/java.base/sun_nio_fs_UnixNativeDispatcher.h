/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class sun_nio_fs_UnixNativeDispatcher */

#ifndef _Included_sun_nio_fs_UnixNativeDispatcher
#define _Included_sun_nio_fs_UnixNativeDispatcher
#ifdef __cplusplus
extern "C" {
#endif
#undef sun_nio_fs_UnixNativeDispatcher_SUPPORTS_OPENAT
#define sun_nio_fs_UnixNativeDispatcher_SUPPORTS_OPENAT 2L
#undef sun_nio_fs_UnixNativeDispatcher_SUPPORTS_FUTIMES
#define sun_nio_fs_UnixNativeDispatcher_SUPPORTS_FUTIMES 4L
#undef sun_nio_fs_UnixNativeDispatcher_SUPPORTS_BIRTHTIME
#define sun_nio_fs_UnixNativeDispatcher_SUPPORTS_BIRTHTIME 65536L
/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    getcwd
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_getcwd
  (JNIEnv *, jclass);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    dup
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_dup
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    open0
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_open0
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    openat0
 * Signature: (IJII)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_openat0
  (JNIEnv *, jclass, jint, jlong, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    close0
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_close0
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fopen0
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fopen0
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fclose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fclose
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    link0
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_link0
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    unlink0
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_unlink0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    unlinkat0
 * Signature: (IJI)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_unlinkat0
  (JNIEnv *, jclass, jint, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    mknod0
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_mknod0
  (JNIEnv *, jclass, jlong, jint, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    rename0
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_rename0
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    renameat0
 * Signature: (IJIJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_renameat0
  (JNIEnv *, jclass, jint, jlong, jint, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    mkdir0
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_mkdir0
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    rmdir0
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_rmdir0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    readlink0
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_readlink0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    realpath0
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_realpath0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    symlink0
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_symlink0
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    stat0
 * Signature: (JLsun/nio/fs/UnixFileAttributes;)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_stat0
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    stat1
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_stat1
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    lstat0
 * Signature: (JLsun/nio/fs/UnixFileAttributes;)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_lstat0
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fstat
 * Signature: (ILsun/nio/fs/UnixFileAttributes;)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fstat
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fstatat0
 * Signature: (IJILsun/nio/fs/UnixFileAttributes;)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fstatat0
  (JNIEnv *, jclass, jint, jlong, jint, jobject);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    chown0
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_chown0
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    lchown0
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_lchown0
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fchown
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fchown
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    chmod0
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_chmod0
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fchmod
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fchmod
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    utimes0
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_utimes0
  (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    futimes
 * Signature: (IJJ)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_futimes
  (JNIEnv *, jclass, jint, jlong, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    opendir0
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_sun_nio_fs_UnixNativeDispatcher_opendir0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fdopendir
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fdopendir
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    closedir
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_closedir
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    readdir
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_readdir
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    read
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_read
  (JNIEnv *, jclass, jint, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    write
 * Signature: (IJI)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_write
  (JNIEnv *, jclass, jint, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    access0
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_access0
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    exists0
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_sun_nio_fs_UnixNativeDispatcher_exists0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    getpwuid
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_getpwuid
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    getgrgid
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_getgrgid
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    getpwnam0
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_getpwnam0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    getgrnam0
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_getgrnam0
  (JNIEnv *, jclass, jlong);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    statvfs0
 * Signature: (JLsun/nio/fs/UnixFileStoreAttributes;)V
 */
JNIEXPORT void JNICALL Java_sun_nio_fs_UnixNativeDispatcher_statvfs0
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    pathconf0
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_sun_nio_fs_UnixNativeDispatcher_pathconf0
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    fpathconf
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_sun_nio_fs_UnixNativeDispatcher_fpathconf
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    strerror
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_sun_nio_fs_UnixNativeDispatcher_strerror
  (JNIEnv *, jclass, jint);

/*
 * Class:     sun_nio_fs_UnixNativeDispatcher
 * Method:    init
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_sun_nio_fs_UnixNativeDispatcher_init
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
