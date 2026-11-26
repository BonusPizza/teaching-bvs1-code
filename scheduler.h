#ifndef BVS1_SCHEDULER_H
#define BVS1_SCHEDULER_H

#include "process.h"

/*
 * Exercise 6 interface: the scheduling decision.
 *
 * The Exercise 6 libkernel.a handles every trap itself (system calls,
 * timer re-arm, unexpected traps, process states) and asks this function
 * only one question: which process runs next? You write it in C.
 *
 * The OS calls schedule() whenever the running process gives up the CPU:
 * after a timer interrupt, an exit or an unexpected trap, and once in
 * os_run() for the first start. At the call
 *
 *   table[0] .. table[count - 1]  are the processes in creation order;
 *   current                       is the process that just ran, already
 *                                 READY (timer) or FINISHED (exit,
 *                                 fault); NULL if no process of the table
 *                                 ran (first start, or the idle process).
 *
 * Return a READY process from the table. Return NULL if no process is
 * READY: the OS then runs its idle process. The OS marks the returned
 * process RUNNING and restores its frame; schedule() changes no state.
 */
struct process *schedule(struct process *const table[], unsigned int count,
                         struct process *current);

#endif
