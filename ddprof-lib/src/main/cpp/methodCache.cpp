#include <set>

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
std::shared_ptr<AbstractMethodInfo> MethodInfoCache::get(const u64& id, bool pin) {
    _lock.lockShared();
    auto it(_map.find(id));
    std::shared_ptr<AbstractMethodInfo> retValue = nullptr;
    if (it == _map.end()) {
        retValue = emptyInfo();
    } else {
        std::shared_ptr<AbstractMethodInfo> method_info_ptr = std::static_pointer_cast<AbstractMethodInfo>(it->second);
        if (pin) {
            method_info_ptr.get()->pin(loadAcquire(_epoch));
        }
        retValue = method_info_ptr;
    }
    _lock.unlockShared();

    return retValue;
}

void MethodInfoCache::pin(const u64& id) {
    get(id, true);
}

void MethodInfoCache::unpin(const u64& id) {
    get(id, false).get()->unpin(loadAcquire(_epoch));
}

size_t MethodInfoCache::infoSize(CachedMethodInfo& info) {
    size_t total_size = 0;
    total_size += sizeof(void*);
    total_size += sizeof(unsigned int); // klass idx
    total_size += sizeof(unsigned int); // name idx
    total_size += sizeof(unsigned int); // signature idx
    total_size += sizeof(int); // _line_number_table_size
    // 12 is the size of jvmtiLineNumberEntry struct (https://github.com/openjdk-mirror/jdk7u-jdk/blob/f4d80957e89a19a29bb9f9807d2a28351ed7f7df/src/share/javavm/export/jvmti.h#L617)
    // we can not rely on jvmti.h as that would break the gtests
    total_size += info._line_number_table.get()->_size * 12;
    total_size += sizeof(u64); // _used_epoch
    total_size += sizeof(char); // _attributes
    total_size += sizeof(u64); // the map key

    return total_size;
}

u32 MethodInfoCache::getOrAddStringIdx(const char* str) {
    static const char* nullStr = "<null>";
    assert(str != nullptr);
    if (str == nullptr) {
        str = (char*)nullStr;
    }
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
 this function will return a pointer pointing to 'nullptr'. This can be used to quckly check whether the id corresponds
 to an evicted item - like `if (!cache.getOrAdd(id, func))`
*/
std::shared_ptr<AbstractMethodInfo> MethodInfoCache::getOrAdd(u64 id, MethodInfoFunc func, bool sticky) {
    _lock.lock();
    if (_pass_through) {
        _lock.unlock();
        return func(id, this, false);
    }
    if (_deep_size >= _limit) {
        fprintf(stderr, "===> Hitting limit!\n");
        _lock.unlock();
        return emptyInfo();
    }

    auto it(_map.find(id));
    std::shared_ptr<AbstractMethodInfo> retValue = nullptr;
    if (it == _map.end()) {    // not found
        std::shared_ptr<AbstractMethodInfo> ami_ptr = func(id, this, true);
        AbstractMethodInfo* ami = ami_ptr.get();
        if (ami->isCacheable()) {
            if (sticky) {
                ami->pin(loadAcquire(_epoch));
            }
            std::shared_ptr<CachedMethodInfo> cached_ptr = std::static_pointer_cast<CachedMethodInfo>(ami_ptr);
            _map[id] = cached_ptr;
            // update the deep size
            _deep_size += infoSize(*cached_ptr.get());
        }
        retValue = ami_ptr;
    } else {
        retValue = it->second;
    }
    _lock.unlock();
    return retValue;
}

void MethodInfoCache::release(const u64& epoch) {
    _lock.lock();

    std::set<std::string> strings;

    for (std::unordered_map<u64, std::shared_ptr<CachedMethodInfo>>::iterator it = _map.begin(); it != _map.end();) {
        if (it->second.get()->isPinned()) {
            strings.insert((*_string_map_ptr.get())[it->second.get()->_klass]);
            strings.insert((*_string_map_ptr.get())[it->second.get()->_name]);
            strings.insert((*_string_map_ptr.get())[it->second.get()->_signature]);
            it++;
        } else {
            _deep_size -= infoSize(*(it->second.get()));
            it = _map.erase(it);
        }
    }
//    _dictionary.clear();
    _string_map_ptr.get()->clear();
    for (const auto& string : strings) {
        getOrAddStringIdx(string.c_str());
    }
    _lock.unlock();
}

SharedLineNumberTable::~SharedLineNumberTable() {
    if (_deallocator && _ptr) {
        _deallocator(_ptr);
    }
}
