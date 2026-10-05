# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR = ../build/test/resources/native-libs/patch-target-lib
CFLAGS = -fPIC -shared -pthread
# Full RELRO (-z now) as on hardened distros: the GOT is read-only once
# loaded, so every write the patcher makes must first make it writable.
LDFLAGS = -Wl,-z,relro,-z,now
# Two more builds that differ only in their build-ids, which have equal
# length so that the program header tables are identical.
ID_A = 0x1111111111111111111111111111111111111111
ID_B = 0x2222222222222222222222222222222222222222
all:
	cc $(CFLAGS) $(LDFLAGS) -o $(TARGET_DIR)/libpatchtarget.so patch_target.c
	cc $(CFLAGS) $(LDFLAGS) -Wl,--build-id=$(ID_A) -o $(TARGET_DIR)/libbuildid-a.so patch_target.c
	cc $(CFLAGS) $(LDFLAGS) -Wl,--build-id=$(ID_B) -o $(TARGET_DIR)/libbuildid-b.so patch_target.c
