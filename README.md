# BVS1 – Betriebssysteme: Course Code

This branch is the **Checkpoint 1 process scaffold**.

## What is provided

- `start.S` and `linker.ld`;
- UART string output in the starter;
- `context.h`: the saved RV64 CPU context representation;
- `context.S`: the provided `context_switch(current_context, next_context)`;
- Make/QEMU integration.

## What is deliberately not provided

There is no:

- `process.h`;
- `process.c`;
- `libprocess.a`;
- implementation of `process_create()`, `process_run()`, `process_yield()`, or `process_exit()`.

For Checkpoint 1, the C-level process abstraction is your work.

Reuse the `process.h` that you created in Exercise 02 and implement its process API in `process.c`. Then reuse your Exercise 02 permutation application unchanged: with the provided library removed, the same application should run against your own implementation.

The build automatically compiles C files that you add at the repository root, so adding `process.c` and `process.h` does not require changing the source list.

## Build and run

```bash
make check
make
make run
```

Exit QEMU with **Ctrl-a**, release the keys, then press **x**.

The mandatory checkpoint is an individual demonstration: your process must yield, resume the same execution, finish, and return control to the operating system. You must also be able to explain how your implementation uses the provided context-switch boundary.

## Environment

Use the course-provided Ubuntu 26.04 VM.
