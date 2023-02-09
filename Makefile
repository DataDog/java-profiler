ifeq ($(PROFILER_VERSION),)
  export PROFILER_VERSION=2.8.3
endif

LIB_PROFILER=libjavaProfiler.$(SOEXT)
LIB_PROFILER_SO=libjavaProfiler.so
LIB_DEBUG=libdebug.$(SOEXT)
LIB_DEBUG_SO=libdebug.so

CFLAGS=-O3
CXXFLAGS=-O3 -fno-omit-frame-pointer -fvisibility=hidden -std=c++11
INCLUDES=-I$(JAVA_HOME)/include
LIBS=-ldl -lpthread
MERGE=true

SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h)
DEBUG_SOURCES := $(wildcard src/debug/*.c)

ifeq ($(JAVA_HOME),)
  export JAVA_HOME:=$(shell java -cp . JavaHome)
endif

OS:=$(shell uname -s)
ifeq ($(OS),Darwin)
  CXXFLAGS += -D_XOPEN_SOURCE -D_DARWIN_C_SOURCE
  INCLUDES += -I$(JAVA_HOME)/include/darwin
  SOEXT=dylib
  OS_TAG=macos
  ifeq ($(FAT_BINARY),true)
    FAT_BINARY_FLAGS=-arch x86_64 -arch arm64 -mmacos-version-min=10.12
    CFLAGS += $(FAT_BINARY_FLAGS)
    CXXFLAGS += $(FAT_BINARY_FLAGS)
    MERGE=false
  endif
else
  CXXFLAGS += -Wl,-z,defs -Wl,-z,nodelete
  ifeq ($(MERGE),true)
    CXXFLAGS += -fwhole-program
  endif
  LIBS += -lrt
  INCLUDES += -I$(JAVA_HOME)/include/linux
  SOEXT=so
  ifeq ($(findstring musl,$(shell ldd /bin/ls)),musl)
    OS_TAG=linux-musl
    CXXFLAGS += -D__musl__
  else
    OS_TAG=linux
  endif
endif

ARCH:=$(shell uname -m)
ifeq ($(ARCH),x86_64)
  ARCH_TAG=x64
else
  ifeq ($(findstring arm,$(ARCH)),arm)
    ifeq ($(findstring 64,$(ARCH)),64)
      ARCH_TAG=arm64
    else
      ARCH_TAG=arm32
    endif
  else
    ifeq ($(findstring aarch64,$(ARCH)),aarch64)
      ARCH_TAG=arm64
    else
      ifeq ($(ARCH),ppc64le)
        ARCH_TAG=ppc64le
      else
        ARCH_TAG=x86
      endif
    endif
  endif
endif

ifneq ($(ARCH),ppc64le)
  ifneq ($(ARCH_TAG),arm32)
    CXXFLAGS += -momit-leaf-frame-pointer
  endif
endif


.PHONY: all release test clean debug

all: build build/$(LIB_PROFILER) build/debug/$(LIB_DEBUG) build/debug/$(LIB_PROFILER_SO)

%.$(SOEXT): %.so
	rm -f $@
	-ln -s $(<F) $@

build:
	mkdir -p build/debug

build/debug/$(LIB_PROFILER_SO): $(SOURCES) $(HEADERS)
ifneq ($(OS),Darwin)
ifeq ($(MERGE),true)
	for f in src/*.cpp; do echo '#include "'$$f'"'; done |\
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -DDEBUG -fPIC -shared -o $@ -xc++ - $(LIBS)
else
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -DDEBUG -fPIC -shared -o $@ $(SOURCES) $(LIBS)
endif
endif

build/debug/$(LIB_DEBUG_SO): $(DEBUG_SOURCES) $(HEADERS)
ifneq ($(OS),Darwin)
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -shared -o $@ $(DEBUG_SOURCES)
endif

build/$(LIB_PROFILER_SO): $(SOURCES) $(HEADERS)
ifeq ($(MERGE),true)
	for f in src/*.cpp; do echo '#include "'$$f'"'; done |\
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -fPIC -shared -o $@ -xc++ - $(LIBS)
else
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -fPIC -shared -o $@ $(SOURCES) $(LIBS)
endif

test: all
	test/load-libraries-test.sh
	test/maven-test.sh
	echo "All tests passed"

test-%: all
	test/$*-test.sh

clean:
	$(RM) -r build

#TODO: replace --suppress with --inline-suppr when Ubuntu 22.04 is available
cppcheck:
	cppcheck \
		--error-exitcode=2 \
		--suppress=memleak:src/codeCache.cpp:30 \
		--suppress=memleakOnRealloc:src/dwarf.cpp:377 \
		--suppress=memleakOnRealloc:src/jattach/jattach_openj9.c:147 \
		--suppress=comparePointers:src/flightRecorder.cpp:1408 \
		--force \
		src/
