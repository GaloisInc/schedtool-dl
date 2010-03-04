/*
 this sticks around for documentation issues only and will be removed in the next
 release - it documents the direct syscalls for affinity, without going thru glibc
 */

#if 0

/* 
 I don't know where this was exactly taken from, but I think I found it
 in glibc.
 */
#include <linux/unistd.h>
#define __NR_sched_setaffinity	241
#define __NR_sched_getaffinity	242

/*
 a nice macro to define the following:
 it's a syscall with 3 args,
 it returns int,
 it's named sched_....,
 the next arg is of type pid_t,
 has the local name pid,
 next is unsigned int,
 with name len,
 then an unsigned long *,
 named user_mask_ptr
 */
_syscall3 (int, sched_setaffinity, pid_t, pid, unsigned int, len, unsigned long *, user_mask_ptr)
_syscall3 (int, sched_getaffinity, pid_t, pid, unsigned int, len, unsigned long *, user_mask_ptr)

#endif

#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <time.h>

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setscheduler_ex	303
#define __NR_sched_getparam_ex		305
#endif

#ifdef __i386__
#define __NR_sched_setscheduler_ex	341
#define __NR_sched_getparam_ex		343
#endif

#ifdef __arm__
#define __NR_sched_setscheduler_ex	370
#define __NR_sched_getparam_ex		372
#endif

#define SF_SIG_RORUN	2
#define SF_SIG_DMISS	4

struct sched_param_ex {
	int sched_priority;
	struct timespec sched_runtime;
	struct timespec sched_deadline;
	struct timespec sched_period;
	unsigned int sched_flags;
	struct timespec curr_runtime;
	struct timespec used_runtime;
	struct timespec curr_deadline;
};

#define sched_setscheduler_ex(pid, policy, len, param) \
	syscall(__NR_sched_setscheduler_ex, pid, policy, len, param)

#define sched_getparam_ex(pid, len, param) \
	syscall(__NR_sched_getparam_ex, pid, len, param)


