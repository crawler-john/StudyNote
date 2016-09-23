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
DEFINES     += -DTRACE_TAM_LIB

ifeq ($(COMPILE_VARIABLE),Debug)
CFLAGS	    += -g -Wall
else
CFLAGS	    += -O2 -Wall -DNDEBUG
endif
CFLAGS	    += -I../../ -I../../../common/Source/
CFLAGS      += -pthread

# here to add "-Wl,-Bsymbolic" to avoid symbolic confilict in different 
# libraries in using same variable or function names
LDFLAGS     += -Wl,-Bsymbolic -fPIC -shared -L../../../common/Target/Redhat5.5/

TGT         = $$PWD/../../Target/redhat5.5/libTAMStdInterface.so
TGT_D       = $$PWD/../../Target/redhat5.5/libTAMStdInterface_D.so

CSRC        = 
CXXSRC      = ../../TAMApi.cpp \
              ../../TAMComm.cpp
ASRC        = 
OBJS        = $(CSRC:.c=.o)  $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)
OBJS_D      = $(CSRC:.c=.debug.o)  $(CXXSRC:.cpp=.debug.o) $(ASRC:.S=.debug.o)
BIN         = $(TGT)
BIN_D       = $(TGT_D)
LIBS        = -lcommon

.PHONY: clean all

all: app  app_D

app: $(BIN)

app_D: $(BIN_D)	

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

$(BIN_D): $(OBJS_D)	
	$(CXX) $(CFLAGS) $(OBJS_D) -o $@ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
	rm -f $(OBJS_D)
	rm -f $(BIN_D)

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

