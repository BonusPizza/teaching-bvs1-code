# BVS1 – Betriebssysteme: Course Code

This is the student code repository for **BVS1 – Betriebssysteme** at TH Köln, ICCT.

## Exercise 05 — The Timer Path

This branch runs your Exercise 04 application against an OS that takes timer interrupts (Lecture 6). A process that never yields now loses the CPU every time slice: the CLINT requests a timer interrupt, the CPU enters the same trap path as for an `ecall`, and the OS gets control back without the process's help.

Provided:

- `lib/libkernel.a`: the Exercise 05 OS: it arms the timer, takes timer interrupts and prints one line per tick (`os: tick N at <pc> in process 1`);
- `lib/libkernel-ex04.a`: the Exercise 04 OS, without the timer, for comparison;
- `lib/broken/libkernel-a.a`, `libkernel-b.a`, `libkernel-c.a`: three OS libraries with one defect each in their timer path (Task 5);
- `riscv.h`: CSR access, `mcause` codes, and the CLINT timer (`timer_now()`, `timer_arm(delta)`);
- `trap.h`, `trap.S`, `syscall.h`, `syscall.c`, `uart.h`, `uart.c`: unchanged from Exercise 04;
- startup, linker, build, and QEMU support. `make run` starts QEMU with `-icount shift=4,sleep=off`, so that timer interrupts land at the same instructions in every run.

Not provided: `process.h`; you bring it, together with your `main.c`, from your Exercise 04 work branch. The sheet tells you which process to add to `main.c`.

Bring your Exercise 04 files onto a local work branch:

```bash
git fetch origin
git switch exercise/05-timer
git switch -c exercise-05
git checkout exercise-04 -- process.h main.c
```

Do not bring a `process.c`: the Makefile compiles every root-level C file, and a second process implementation clashes with the provided library.

Choose the OS library with `KERNEL`; the program is relinked when it changes:

```bash
make run                 # Exercise 05 library
make run KERNEL=ex04     # Exercise 04 library
make run KERNEL=a        # broken library A (also b, c)
make run ICOUNT=         # without -icount: QEMU follows host time
```

For Checkpoint 2, the provided kernel library disappears and you implement the OS side yourself around the same provided `trap.S`, including the timer and a scheduler.

## Course Workflow

Clone this repository **once** inside the Ubuntu 26.04 course VM:

```bash
git clone https://github.com/stavroskousidis/teaching-bvs1-code.git
cd teaching-bvs1-code
```

Recommended Exercise 05 workflow:

```bash
git fetch origin
git switch exercise/05-timer
git switch -c exercise-05
```

Keep your local semester repository and commit meaningful working states. Do not push student work to the course repository.

Local Git history is **not a backup**. Keep regular copies or a Git bundle outside the course VM, especially before checkpoints.

## Build and Run

```bash
make check
make
make run
```

`make run` uses the library selected by `KERNEL` (default: `ex05`). Exit QEMU with **Ctrl-a**, release the keys, then press **x**.

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
