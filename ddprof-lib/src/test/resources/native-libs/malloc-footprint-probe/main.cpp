/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "mallocFootprint.h"
#include "mallocFootprintChecks.h"

#ifdef __GLIBC__
struct FreeAllocation {
  void operator()(void *p) const { free(p); }
};
using Allocation = std::unique_ptr<void, FreeAllocation>;

// Standalone so no profiler global constructor can initialize headerBytes()
// before this heap layout is ready. GLIBC_TUNABLES disables tcache at exec.
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  if (argc != 2) return 1;
  const bool fragmented = strcmp(argv[1], "fragmented") == 0;
  if (!fragmented && strcmp(argv[1], "contiguous") != 0) {
    fprintf(stderr, "Unknown allocator layout: %s\n", argv[1]);
    return 1;
  }
  // Disable fastbins as well: adjacent freed chunks must coalesce, while the
  // live spacers below keep the fragmented holes separate.
  if (mallopt(M_MXFAST, 0) == 0) return 2;
  Allocation drain[256];
  Allocation holes[32];
  Allocation spacers[32];
  for (auto &p : drain) {
    p.reset(malloc(48));
    if (!p) return 3;
  }
  for (int i = 0; i < 32; i++) {
    holes[i].reset(malloc(48));
    if (!holes[i]) return 3;
    if (fragmented) {
      spacers[i].reset(malloc(256));
      if (!spacers[i]) return 3;
    }
  }
  const size_t usable = malloc_usable_size(holes[0].get());
  const uintptr_t stride = (uintptr_t)holes[1].get() - (uintptr_t)holes[0].get();
  // Validate the real allocator layout, rather than assuming an ABI's chunk
  // size. A changed layout is a failed precondition, never a silent skip.
  if (stride <= usable) return 4;
  for (int i = 1; i < 32; i++) {
    if ((uintptr_t)holes[i].get() - (uintptr_t)holes[i - 1].get() != stride ||
        malloc_usable_size(holes[i].get()) != usable) return 4;
  }
  if (fragmented ? stride - usable <= 64 : stride - usable > 64) return 4;
  const size_t expected_header = fragmented ? 0 : stride - usable;
  for (auto &p : holes) p.reset();

  const size_t header = MallocFootprint::headerBytes();
  if (header != expected_header) {
    fprintf(stderr, "header: expected %zu, got %zu (stride=%zu usable=%zu)\n",
            expected_header, header, (size_t)stride, usable);
    return 5;
  }
  Allocation p(malloc(96));
  if (!p) return 3;
  const size_t expected_footprint = malloc_usable_size(p.get()) + expected_header;
  const size_t expected_overhead = expected_footprint - 96;
  if (MallocFootprint::of(p.get(), 96) != expected_footprint ||
      MallocFootprint::overheadOf(p.get(), 96) != expected_overhead) return 6;
  // The fragmented case must reproduce the original percentage-test failure,
  // including its remaining usable-size rounding, rather than just header=0.
  if (fragmented && (expected_overhead == 0 || expected_overhead * 10 >= 96)) return 7;
  Allocation large(malloc(512 * 1024));
  if (!large) return 3;
  checkOverheadFractions(100.0 * expected_overhead / 96,
      100.0 * MallocFootprint::overheadOf(large.get(), 512 * 1024) / (512 * 1024));
  fprintf(stderr, "%s: header=%zu usable=%zu overhead=%zu\n",
          fragmented ? "fragmented" : "contiguous", header,
          malloc_usable_size(p.get()), expected_overhead);
  return ::testing::Test::HasFailure() ? 8 : 0;
}
#else
int main() { return 77; }
#endif
