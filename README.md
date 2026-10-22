# BVS1 – Betriebssysteme: Course Code

This is the student code repository for **BVS1 – Betriebssysteme** at TH Köln, ICCT.

## Exercise 02 — Using Your First Process

This branch provides a **precompiled process implementation** so you can define and use its C interface before implementing the abstraction yourself for Checkpoint 1.

Provided:

- `lib/libprocess.a`: a precompiled RV64 implementation of `process_create()`, `process_run()`, `process_yield()`, and `process_exit()`;
- `context.h` and `context.S`: the visible low-level context-switch boundary;
- startup, linker, UART, build, and QEMU support.

Not provided:

- the C source that implements the process API.

There is intentionally **no `process.h` and no `process.c` implementation** on this branch. You create the public header during Exercise 02; the implementation is linked from `lib/libprocess.a`.

The exercise asks you to write an entry function and helper that perform a deterministic permutation of a local character array, yield while the helper is active, resume the same execution, and print the resulting permutation.

Use:

```bash
make
make run
```


For Checkpoint 1, the provided process library disappears and you implement the C-level process abstraction yourself around the same provided `context_switch()`.

## Course Workflow

Clone this repository **once** inside the Ubuntu 26.04 course VM:

```bash
git clone https://github.com/stavroskousidis/teaching-bvs1-code.git
cd teaching-bvs1-code
```

Recommended Exercise 02 workflow:

```bash
git fetch origin
git switch exercise/02-process-use
git switch -c exercise-02
```

Keep your local semester repository and commit meaningful working states. Do not push student work to the course repository.

Local Git history is **not a backup**. Keep regular copies or a Git bundle outside the course VM, especially before checkpoints.

## Build and Run

```bash
make check
make
make run
```

Exit QEMU with **Ctrl-a**, release the keys, then press **x**.

Useful inspection targets:

```bash
make inspect
make disasm
```

Generated files are written to `build/`.

## Environment

The supported development environment is the course-provided Ubuntu 26.04 VM named `bvs1`. Complete Lab 0 before using this repository.

Inside that VM:

- Git and Make manage the local code and build;
- the RISC-V cross-toolchain produces RV64 code;
- QEMU emulates the RV64 `virt` teaching machine.
