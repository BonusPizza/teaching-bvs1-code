/*
 * Checkpoint 2: the OS. You write this file.
 *
 * After main() calls os_run(), the OS runs only inside trap_handler():
 * every entry into the OS is a trap, and the handler returns the frame
 * that the provided return path restores (trap.S, os_start).
 *
 * The Checkpoint 2 sheet, section "Required Semantics", lists what each
 * function must do. You may add static helper functions and data in this
 * file. The bodies below only let the scaffold build; replace them.
 */

#include <stddef.h>
#include <stdint.h>

#include "process.h"
#include "riscv.h"
#include "scheduler.h"
#include "syscall.h"
#include "trap.h"
#include "uart.h"

/*
 * Prepare a process without running it and enter it in the process
 * table: owned stack, first frame (pc, sp), READY.
 */
void process_create(struct process *process, process_entry_t entry)
{
    (void)process;
    (void)entry;
    /* TODO (CP2) */
}

/*
 * The OS: called by trap_entry with the frame of the interrupted process.
 * Handles ecall (exit), the timer interrupt and unexpected traps,
 * then returns the frame to restore.
 */
struct trap_frame *trap_handler(struct trap_frame *trapped)
{
    /* TODO (CP2) */
    return trapped;
}

/*
 * The hand-over from start-up: mtvec, timer, first process, os_start().
 * Never returns.
 */
void os_run(void)
{
    /* TODO (CP2) */
    for (;;) {
    }
}
