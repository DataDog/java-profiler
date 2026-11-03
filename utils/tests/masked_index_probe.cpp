// Copyright 2026, Datadog, Inc
// Standalone regression for Clang 14's aarch64 ASan/UBSan masked-index failure.
// Keep the signed slot, int mask, conditional cell address and publication load:
// Clang 14.0.0 can report a negative bounds index for a valid low byte >= 128.
#include <atomic>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <new>

using u64 = std::uint64_t;

static constexpr int kChunkSize = 256;
static constexpr int kChunkShift = 8;
static constexpr int kChunkMask = kChunkSize - 1;
static constexpr int kMaxThreads = 2048;
static constexpr int kMaxChunks = (kMaxThreads + kChunkSize - 1) / kChunkSize;

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
    const int invalid_slots[] = {INT_MIN, -1, kMaxThreads, INT_MAX};
    context_snapshots_needed.store(true, std::memory_order_release);
    for (int slot = 0; slot < kMaxThreads; ++slot) {
        if (unownedContextCell(slot) != nullptr || canPublishUnownedContext(slot)) {
            std::fprintf(stderr, "unallocated slot %d accepted\n", slot);
            return 1;
        }
    }

    // Owners outlive all non-owning atomic pointers; no concurrent readers exist.
    std::unique_ptr<UnownedContextChunk> chunks[kMaxChunks];
    for (int chunk = 0; chunk < kMaxChunks; ++chunk) {
        chunks[chunk].reset(new (std::nothrow) UnownedContextChunk());
        if (!chunks[chunk]) return 2;
        context_chunks[chunk].store(chunks[chunk].get(), std::memory_order_release);
        for (int offset = 0; offset < kChunkSize; ++offset) {
            const int slot = chunk * kChunkSize + offset;
            chunks[chunk]->cells[offset].words[0].store(static_cast<u64>(slot + 1), std::memory_order_release);
        }
    }

    for (int slot : invalid_slots) {
        if (unownedContextCell(slot) != nullptr || canPublishUnownedContext(slot)) {
            std::fprintf(stderr, "invalid slot %d accepted\n", slot);
            return 3;
        }
    }

    struct PublicationCase {
        u64 value;
        bool allowed;
    };
    const PublicationCase publications[] = {
        {0, true}, {2, true}, {1, false}, {UINT64_MAX - 3, true},
        {UINT64_MAX - 2, false}, {UINT64_MAX - 1, false}, {UINT64_MAX, false}
    };
    int checked = 0;
    for (int chunk = 0; chunk < kMaxChunks; ++chunk) {
        for (int offset = 0; offset < kChunkSize; ++offset) {
            const int slot = chunk * kChunkSize + offset;
            // The oracle uses loop coordinates, not the masked lookup under test.
            auto* expected = &chunks[chunk]->cells[offset];
            auto* actual = unownedContextCell(slot);
            if (actual != expected || actual->words[0].load(std::memory_order_acquire) != static_cast<u64>(slot + 1)) {
                std::fprintf(stderr, "slot %d address/content mismatch\n", slot);
                return 4;
            }
            for (const auto& publication : publications) {
                expected->publication.store(publication.value, std::memory_order_release);
                if (canPublishUnownedContext(slot) != publication.allowed) {
                    std::fprintf(stderr, "slot %d publication %llu mismatch\n", slot,
                                 static_cast<unsigned long long>(publication.value));
                    return 5;
                }
            }
            expected->publication.store(0, std::memory_order_release);
            context_snapshots_needed.store(false, std::memory_order_release);
            if (canPublishUnownedContext(slot)) {
                std::fprintf(stderr, "disabled snapshots accepted slot %d\n", slot);
                return 6;
            }
            context_snapshots_needed.store(true, std::memory_order_release);
            ++checked;
        }
    }
    for (auto& pointer : context_chunks) {
        pointer.store(nullptr, std::memory_order_release);
    }
    std::printf("PASS: %d valid slots, exact addresses/content, 7 publication states, disabled snapshots, 4 invalid boundaries\n", checked);
    return 0;
}
