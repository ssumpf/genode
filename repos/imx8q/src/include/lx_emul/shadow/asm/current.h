/**
 * \brief  Shadow copy of asm/current.h
 * \author Josef Soentgen
 * \date   2021-04-07
 */

#pragma once

struct task_struct;

/*
 * The original implementation used inline assembly we for obvious
 * reason cannot use.
 */
struct task_struct *get_current(void);

#define current get_current()
