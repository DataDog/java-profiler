ifeq ($(PROFILER_VERSION),)
  export PROFILER_VERSION=2.8.3
endif

PACKAGE_NAME=java-profiler-$(PROFILER_VERSION)-$(OS_TAG)-$(ARCH_TAG)
PACKAGE_DIR=/tmp/$(PACKAGE_NAME)

LIB_PROFILER=libjavaProfiler.$(SOEXT)
LIB_PROFILER_SO=libjavaProfiler.so
LIB_DEBUG=libdebug.$(SOEXT)
LIB_DEBUG_SO=libdebug.so
API_JAR=java-profiler.jar

CFLAGS=-O3
CXXFLAGS=-O3 -fno-omit-frame-pointer -fvisibility=hidden -std=c++11
INCLUDES=-I$(JAVA_HOME)/include
LIBS=-ldl -lpthread
MERGE=true

JAVAC=$(JAVA_HOME)/bin/javac
JAR=$(JAVA_HOME)/bin/jar
JAVAC_OPTIONS=-source 7 -target 7 -Xlint:-options

SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h)
DEBUG_SOURCES := $(wildcard src/debug/*.c)
API_SOURCES := $(wildcard src/api/one/profiler/*.java)

ifeq ($(JAVA_HOME),)
  export JAVA_HOME:=$(shell java -cp . JavaHome)
endif

OS:=$(shell uname -s)
ifeq ($(OS),Darwin)
  CXXFLAGS += -D_XOPEN_SOURCE -D_DARWIN_C_SOURCE
  INCLUDES += -I$(JAVA_HOME)/include/darwin
  SOEXT=dylib
  PACKAGE_EXT=zip
  OS_TAG=macos
  ifeq ($(FAT_BINARY),true)
    FAT_BINARY_FLAGS=-arch x86_64 -arch arm64 -mmacos-version-min=10.12
    CFLAGS += $(FAT_BINARY_FLAGS)
    CXXFLAGS += $(FAT_BINARY_FLAGS)
    PACKAGE_NAME=java-profiler-$(PROFILER_VERSION)-$(OS_TAG)
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
  PACKAGE_EXT=tar.gz
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

all: build build/$(LIB_PROFILER) build/$(API_JAR) build/debug/$(LIB_DEBUG) build/debug/$(LIB_PROFILER_SO)

release: build $(PACKAGE_NAME).$(PACKAGE_EXT)

$(PACKAGE_NAME).tar.gz: $(PACKAGE_DIR)
	tar czf $@ -C $(PACKAGE_DIR)/.. $(PACKAGE_NAME)
	rm -r $(PACKAGE_DIR)

$(PACKAGE_NAME).zip: $(PACKAGE_DIR)
	codesign -s "Developer ID" -o runtime --timestamp -v $(PACKAGE_DIR)/build/$(LIB_PROFILER_SO)
	ditto -c -k --keepParent $(PACKAGE_DIR) $@
	rm -r $(PACKAGE_DIR)

$(PACKAGE_DIR): build/$(LIB_PROFILER) \
                build/$(API_JAR)  \
                LICENSE *.md
	mkdir -p $(PACKAGE_DIR)
	cp -RP build LICENSE *.md $(PACKAGE_DIR)
	chmod -R 755 $(PACKAGE_DIR)
	chmod 644 $(PACKAGE_DIR)/LICENSE $(PACKAGE_DIR)/*.md $(PACKAGE_DIR)/build/*.jar

%.$(SOEXT): %.so
	rm -f $@
	-ln -s $(<F) $@

build:
	mkdir -p build/debug

build/debug/$(LIB_PROFILER_SO): $(SOURCES) $(HEADERS)
ifeq ($(MERGE),true)
	for f in src/*.cpp; do echo '#include "'$$f'"'; done |\
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -DDEBUG -fPIC -shared -o $@ -xc++ - $(LIBS)
else
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -DDEBUG -fPIC -shared -o $@ $(SOURCES) $(LIBS)
endif

build/debug/$(LIB_DEBUG_SO): $(DEBUG_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -shared -o $@ $(DEBUG_SOURCES)

build/$(LIB_PROFILER_SO): $(SOURCES) $(HEADERS)
ifeq ($(MERGE),true)
	for f in src/*.cpp; do echo '#include "'$$f'"'; done |\
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -fPIC -shared -o $@ -xc++ - $(LIBS)
else
	$(CXX) $(CXXFLAGS) -DPROFILER_VERSION=\"$(PROFILER_VERSION)\" $(INCLUDES) -fPIC -shared -o $@ $(SOURCES) $(LIBS)
endif

build/$(JATTACH): src/jattach/*.c src/jattach/*.h
	$(CC) $(CFLAGS) -DJATTACH_VERSION=\"$(PROFILER_VERSION)-ap\" -o $@ src/jattach/*.c

build/$(API_JAR): $(API_SOURCES)
	mkdir -p build/api
	$(JAVAC) $(JAVAC_OPTIONS) -d build/api $^
	$(JAR) cf $@ -C build/api .
	$(RM) -r build/api

# %.class: %.java
# 	$(JAVAC) $(JAVAC_OPTIONS) -g:none $^

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
		--suppress=memleakOnRealloc:src/dwarf.cpp:345 \
		--suppress=memleakOnRealloc:src/memleakTracer.cpp:352 \
		--suppress=memleakOnRealloc:src/jattach/jattach_openj9.c:147 \
		--suppress=comparePointers:src/flightRecorder.cpp:1408 \
		--suppress=comparePointers:src/memleakTracer.cpp:236 \
		--suppress=comparePointers:src/memleakTracer.cpp:247 \
		--force \
		src/
