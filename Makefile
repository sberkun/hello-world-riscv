
XLEN ?= 64


src_dir = common

RISCV_PREFIX ?= riscv$(XLEN)-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc

RISCV_GCC_OPTS ?= \
				-DPREALLOCATE=1 -mcmodel=medany -static \
				-march=rv32i -mabi=ilp32 \
				-std=gnu99 \
				-Og \
				-ffast-math -fno-common -fno-builtin-printf

RISCV_LINK ?= $(RISCV_GCC) -T $(src_dir)/link.ld $(incs)
RISCV_LINK_OPTS ?= -g -static -nostartfiles -lm -lgcc -T $(src_dir)/link.ld

RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data

incs  += -I $(src_dir)

demo.riscv: $(wildcard ./*.c) $(src_dir)/syscall.c $(src_dir)/crt.S
	$(RISCV_GCC) $(incs) $(RISCV_GCC_OPTS) $(RISCV_LINK_OPTS) -o $@ $^

demo.dump: demo.riscv
	$(RISCV_OBJDUMP) $< > $@

demo.dump.annot: demo.riscv
	$(RISCV_OBJDUMP) -S $< > $@

all: demo.riscv demo.dump demo.dump.annot

clean:
	-rm -f *.riscv *.dump *.dump.annot


