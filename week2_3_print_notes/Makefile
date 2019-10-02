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
HEADERS += melody.hpp
HEADERS += note_player.hpp
HEADERS += fur_elise.hpp

HEADERS += rtttl_player.hpp note_printer.hpp
SOURCES += rtttl_player.cpp note_printer.cpp note.cpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
