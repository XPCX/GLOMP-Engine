INCDIR=./inc/
SRCDIR=./src/
ASMDIR=./asm/
OBJDIR=./obj/
LIBDIR=./lib/

GL3WDIR?=./gl3w/
GL3WINCDIR?=$(GL3WDIR)include/
GL3WSRCDIR?=$(GL3WDIR)src/
GL3WLIBDIR?=$(GL3WDIR)lib/
GL3WOBJS?=$(GL3WLIBDIR)gl3w.o

BINDIR=./bin/
TESTDIR=./test/

vpath %.cpp $(SRCDIR)
vpath %.hpp $(INCIDR)

CXX=g++ 
CPPFLAGS?=-std=c++11 -pthread\
		  -I$(GL3WINCDIR)

EXE?=$(BINDIR)glomp
TEST_EXE?=$(BINDIR)glomp_test

LDFLAGS?=-lpthread \
		-lGLU -lX11 \
		-lglfw -lGL -ldl

TEST_LDFLAGS?=$(LDFLAGS) -lboost_unit_test_framework

ASMFLAGS?=-fverbose-asm -g -masm=intel -S
LSTFLAGS?=-alhnd

INCS=$(wildcard $(INCDIR)*.hpp)
SRCS=$(wildcard $(SRCDIR)*.cpp)

TEST_SRCS=$(wildcard $(TESTDIR)*.cpp)

OBJS=$(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRCS))

TEST_OBJS=$(filter-out $(OBJDIR)main.o,$(OBJS)) \
		  $(patsubst $(TESTDIR)%.cpp,$(TESTDIR)%.o,$(TEST_SRCS))

ASMS=$(patsubst $(SRCDIR)%.cpp,$(ASMDIR)%.s,$(SRCS))
LSTS=$(patsubst $(SRCDIR)%.cpp,$(ASMDIR)%.lst,$(SRCS))

default: $(EXE)

all:$(EXE) $(TEST_EXE)

$(OBJDIR)%.o:$(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CXX) $(CPPFLAGS) $(WFLAGS) -c -o $@ $<

$(TESTDIR)%.o:$(TESTDIR)%.cpp
	$(CXX) $(CPPFLAGS) $(WFLAGS) -c -o $@ $<

$(EXE):$(OBJS) 
	$(CXX) $(OBJS) $(GL3WOBJS) -o $@ $(LDFLAGS)

$(TEST_EXE):$(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@ $(TEST_LDFLAGS)

$(ASMDIR)%.s:$(SRCDIR)%.cpp
	$(CXX) $(CPPFLAGS) $(ASMFLAGS) -o $@ $<

$(ASMDIR)%.lst:$(ASMDIR)%.s
	as $(LSTFLAGS) $< > $@

## TODO depend without generating a.out
asm:$(LSTS) $(ASMS)
	@rm a.out

clean:
	@rm -f $(EXE) $(OBJS) $(TEST_OBJS) $(ASMS) $(LSTS)

do:$(EXE)
	@$(EXE)

test:$(TEST_EXE)
	@$(TEST_EXE) --log_level=error
	

.PHONY: all asm clean do test
