# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR = ../build/test/resources/native-libs/ddprof-admission
CFLAGS = -fPIC -shared
LDFLAGS =

# The STT_GNU_IFUNC marker needs glibc: musl headers and assembler have no
# indirect-function support, so the ifunc fixture is only built on glibc hosts.
GLIBC := $(shell if ldd --version 2>/dev/null | grep -qiE 'glibc|gnu[[:space:]]+libc'; then echo 1; else echo 0; fi)

VARIANTS = libddprof-fixture-gnu.so \
           libddprof-fixture-sysv.so \
           libddprof-fixture-both.so \
           libddprof-fixture-nomark.so \
           libddprof-fixture-onemark.so \
           libddprof-fixture-object.so \
           libddprof-fixture-dep.so \
           libddprof-fixture-deponly.so

ifeq ($(GLIBC),1)
VARIANTS += libddprof-fixture-ifunc.so
endif

all: $(addprefix $(TARGET_DIR)/,$(VARIANTS))

$(TARGET_DIR):
	mkdir -p $@

$(TARGET_DIR)/libddprof-fixture-gnu.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DMARK_START -DMARK_STOP -Wl,--hash-style=gnu -o $@ $<
$(TARGET_DIR)/libddprof-fixture-sysv.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DMARK_START -DMARK_STOP -Wl,--hash-style=sysv -o $@ $<
$(TARGET_DIR)/libddprof-fixture-both.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DMARK_START -DMARK_STOP -Wl,--hash-style=both -o $@ $<
$(TARGET_DIR)/libddprof-fixture-nomark.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -Wl,--hash-style=both -o $@ $<
$(TARGET_DIR)/libddprof-fixture-onemark.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DMARK_STOP -Wl,--hash-style=gnu -o $@ $<
$(TARGET_DIR)/libddprof-fixture-object.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DMARK_OBJECT -DMARK_STOP -Wl,--hash-style=gnu -o $@ $<
ifeq ($(GLIBC),1)
$(TARGET_DIR)/libddprof-fixture-ifunc.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DMARK_IFUNC -DMARK_STOP -Wl,--hash-style=gnu -o $@ $<
endif
$(TARGET_DIR)/libddprof-fixture-dep.so: depFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -Wl,--hash-style=gnu -o $@ $<
$(TARGET_DIR)/libddprof-fixture-deponly.so: hookFixture.c | $(TARGET_DIR)
	cc $(CFLAGS) -DREFERENCE_MARKERS -Wl,--hash-style=gnu -o $@ $<
