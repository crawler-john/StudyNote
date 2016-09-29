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

CFLAGS	    += -I.

# here to add "-Wl,-Bsymbolic" to avoid symbolic confilict in different 
# libraries in using same variable or function names
LDFLAGS     +=
TGT         = IOlib


CSRC        = 
CXXSRC      = IOlib.cpp
ASRC        = 
OBJS        = $(CSRC:.c=.o)  $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)

BIN         = $(TGT)

.PHONY: clean all

all: app  

app: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS)

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
	


