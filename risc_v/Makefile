default: hello.elf
hello.o : hello.c
	riscv64-unknown-elf-gcc -c -g -O0 -ffreestanding -march=rv32i -mabi=ilp32 -o hello.o hello.c

	#In case of bare metal applications no standard libs,no startup files 
	#can also use nostdlib
	#specify the arch and abi flags -> arch+ilp

start.o: start.s
	#output the o file by taking in the s file
	riscv64-unknown-elf-as -march=rv32i -mabi=ilp32 -o start.o start.s
hello.elf : hello.o start.o baremetal.ld
	riscv64-unknown-elf-ld -T baremetal.ld -m elf32lriscv -o hello.elf hello.o start.o
	#output the elf and input the object files
run: hello.elf
	@echo "Ctrl-A C for qemu console , thes quit to exit"
	#redirect the serial port to my host terminal
	qemu-system-riscv32 -nographic -serial mon:stdio -machine virt -bios hello.elf
	#fake machine with bios flag -->Serial port
clean: 
	rm -f hello.o hello.elf start.o