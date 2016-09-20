#
# Common Function PORT - Makefile
#
# Copyright (c) 2012 Legate, Suzhou, China.
#
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# platform dependencies
# ---------------------------------------------------------------------------
CC	    = gcc
CXX	    = g++
AR      = ar

# ---------------------------------------------------------------------------
# project specifics
# ---------------------------------------------------------------------------
#set Debug or Release
#COMPILE_VARIABLE   = Debug

ifeq ($(COMPILE_VARIABLE),Debug)
CFLAGS	    += -g -Wall
else
CFLAGS	    += -O2 -Wall
endif
CFLAGS	    += -I./ -I../../Source/
CFLAGS      += -pthread

LDFLAGS     += -L../../Target/Ubuntu10.04.4/

TGT         = commonTest
CSRC        = 
CXXSRC      = ./main.cpp
ASRC        = 
OBJS        = $(CSRC:.c=.o)  $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)
BIN         = $(TGT)
LIBS        = -lcommon -lpthread -lrt

.PHONY: clean all

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f $(BIN)

# ---------------------------------------------------------------------------
# rules for code generation
# ---------------------------------------------------------------------------
%.o:    %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o:    %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

%.o:    %.S
	$(CC) $(ASFLAGS) -o $@ -c $<


