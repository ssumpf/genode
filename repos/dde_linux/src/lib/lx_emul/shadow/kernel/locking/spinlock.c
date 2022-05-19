/*
 * \brief  Replaces kernel/locking/spinlock.c
 * \author Stefan Kalkowski
 * \date   2021-03-16
 *
 * We run single-core, cooperatively scheduled. We should never spin.
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/spinlock.h>
#include <linux/rwlock_api_smp.h>
#include <asm/spinlock.h>

#include <lx_emul/debug.h>
#include <lx_emul/task.h>


void __lockfunc _raw_spin_lock(raw_spinlock_t * lock)
{
	arch_spin_lock(&lock->raw_lock);
//	if (atomic_read(SPINLOCK_VALUE_PTR(lock))) {
//		printk("Error: spinlock contention!");
//		lx_emul_trace_and_stop(__func__);
//	}
//	atomic_set(SPINLOCK_VALUE_PTR(lock), 1);
}


unsigned long __lockfunc _raw_spin_lock_irqsave(raw_spinlock_t * lock)
{
	unsigned long flags;
	local_irq_save(flags);
	_raw_spin_lock(lock);
	return flags;
}


void __lockfunc _raw_spin_unlock(raw_spinlock_t * lock)
{
	arch_spin_unlock(&lock->raw_lock);
	//atomic_set(SPINLOCK_VALUE_PTR(lock), 0);
}


void __lockfunc _raw_spin_unlock_irqrestore(raw_spinlock_t * lock,
                                            unsigned long flags)
{
	_raw_spin_unlock(lock);
	local_irq_restore(flags);
}


void __lockfunc _raw_spin_lock_irq(raw_spinlock_t * lock)
{
	_raw_spin_lock_irqsave(lock);
}


void __lockfunc _raw_spin_unlock_irq(raw_spinlock_t * lock)
{
	_raw_spin_unlock_irqrestore(lock, 0);
}


int __lockfunc _raw_spin_trylock(raw_spinlock_t * lock)
{
	arch_spin_trylock(&lock->raw_lock);
//	if (atomic_read(SPINLOCK_VALUE_PTR(lock)))
//		return 0;
//
//	_raw_spin_lock(lock);
//	return 1;
}


void __lockfunc _raw_write_lock(rwlock_t * lock)
{
	arch_write_lock(&(lock)->raw_lock);
//	if (RWLOCK_VALUE(lock)) {
//		printk("Error: rwlock contention!");
//		lx_emul_trace_and_stop(__func__);
//	}
//	RWLOCK_VALUE(lock) = 1;
}


void __lockfunc _raw_write_unlock(rwlock_t * lock)
{
	arch_write_unlock(&(lock)->raw_lock);
	//RWLOCK_VALUE(lock) = 0;
}
