# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR = ../build/test/resources/native-libs/patch-target-lib
# Full RELRO (-z now) as on hardened distros: the GOT is read-only once
# loaded, so every write the patcher makes must first make it writable.
all:
	cc -fPIC -shared -pthread -Wl,-z,relro,-z,now -o $(TARGET_DIR)/libpatchtarget.so patch_target.c
