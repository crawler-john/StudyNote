# TAM DL PORT - Makefile
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
CFLAGS	    += -O2 -Wall -DNDEBUG

CFLAGS	    += -I../../Source/

# here to add "-Wl,-Bsymbolic" to avoid symbolic confilict in different 
# libraries in using same variable or function names
LDFLAGS     += -Wl,-Bsymbolic -fPIC -shared 
TGT         = $$PWD/../../Target/XP/libcommon.a


#CSRC        = ../../Source/wcemmtimer.c
CXXSRC      = ../../Source/event.cpp \
              ../../Source/goodies.cpp \
			  ../../Source/msgQueue.cpp \
			  ../../Source/serial.cpp \
			  ../../Source/sync.cpp \
			  ../../Source/thread.cpp \
			  ../../Source/timer.cpp 
ASRC        = 
OBJS        = $(CSRC:.c=.o)  $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)

BIN         = $(TGT)

.PHONY: clean all

all: app  

app: $(BIN)

$(BIN): $(OBJS)
	$(AR) -r $(BIN) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(BIN)

# ---------------------------------------------------------------------------
# rules for code generation
# ---------------------------------------------------------------------------
%.o:    %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
%.debug.o:  %.c
	$(CC) $(DEFINES) $(CFLAGS) -o $@ -c $<
	
%.o:    %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<
	
%.debug.o:    %.cpp
	$(CXX) $(DEFINES) $(CFLAGS) -o $@ -c $<

%.o:    %.S
	$(CC) $(ASFLAGS) -o $@ -c $<
	
%.debug.o:    %.S
	$(CC) $(DEFINES) $(ASFLAGS) -o $@ -c $<

