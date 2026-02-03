CC := g++
SRCDIR := ../../main/cpp
OBJDIR := ./../../../build/scanbuild_obj
CFLAGS := -O0 -Wall -std=c++17 -fno-omit-frame-pointer -momit-leaf-frame-pointer -fvisibility=hidden
SRCS := ${wildcard ${SRCDIR}/*.cpp }
OBJS=${patsubst ${SRCDIR}/%.cpp,${OBJDIR}/%.o,${SRCS}}
INCLUDES := -I$(JAVA_HOME)/include -I../../../../malloc-shim/src/main/public

OS := $(shell uname -s)
ifeq ($(OS),Darwin)
  CFLAGS += -D_XOPEN_SOURCE -D_DARWIN_C_SOURCE
  INCLUDES += -I$(JAVA_HOME)/include/darwin
else
  CFLAGS += -Wl,-z,defs -Wl,-z,nodelete
  INCLUDES += -I$(JAVA_HOME)/include/linux
  ifeq ($(findstring musl,$(shell ldd /bin/ls)),musl)
    CFLAGS += -D__musl__
  endif
endif

.PHONY: all clean

all: $(OBJDIR) $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : ${SRCDIR}/%.cpp | $(OBJDIR)
	${CC} ${CFLAGS} -DEBUG -DPROFILER_VERSION=\"snapshot\" ${INCLUDES}   -c  $<  -o  $@

clean :
	@rm -rf $(OBJDIR)
