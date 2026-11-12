CROSS ?= riscv64-unknown-elf-
CC := $(CROSS)gcc
OBJDUMP := $(CROSS)objdump
SIZE := $(CROSS)size
QEMU ?= qemu-system-riscv64

BUILD_DIR := build
ELF := $(BUILD_DIR)/hello-bvs1.elf
MAP := $(BUILD_DIR)/hello-bvs1.map
DISASM := $(BUILD_DIR)/hello-bvs1.disasm

# Exercise 05 provides the OS as precompiled RV64 libraries. KERNEL selects
# the one to link:
#   ex05  lib/libkernel.a             timer on, one line per tick (default)
#   ex04  lib/libkernel-ex04.a        the Exercise 04 OS, no timer
#   a     lib/broken/libkernel-a.a    broken library A (Task 5)
#   b     lib/broken/libkernel-b.a    broken library B (Task 5)
#   c     lib/broken/libkernel-c.a    broken library C (Task 5)
KERNEL ?= ex05
KERNEL_LIB_ex05 := lib/libkernel.a
KERNEL_LIB_ex04 := lib/libkernel-ex04.a
KERNEL_LIB_a := lib/broken/libkernel-a.a
KERNEL_LIB_b := lib/broken/libkernel-b.a
KERNEL_LIB_c := lib/broken/libkernel-c.a
KERNEL_LIBS := $(KERNEL_LIB_ex05) $(KERNEL_LIB_ex04) $(KERNEL_LIB_a) $(KERNEL_LIB_b) $(KERNEL_LIB_c)
KERNEL_LIB := $(KERNEL_LIB_$(KERNEL))
ifeq ($(KERNEL_LIB),)
$(error KERNEL must be one of ex05, ex04, a, b, c)
endif

# Reproducible timer interrupts (Lecture 6): QEMU's virtual time advances
# by 16 ns per executed instruction. Run without it with: make run ICOUNT=
ICOUNT ?= -icount shift=4,sleep=off

# trap.S stays visible because the trap path and the return path are course
# material. Student C files remain ordinary sources at the repo root.
C_SOURCES := $(sort $(wildcard *.c))
ASM_SOURCES := start.S trap.S
HEADERS := $(sort $(wildcard *.h))
SOURCES := $(ASM_SOURCES) $(C_SOURCES)

CFLAGS := \
	-march=rv64imac_zicsr \
	-mabi=lp64 \
	-mcmodel=medany \
	-msmall-data-limit=0 \
	-ffreestanding \
	-fno-builtin \
	-fno-stack-protector \
	-fno-pie \
	-fno-asynchronous-unwind-tables \
	-Wall \
	-Wextra \
	-Werror \
	-O2

LDFLAGS := \
	-nostdlib \
	-nostartfiles \
	-no-pie \
	-T linker.ld \
	-Wl,--build-id=none \
	-Wl,-Map,$(MAP)

.PHONY: all check run inspect disasm clean FORCE

all: check $(ELF)
	@$(SIZE) $(ELF)

check:
	@echo "Checking BVS1 environment..."
	@command -v $(CC) >/dev/null 2>&1 || { echo "Missing tool: $(CC)"; exit 1; }
	@command -v $(OBJDUMP) >/dev/null 2>&1 || { echo "Missing tool: $(OBJDUMP)"; exit 1; }
	@command -v $(SIZE) >/dev/null 2>&1 || { echo "Missing tool: $(SIZE)"; exit 1; }
	@command -v $(QEMU) >/dev/null 2>&1 || { echo "Missing tool: $(QEMU)"; exit 1; }
	@command -v file >/dev/null 2>&1 || { echo "Missing tool: file"; exit 1; }
	@for lib in $(KERNEL_LIBS); do \
		test -f $$lib || { echo "Missing provided kernel library: $$lib"; exit 1; }; \
	done
	@$(QEMU) --machine help | grep -q "virt" || { echo "QEMU does not provide the RISC-V virt machine."; exit 1; }
	@echo "Environment OK."

$(BUILD_DIR):
	mkdir -p $@

# Relink when KERNEL changes, so that the ELF always contains the library
# of the last make or make run.
$(BUILD_DIR)/kernel: FORCE | $(BUILD_DIR)
	@echo "$(KERNEL)" | cmp -s - $@ || echo "$(KERNEL)" > $@

$(ELF): $(SOURCES) $(HEADERS) $(KERNEL_LIB) linker.ld $(BUILD_DIR)/kernel | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) $(KERNEL_LIB) -o $@


run: all
	@echo "Starting bare RV64 machine with $(KERNEL_LIB). Exit QEMU with Ctrl-a, then x."
	$(QEMU) \
		-machine virt \
		-m 128M \
		-smp 1 \
		-nographic \
		-bios none \
		$(ICOUNT) \
		-kernel $(ELF)

inspect: all
	@echo "ELF:"
	@file $(ELF)
	@echo
	@echo "Sections:"
	@$(OBJDUMP) -h $(ELF)

disasm: all
	$(OBJDUMP) -d -S $(ELF) > $(DISASM)
	@echo "Wrote $(DISASM)"

clean:
	rm -rf $(BUILD_DIR)
