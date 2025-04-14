// Copyright (c) 2024
// This file is part of a profiler system maintained by Datadog, Inc.
// Generated with AI assistance.

#include "threadFilter.h"
#include "common.h"
#include <thread>
#include <cstdlib>
#include <cstring>
#include <cstdio>

void ThreadFilter::clear() {
    _active_threads.clear();
}

bool ThreadFilter::accept(int thread_id) const {
    if (!_enabled) return true;
    return _active_threads.find(thread_id);
}

void ThreadFilter::add(int thread_id) {
    _active_threads.insert(thread_id, true);
}

bool ThreadFilter::remove(int thread_id) {
    _active_threads.erase(thread_id);
    return true;
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    _active_threads.collect(tids);
}

bool ThreadFilter::init(const char* filter) {
    _enabled = (filter != nullptr);
    return true;
}

bool ThreadFilter::enabled() const {
    return _enabled;
}
