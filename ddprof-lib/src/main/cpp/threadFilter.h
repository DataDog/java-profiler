#ifndef _THREAD_FILTER_H
#define _THREAD_FILTER_H

#include <atomic>
#include <vector>
#include "common.h"
#include "atomicHashMap.h"

class ThreadFilter {
public:
    ThreadFilter() = default;
    ~ThreadFilter() = default;

    bool init(const char* filter = nullptr);
    bool accept(int thread_id) const;
    void add(int thread_id);
    bool remove(int thread_id);
    void clear();
    void collect(std::vector<int>& tids) const;
    bool enabled() const;

private:
    AtomicHashMap<int, bool> _active_threads;
    bool _enabled;
};

#endif // _THREAD_FILTER_H
