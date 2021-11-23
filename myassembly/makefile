hello1:
	nasm -f elf hello1.asm
	ld -m elf_i386 -s -o hello1 hello1.o

runhello1:
	./hello1

readonlyhello1:
	#view hello1.asm
	cat hello1.asm

hello2:
	nasm -f elf hello2.asm
	ld -m elf_i386 -s -o hello2 hello2.o

runhello2:
	./hello2

backward2:
	nasm -f elf backward2.asm
	ld -m elf_i386 -s -o backward2 backward2.o
runbackward2:
	./backward

backward:
	nasm -f elf backward.asm
	ld -m elf_i386 -s -o backward backward.o

runbackward2:
	./backward

clean:
	find . -maxdepth 1 -type f -executable -delete
