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
SOURCES := SI7021.cpp SSD1306.cpp

# header files in this project
HEADERS := SI7021.h SSD1306.h

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory 
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
