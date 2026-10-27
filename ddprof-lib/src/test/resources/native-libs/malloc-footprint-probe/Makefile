# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0

TARGET_DIR ?= ../../../../../build/test/resources/native-libs/malloc-footprint-probe

.PHONY: all
all:
	$(CXX) -std=c++17 -O2 -Wall -Wextra -I../../../../main/cpp -I../../../cpp main.cpp -lgtest -pthread -o $(TARGET_DIR)/malloc-footprint-probe
