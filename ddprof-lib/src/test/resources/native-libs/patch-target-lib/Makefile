# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR = ../build/test/resources/native-libs/patch-target-lib
CFLAGS = -fPIC -shared -pthread
# Full RELRO (-z now) as on hardened distros: the GOT is read-only once
# loaded, so every write the patcher makes must first make it writable.
LDFLAGS = -Wl,-z,relro,-z,now
# Align segments to the page size of the build host, which runs the tests. With
# a larger p_align (64K by default on aarch64), glibc over-allocates the mapping
# to align it, so a reload never fits the hole an unload left behind and the
# tests that need a reload at the same base would always skip.
LDFLAGS += -Wl,-z,max-page-size=$(shell getconf PAGESIZE)
# Two more builds that differ only in their build-ids, which have equal
# length so that the program header tables are identical.
ID_A = 0x1111111111111111111111111111111111111111
ID_B = 0x2222222222222222222222222222222222222222
all:
	cc $(CFLAGS) $(LDFLAGS) -o $(TARGET_DIR)/libpatchtarget.so patch_target.c
	cc $(CFLAGS) $(LDFLAGS) -Wl,--build-id=$(ID_A) -o $(TARGET_DIR)/libbuildid-a.so patch_target.c
	cc $(CFLAGS) $(LDFLAGS) -Wl,--build-id=$(ID_B) -o $(TARGET_DIR)/libbuildid-b.so patch_target.c
	# Two builds without a build-id that differ only in importing write() or read().
	cc $(CFLAGS) $(LDFLAGS) -Wl,--build-id=none -DIMPORT=write -o $(TARGET_DIR)/libnoid-write.so noid_target.c
	cc $(CFLAGS) $(LDFLAGS) -Wl,--build-id=none -DIMPORT=read -o $(TARGET_DIR)/libnoid-read.so noid_target.c
