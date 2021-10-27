all: hipoMachine.c functions
	gcc $< instructions.h -o machine

functions: instructions.h
	gcc -c -O2 instructions.h

clear: 
	rm instructions.h.gch

program_writer: write_program.c
	gcc write_program.c -o write_program
