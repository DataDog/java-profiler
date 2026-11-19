# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR = ../build/test/resources/native-libs/netty-epoll-discovery-lib
all:
	gcc -fPIC -shared -DFIXTURE_DIRECTORY_ANCHOR -o $(TARGET_DIR)/libjava.so netty_epoll_discovery.c
	gcc -fPIC -shared -DJDK_NETWORK_IMAGE -o $(TARGET_DIR)/libnet.so netty_epoll_discovery.c
	gcc -fPIC -shared -Wl,-z,now,-z,relro -o $(TARGET_DIR)/libshaded_netty_transport_native_epoll.so netty_epoll_discovery.c
	gcc -fPIC -shared -DREPLACEMENT_IMAGE -Wl,-z,now,-z,relro -o $(TARGET_DIR)/libreplacement_netty_transport_native_epoll.so netty_epoll_discovery.c
