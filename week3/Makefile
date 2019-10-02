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
SOURCES := clock.cpp

# header files in this project
HEADERS := clock.hpp

# other places to look for files for this project
SEARCH  :=

# we can use this file to verify that our constexpr are indeed compile time
RESULTS := clock.lst

# set RELATIVE to the next higher directory
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
