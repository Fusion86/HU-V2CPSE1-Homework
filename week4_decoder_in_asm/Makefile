#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := compressed_data.asm

# header files in this project
HEADERS :=

# other places to look for files for this project
SEARCH  :=

# other files to create
RESULTS :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := ..
include $(RELATIVE)/Makefile.due

clean:
	rm -f *.o *.elf *.map *.ld *.bin bmptk_fixed_size_stack.c generator compressed_data.asm

generator: generator.cpp
	g++ -std=c++17 generator.cpp -o generator

compressed_data.asm: generator
	./generator
