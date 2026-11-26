/*
 * Exercise 06: the scheduling decision. You write schedule().
 *
 * The provided libkernel.a calls schedule() whenever the running process
 * gives up the CPU (timer interrupt, exit, unexpected trap) and
 * once in os_run() for the first start. scheduler.h describes the
 * arguments and what the function must return.
 */

#include <stddef.h>

#include "scheduler.h"

struct process *schedule(struct process *const table[], unsigned int count,
                         struct process *current)
{
    (void)table;
    (void)count;
    (void)current;

    /* TODO (Exercise 06): return the next READY process, round robin. */
    return NULL;
}
