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
CFLAGS	    += 

CFLAGS	    += 

# here to add "-Wl,-Bsymbolic" to avoid symbolic confilict in different 
# libraries in using same variable or function names
LDFLAGS     +=  
TGT         = Inline_function



CSRC        =
CXXSRC      = main.cpp \
			  fun1.cpp
ASRC        = 
OBJS        = $(CSRC:.c=.o)  $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)

BIN         = $(TGT)

.PHONY: clean all

all: app  

app: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o  $(BIN) $(OBJS)

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
	
