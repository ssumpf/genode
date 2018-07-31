#include <base/log.h>

extern "C" {
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
}

#include <runtime/frame.inline.hpp>
#include <utilities/growableArray.hpp>

#include <os_bsd.hpp>


#define WARN_NOT_IMPL Genode::warning(__func__, " not implemented (jvm)");

typedef jlong load_long_func_t(volatile jlong*);
load_long_func_t* os::atomic_load_long_func;

typedef jint cmpxchg_func_t(jint, jint, volatile jint*);
cmpxchg_func_t* os::atomic_cmpxchg_func;

typedef jint  atomic_xchg_func_t(jint exchange_value, volatile jint *dest);
atomic_xchg_func_t * os::atomic_xchg_func;

typedef jlong cmpxchg_long_func_t(jlong, jlong, volatile jlong*);
cmpxchg_long_func_t* os::atomic_cmpxchg_long_func;

typedef jint  atomic_add_func_t(jint add_value, volatile jint *dest);
atomic_add_func_t * os::atomic_add_func;

typedef void store_long_func_t(jlong, volatile jlong*);
store_long_func_t* os::atomic_store_long_func;

size_t os::Posix::_vm_internal_thread_min_stack_allowed = 64 * K;
size_t os::Posix::_compiler_thread_min_stack_allowed = 64 * K;
size_t os::Posix::_java_thread_min_stack_allowed = 64 * K;

void os::print_context(outputStream* st, const void* context)
{
	WARN_NOT_IMPL;
}


void os::print_register_info(outputStream *st, const void *context)
{
	WARN_NOT_IMPL;
}


void os::initialize_thread(Thread* thr)
{
	WARN_NOT_IMPL;
}


void os::Bsd::init_thread_fpu_state()
{
	WARN_NOT_IMPL;
}


void os::setup_fpu()
{
	WARN_NOT_IMPL;
}


char* os::non_memory_address_word()
{
	WARN_NOT_IMPL;
	return (char*)-1;
}


bool os::is_allocatable(size_t bytes)
{
	WARN_NOT_IMPL;
	return false;
}


int os::extra_bang_size_in_bytes()
{
	WARN_NOT_IMPL;
	return 0;
}


frame os::current_frame()
{
	WARN_NOT_IMPL;
	return frame();
}


frame os::get_sender_for_C_frame(frame* fr)
{
	WARN_NOT_IMPL;
	return frame();
}


frame os::fetch_frame_from_context(const void* ucVoid)
{
	WARN_NOT_IMPL;
	return frame();
}


size_t os::current_stack_size()
{
	WARN_NOT_IMPL;
	return 0;
}


void os::verify_stack_alignment()
{
	WARN_NOT_IMPL;
}


address os::current_stack_pointer()
{
	WARN_NOT_IMPL;
	return 0;
}


address os::current_stack_base()
{
	WARN_NOT_IMPL;
	return 0;
}

/**
 * POSIX
 */

size_t os::Posix::default_stack_size(os::ThreadType thr_type)
{
	WARN_NOT_IMPL;
	return 0;
}


/**
 * BSD
 */

void os::Bsd::ucontext_set_pc(ucontext_t * uc, address pc)
{
	WARN_NOT_IMPL;
}


address os::Bsd::ucontext_get_pc(const ucontext_t* uc)
{
	WARN_NOT_IMPL;
	return 0;
}


void VM_Version::get_os_cpu_info()
{
	WARN_NOT_IMPL;
}

void VM_Version::early_initialize()
{
	WARN_NOT_IMPL;
}


extern "C" JNIEXPORT int
JVM_handle_bsd_signal(int sig,
                      siginfo_t* info,
                      void* ucVoid,
                      int abort_if_unrecognized)
{
	WARN_NOT_IMPL;
	return -1;
}


/**
 * JavaThread
 */
bool JavaThread::pd_get_top_frame_for_signal_handler(frame* fr_addr,
                                                      void* ucontext, bool isInJava)
{
	WARN_NOT_IMPL;
	return false;
}


void JavaThread::cache_global_variables()
{
	WARN_NOT_IMPL;
}


