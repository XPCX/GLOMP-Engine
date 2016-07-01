INCDIR=./inc/
SRCDIR=./src/
ASMDIR=./asm/
LIBDIR=./lib/
BINDIR=./bin/
TESTDIR=./test/

GL3WDIR?=./gl3w/
GL3WINCDIR?=$(GL3WDIR)include/
GL3WSRCDIR?=$(GL3WDIR)src/
GL3WOBJS?=$(GL3WDIR)gl3w.o


vpath %.cpp $(SRCDIR)
vpath %.hpp $(INCIDR)

CC=clang
CXX=clang++
CFLAGS?=-I$(INCDIR) -I$(GL3WINCDIR)
		#-I/usr/lib/gcc/x86_64-linux-gnu/5.3.1/include
CPPFLAGS?=-std=c++11 -pthread -fopenmp=libomp\
		  $(CFLAGS)

EXE?=$(BINDIR)glomp
TEST_EXE?=$(BINDIR)glomp_test

LDFLAGS?=-lpthread\
		$(GL3WOBJS) -lboost_system -lglfw -lGL -ldl

TEST_LDFLAGS?=$(LDFLAGS) -lboost_unit_test_framework

ASMFLAGS?=-fverbose-asm -g -masm=intel -S
LSTFLAGS?=-alhnd

INCS=$(filter-out $(INCDIR)main.hpp,\
	 $(wildcard $(INCDIR)*.hpp))
SRCS=$(filter-out $(SRCDIR)main.cpp,\
	 $(wildcard $(SRCDIR)*.cpp))
TEST_SRCS=$(wildcard $(TESTDIR)*.cpp)

OBJS=$(patsubst $(SRCDIR)%.cpp,$(LIBDIR)%.o,$(SRCS))
#TEST_OBJS=$(patsubst $(TESTDIR)%.cpp,$(TESTDIR)%.o,$(TEST_SRCS))

ASMS=$(patsubst $(SRCDIR)%.cpp,$(ASMDIR)%.s,$(SRCS))
LSTS=$(patsubst $(SRCDIR)%.cpp,$(ASMDIR)%.lst,$(SRCS))

default: $(EXE)

all:$(EXE) $(TEST_EXE)

$(GL3WDIR)%.o:$(GL3WSRCDIR)%.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<

$(LIBDIR)%.o:$(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CXX) $(CPPFLAGS) $(WFLAGS) -c -o $@ $<

#$(TESTDIR)%.o:$(TESTDIR)%.cpp
#	$(CXX) $(CPPFLAGS) $(WFLAGS) -c -o $@ $<

$(EXE):$(OBJS) $(GL3WOBJS) $(SRCDIR)main.cpp $(INCS)
	$(CXX) $(LIBDIR)*.o -o $@ $(SRCDIR)main.cpp $(CPPFLAGS) $(LDFLAGS)

$(TEST_EXE):$(GL3WOBJS) $(TEST_SRCS)
	$(CXX) -o $@ $(TEST_SRCS) $(CPPFLAGS) $(TEST_LDFLAGS)

$(ASMDIR)%.s:$(SRCDIR)%.cpp
	$(CXX) $(CPPFLAGS) $(ASMFLAGS) -o $@ $<

$(ASMDIR)%.lst:$(ASMDIR)%.s
	as $(LSTFLAGS) $< > $@

## TODO depend without generating a.out
asm:$(LSTS) $(ASMS)
	@rm a.out

clean:
	@rm -f $(EXE) $(OBJS) $(ASMS) $(LSTS)

do:$(EXE)
	@$(EXE)

test:$(TEST_EXE)
	@$(TEST_EXE) --log_level=error
	

.PHONY: all asm clean do test
