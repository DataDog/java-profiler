# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR = ../build/test/resources/native-libs/socket-patch-transaction-lib
# Match host pages so dlclose/reload can reuse the identical mapping.
LDFLAGS = -Wl,-z,now,-z,relro,-z,max-page-size=$(shell getconf PAGESIZE)
all:
	gcc -fPIC -shared -DFIXTURE_DIRECTORY_ANCHOR -o $(TARGET_DIR)/libjava.so socket_patch_transaction.c
	gcc -fPIC -shared $(LDFLAGS) -o $(TARGET_DIR)/libnet.so socket_patch_transaction.c
	gcc -fPIC -shared $(LDFLAGS) -o $(TARGET_DIR)/libnio.so socket_patch_transaction.c
