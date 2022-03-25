
RISCV_GCC ?= riscv64-unknown-elf-gcc
RISCV_GCC_OPTS ?= \
				-DPREALLOCATE=1 -mcmodel=medany -static \
				-march=rv32i -mabi=ilp32 \
				-std=gnu99 \
				-Og \
				-ffast-math -fno-common -fno-builtin-printf

RISCV_LINK_OPTS ?= -g -static -nostartfiles -lm -lgcc -T common/link.ld

all: cheese1.riscv cheese2.riscv

cheese1.riscv: cheese.c common/syscall.c common/crt.S
	$(RISCV_GCC) -I common $(RISCV_GCC_OPTS) $(RISCV_LINK_OPTS) -o $@ cheese.c common/syscall.c common/crt.S

cheese2.riscv: cheese.c common/sbrk_only.c common/start.S
	$(RISCV_GCC) -O0 -march=rv32i -mabi=ilp32 -nostartfiles -Wl,-Ttext=0x80000100 -o $@ cheese.c common/sbrk_only.c common/start.S

clean:
	-rm -f cheese1.riscv cheese2.riscv

