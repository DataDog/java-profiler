#include "arch.h"
#include "counters.h"
#include "methodCache.h"
#include "log.h"

std::string AbstractMethodInfo::_error_klass = "L;";
std::string AbstractMethodInfo::_error_name = "jvmtiError";
std::string AbstractMethodInfo::_error_signature = "()L;";

/**
 * Usually, retrieving a cache item will make its usage to be set to the current epoch.
 * The last used epoch is used to calculate the eviction candidates, based on retention.
 * Sometimes, however, it is required to inspect a cache item without updating its usage -
 * and that is possible by providing 'false' to the markUsage argument.
 */
std::shared_ptr<AbstractMethodInfo> MethodInfoCache::get(const u64& id, bool markUsage) {
    _lock.lockShared();
    auto it(_map.find(id));
    std::shared_ptr<AbstractMethodInfo> retValue = nullptr;
    if (it == _map.end()) {
        Counters::increment(JMETHODID_MAP_MISS, 1);
        retValue = emptyInfo();
    } else {
        CachedItem& item = it->second;
        if (item._value_ptr) {
            if (markUsage) {
                item._value_ptr.get()->_used_epoch = _epoch;
            }
        } else {
            Counters::increment(JMETHODID_MAP_MISS, 1);
        }
        retValue = item._value_ptr;
    }
    _lock.unlockShared();

    return retValue;
}

void MethodInfoCache::markUnloaded(u64 id) {
    _lock.lockShared();

    auto it(_map.find(id));
    if (it != _map.end()) {
        CachedMethodInfo* value_ptr = it->second._value_ptr.get();
        if (value_ptr != nullptr) {
            value_ptr->markUnloaded();
        }
    }
    _lock.unlockShared();
}

bool MethodInfoCache::shouldCleanup(CachedItem& item) {
    CachedMethodInfo* value_ptr = item._value_ptr.get();
    if (value_ptr == nullptr) {
        return false;
    }
    return value_ptr->isUnloaded() || (_epoch - value_ptr->_used_epoch) >= _retention;
}

void MethodInfoCache::cleanup() {
    // must be called under exlusive lock
    if (_unloaded || _map.size() > _threshold) {
        for (auto it = _map.begin(); it != _map.end(); ) {
            auto item = it->second;
            if (shouldCleanup(item)) {
                Counters::increment(JMETHODID_MAP_PURGED_ITEMS);
                // update the deep size only on removal
                // the reasoning is that after a while the actually used method infos should stabilize and there
                // will be a very few removals
                size_t to_remove = itemSize(item);
                to_remove -= sizeof(void*) + sizeof(u64); // compensate for the item pointer and the map key
                Counters::decrement(JMETHODID_MAP_BYTES, to_remove);
                it->second.evict();
            } else {
                ++it;
            }
        }
        _unloaded = 0;
    }
}

size_t MethodInfoCache::itemSize(CachedItem& item) {
    size_t total_size = sizeof(void*);
    if (item._value_ptr == nullptr) {
        return total_size;
    }
    CachedMethodInfo mi = *(item._value_ptr);
    total_size += sizeof(void*);
    total_size += sizeof(unsigned int); // klass idx
    total_size += sizeof(unsigned int); // name idx
    total_size += sizeof(unsigned int); // signature idx
    total_size += sizeof(int); // _line_number_table_size
    // 12 is the size of jvmtiLineNumberEntry struct (https://github.com/openjdk-mirror/jdk7u-jdk/blob/f4d80957e89a19a29bb9f9807d2a28351ed7f7df/src/share/javavm/export/jvmti.h#L617)
    // we can not rely on jvmti.h as that would break the gtests
    total_size += mi._line_number_table.get()->_size * 12;
    total_size += sizeof(u64); // _used_epoch
    total_size += sizeof(char); // _attributes
    total_size += sizeof(u64); // the map key

    return total_size;
}

u32 MethodInfoCache::getOrAddStringIdx(char* str) {
    assert(str != nullptr);
    u32 idx = _dictionary.lookup(str);
    _string_map_ptr.get()->set(idx, str);
    return idx;
}

std::shared_ptr<AbstractMethodInfo> MethodInfoCache::newMethodInfo(FrameTypeId frame_type, char* klass, char* name, char* signature, const int modifiers, int line_number_table_size, void* line_number_table, bool is_entry, SharedLineNumberTableDeallocator line_number_table_deallocator, bool cached) {
    if (klass == nullptr || name == nullptr || signature == nullptr) {
        return MethodInfoCache::emptyInfo();
    }

    std::shared_ptr<SharedLineNumberTable> line_number_table_ptr = std::make_shared<SharedLineNumberTable>(line_number_table_size, line_number_table, line_number_table_deallocator);
    if (cached && !_pass_through) {
        u32 klass_idx = getOrAddStringIdx(klass);
        u32 name_idx = getOrAddStringIdx(name);
        u32 signature_idx = getOrAddStringIdx(signature);

        return std::make_shared<CachedMethodInfo>(_string_map_ptr, frame_type, klass_idx, name_idx, signature_idx, modifiers, line_number_table_ptr, is_entry, false);
    } else {
        return std::make_shared<UncachedMethodInfo>(frame_type, klass, name, signature, modifiers, line_number_table_ptr, is_entry, false);
    }
}

/*
 This will attempt to retrieve the item identified by the 'id' value from the cache.
 If such item can not be found, it will invoke the 'func' to create a new item and add it to the cache.
 In case an item with the given id is already in the cache but was evicted (all of its data is gone, just the mapping remaining)
 this function will return a poiner pointing to 'nullptr'. This can be used to quckly check whether the id corresponds
 to an evicted item - like `if (!cache.getOrAdd(id, func))`
*/
std::shared_ptr<AbstractMethodInfo> MethodInfoCache::getOrAdd(u64 id, MethodInfoFunc func) {
    _lock.lock();
    auto it(_map.find(id));
    std::shared_ptr<AbstractMethodInfo> retValue = nullptr;
    if (it == _map.end()) {    // not found
        std::shared_ptr<AbstractMethodInfo> ami_ptr = func(id, this);
        AbstractMethodInfo* ami = ami_ptr.get();
        if (ami->isCacheable()) {
            CachedMethodInfo* cmi = static_cast<CachedMethodInfo*>(ami);
            cmi->_used_epoch = _epoch;
            CachedItem item(std::static_pointer_cast<CachedMethodInfo>(ami_ptr));
            _map.emplace(id, item); //std::make_pair(id, item));
            // update the deep size
            Counters::increment(JMETHODID_MAP_BYTES, itemSize(item));
        }
        retValue = ami_ptr;
    } else {
        retValue = it->second._value_ptr;
    }
    _lock.unlock();
    return retValue;
}

bool MethodInfoCache::add(u64 id, std::shared_ptr<CachedMethodInfo> cmi_ptr) {
    _lock.lock();
    auto it(_map.find(id));
    bool added = false;
    if (it == _map.end()) {    // not found
        CachedMethodInfo* cmi = cmi_ptr.get();
        cmi->_used_epoch = _epoch;
        CachedItem item(cmi_ptr);
        _map.emplace(id, item); //std::make_pair(id, item));
        // update the deep size
        Counters::increment(JMETHODID_MAP_BYTES, itemSize(item));
        added = true;
    } else {

        #ifndef DEBUG
        Log::warn("Attempted duplicate load of jmethodID[%llu] in epoch %llu", id, _epoch);
        #else
        // can not use Log::warn because it pulls in JVMTI transitively and will break unit tests
        fprintf(stdout, "[WARN] Attempted duplicate load of jmethodID[%llu] in epoch %llu", id, _epoch);
        #endif
    }
    _lock.unlock();
    return added;
}

void MethodInfoCache::incEpoch() {
    _lock.lock();
    cleanup();

    _epoch++;
    _lock.unlock();
}

SharedLineNumberTable::~SharedLineNumberTable() {
    if (_deallocator && _ptr) {
        _deallocator(_ptr);
    }
}
