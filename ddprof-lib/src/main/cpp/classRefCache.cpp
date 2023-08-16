
#include <set>

#include <jni.h>

#include "classRefCache.h"
#include "vmEntry.h"

ClassRefCache* const ClassRefCache::_instance = new ClassRefCache();

void ClassRefCache::store(JNIEnv* jni, std::set<jclass>& classes) {
    std::set<jobject> refs;
    int numRefs = 0;
    for (auto const& clz : classes) {
        refs.insert(jni->NewGlobalRef(clz));
    }
    int epoch = loadAcquire(_epoch);
    _cache_lock[epoch].lock();
    for (auto const& ref : refs) {
        if (!_data[epoch].insert(ref).second) {
            jni->DeleteGlobalRef(ref);
        }
    }
    _cache_lock[epoch].unlock();
}

void ClassRefCache::keep(JNIEnv* jni, std::set<jclass>& kept_classes) {
    std::set<jobject> oldset;
    oldset.insert(_persistent.begin(), _persistent.end());

    _persistent.clear();
    for (auto const& clz : kept_classes) {
        _persistent.insert(jni->NewGlobalRef(clz));
    }

    for (auto const& ref : oldset) {
        jni->DeleteGlobalRef(ref);
    }
}

void ClassRefCache::doClean(ClearTask* cleanable) {
    JNIEnv* jni = VM::jni();
    int epoch = cleanable->_epoch;
    _cache_lock[epoch].lock();
    for (auto const& ref : _data[epoch]) {
        if (cleanable->_forced || _persistent.find(ref) == _persistent.end()) {
            jni->DeleteGlobalRef(ref);
        }
    }
    _data[epoch].clear();
    _cache_lock[epoch].unlock();
}

void ClassRefCache::destroy() {
    ClearTask task1 = clear(true);
    ClearTask task2 = clear(true);
    _persistent.clear();
}

ClearTask ClassRefCache::clear(bool force) {
    int epoch;
    do {
        epoch = _epoch;
    } while (!__sync_bool_compare_and_swap(&_epoch, epoch, epoch == 0 ? 1 : 0));

    return ClearTask(epoch, force);
}

ClearTask::~ClearTask() {
    ClassRefCache::instance()->doClean(this);
}

