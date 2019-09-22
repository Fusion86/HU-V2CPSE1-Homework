#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source & header files in this project (main.cpp is automatically assumed)

HEADERS += note.hpp
HEADERS += note_player.hpp

HEADERS += note_player_gpio.hpp
SOURCES += note_player_gpio.cpp

HEADERS += rtttl_player.hpp
SOURCES += rtttl_player.cpp my_melody.cpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due

all: my_melody.cpp main.cpp
	make # Uses Makefile

clean:
	rm -f *.o *.elf *.map *.ld *.bin bmptk_fixed_size_stack.c generator my_melody.cpp

my_melody.cpp: generator
	./generator my_melody.cpp

generator: generator.cpp rtttl_player.cpp notes_to_cpp.cpp
	g++ -std=c++17 generator.cpp rtttl_player.cpp notes_to_cpp.cpp -o generator
