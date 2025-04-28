#ifndef _THREADFILTER_H
#define _THREADFILTER_H

#include <atomic>
#include <array>
#include <vector>
#include <cstdint>
#include <mutex>

class ThreadFilter {
public:
    using SlotID = int;
    static constexpr int kChunkSize = 128;
    static constexpr int kChunkShift = 7;
    static constexpr int kChunkMask = kChunkSize - 1;
    static constexpr int kMaxThreads = 2048;
    ThreadFilter();
    ~ThreadFilter();

    void init(const char* filter);
    void clear();
    bool enabled() const;
    bool accept(SlotID slot_id) const;
    void add(int tid, SlotID slot_id);
    void remove(SlotID slot_id);
    void collect(std::vector<int>& tids) const;

    SlotID registerThread();
    void unregisterThread(SlotID slot_id);

private:
    struct Slot {
        std::atomic<int> value{-1};
        Slot() = default;
        Slot(const Slot& o) { value.store(o.value.load(std::memory_order_relaxed), std::memory_order_relaxed); }
        Slot& operator=(const Slot& o) { 
            value.store(o.value.load(std::memory_order_relaxed), std::memory_order_relaxed); 
            return *this; 
        }
    };

    bool _enabled = false;
    std::vector<std::array<Slot, kChunkSize>> _slots;
    std::atomic<SlotID> _next_index;
    
    static constexpr int kFreeListSize = 128;
    std::atomic<SlotID> _free_list[kFreeListSize];
    std::atomic<int> _free_list_top;  // Points to next free slot

    mutable std::mutex _slot_mutex;
};

#endif // _THREADFILTER_H
