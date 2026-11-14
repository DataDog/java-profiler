// Copyright 2026, Datadog, Inc
// Preserve the signed slot, conditional masked address and publication load:
// Clang 14.0.0 on aarch64 can report a negative bounds index for valid slots.
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <memory>

using u64 = std::uint64_t;

static constexpr int kChunkSize = 256;
static constexpr int kChunkShift = 8;
static constexpr int kChunkMask = kChunkSize - 1;
static constexpr int kMaxThreads = 2048;
static constexpr int kMaxChunks = kMaxThreads / kChunkSize;

struct alignas(64) UnownedContextCell {
    std::atomic<u64> words[7]{};
    std::atomic<u64> publication{0};
};

struct UnownedContextChunk {
    UnownedContextCell cells[kChunkSize];
};

static std::atomic<UnownedContextChunk*> context_chunks[kMaxChunks]{};
static std::atomic<bool> context_snapshots_needed{false};

static UnownedContextCell* unownedContextCell(int slot_id) {
    if (slot_id < 0 || slot_id >= kMaxThreads) return nullptr;
    auto* chunk = context_chunks[slot_id >> kChunkShift].load(std::memory_order_acquire);
    return chunk != nullptr ? &chunk->cells[slot_id & kChunkMask] : nullptr;
}

static bool canPublishUnownedContext(int slot_id) {
    if (!context_snapshots_needed.load(std::memory_order_acquire)) return false;
    auto* cell = unownedContextCell(slot_id);
    if (cell == nullptr) return false;
    u64 publication = cell->publication.load(std::memory_order_acquire);
    return (publication & 1) == 0 && publication != UINT64_MAX - 1;
}

int main() {
    std::unique_ptr<UnownedContextChunk> chunks[kMaxChunks];
    context_snapshots_needed.store(true, std::memory_order_release);
    for (int chunk = 0; chunk < kMaxChunks; ++chunk) {
        chunks[chunk] = std::make_unique<UnownedContextChunk>();
        context_chunks[chunk].store(chunks[chunk].get(), std::memory_order_release);
        for (int offset = 0; offset < kChunkSize; ++offset) {
            const int slot = chunk * kChunkSize + offset;
            // The oracle indexes directly; it does not repeat the masked lookup.
            auto* expected = &chunks[chunk]->cells[offset];
            expected->words[0].store(static_cast<u64>(slot + 1), std::memory_order_release);
            auto* actual = unownedContextCell(slot);
            if (actual != expected || actual->words[0].load(std::memory_order_acquire) != static_cast<u64>(slot + 1)
                || !canPublishUnownedContext(slot)) {
                std::fprintf(stderr, "slot %d address/content/publication mismatch\n", slot);
                return 1;
            }
        }
    }
    std::printf("PASS: %d valid masked indices and publication loads\n", kMaxThreads);
    return 0;
}
