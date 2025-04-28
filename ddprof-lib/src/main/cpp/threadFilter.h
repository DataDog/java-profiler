#ifndef _THREADFILTER_H
#define _THREADFILTER_H

#include <atomic>
#include <vector>
#include <cstdint>

class ThreadFilter {
public:
    using SlotID = int;

    ThreadFilter();
    ~ThreadFilter();

    void init(const char* filter);
    void clear();
    bool enabled() const;
    bool accept(int slot_id) const;
    void add(int tid, int slot_id);
    void remove(int slot_id);  // tid unused, for API consistency
    void collect(std::vector<int>& tids) const;

    SlotID registerThread();
    void unregisterThread(SlotID slot_id);

private:
    struct Slot {
        std::atomic<int> value{-1};
        Slot() = default;
        Slot(const Slot&o) { value.store(o.value.load(std::memory_order_relaxed), std::memory_order_relaxed); }
        Slot& operator=(const Slot& o) { value.store(o.value.load(std::memory_order_relaxed),
           std::memory_order_relaxed); return *this; }
    };

    bool _enabled = false;
    std::vector<Slot> _slots;
    std::vector<Slot> _free_list;
    std::atomic<int> _next_index;
};

#endif // _THREADFILTER_H
