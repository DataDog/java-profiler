/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NATIVEALLOCATIONUSDT_H
#define _NATIVEALLOCATIONUSDT_H

#include <stddef.h>
#include <stdint.h>

// Returns a point-in-time indication that at least one consumer is attached.
bool isNativeAllocationUsdtEnabled() noexcept;

// Emits ddheap:alloc. Call only after isNativeAllocationUsdtEnabled().
void emitNativeAllocationUsdt(void* address, uint64_t size,
                              uint64_t weighted_bytes) noexcept;

// Converts this sampler's object-count weight into ddheap's weighted-byte ABI.
uint64_t nativeAllocationUsdtWeight(size_t size, uint64_t interval) noexcept;

#ifdef UNIT_TEST
void setNativeAllocationUsdtSemaphoreForTest(uint16_t value) noexcept;
#endif

#endif // _NATIVEALLOCATIONUSDT_H
