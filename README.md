
A simple "hello world" program for riscv

Prerequisites:
 - `riscv32-unknown-elf-gcc`
 - `spike`

## Instructions

 - Run `make`. This should build `demo.riscv`
 - Run `make run`. This will run `demo.riscv` on a simulated rv32ia architecture. This corresponds to the `-march=rv32ia -mabi=ilp32` flags in the Makefile.

## Credits

 - https://github.com/riscv-software-src/riscv-tests/tree/master/benchmarks/common
 - https://github.com/lsk567/lf-flexpret-scripts/tree/15eb04548a9696d13fa451b16a4b0814b3f53989/lib


