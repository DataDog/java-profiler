#ifndef _METHODCACHE_H
#define _METHODCACHE_H

#include <cassert>
#include <climits>
#include <unordered_map>
#include <memory>
#include <string>

#include <string.h>
#include <sys/types.h>

#include "arch.h"
#include "arguments.h"
#include "dictionary.h"
#include "frame.h"
#include "log.h"
#include "spinLock.h"

class AbstractMethodInfo;
class MethodInfoCache;

typedef void (*SharedLineNumberTableDeallocator)(void*);
typedef std::shared_ptr<AbstractMethodInfo> (*MethodInfoFunc)(u64 id, MethodInfoCache* cache, bool with_cache);

class SharedLineNumberTable {
  public:
    int _size;
    void* _ptr;
    SharedLineNumberTableDeallocator _deallocator;

    SharedLineNumberTable(int size, void* ptr, SharedLineNumberTableDeallocator deallocator) : _size(size), _ptr(ptr), _deallocator(deallocator) {}
    ~SharedLineNumberTable();
};

class StringMap {
  private:
    std::map<u32, std::string> _map;
  public:
    std::string operator[](u32 index) {
        return _map[index];
    }

    void set(u32 index, std::string value) {
        _map[index] = value;
    }

    void clear() {
        _map.clear();
    }

    u64 size() {
        return _map.size();
    }

    u64 deepSize() {
        u64 size = 0;
        for (const auto &pair : _map) {
            size += pair.second.size();
        }
        return size;
    }
};
class MethodInfoCache;

class TestCachedMethodInfo;

class AbstractMethodInfo {
  friend MethodInfoCache;
  friend TestCachedMethodInfo;

  public:
    static std::string _error_klass;
    static std::string _error_name;
    static std::string _error_signature;

  protected:
    const static char ATTRIBUTE_EMPTY = 1;
    const static char ATTRIBUTE_ENTRY = 2;
    const static char ATTRIBUTE_CACHEABLE = 4;

    char _attributes;

    volatile u64 _pinned_epoch;

    virtual void pin(u64 epoch) {
        u64 prev;

        do {
            prev = _pinned_epoch;
            if (epoch <= prev) {
              return;
            }
        } while (!__sync_bool_compare_and_swap(&_pinned_epoch, prev, epoch));
    }

    virtual void unpin(u64 epoch) {
        u64 prev;

        do {
            prev = _pinned_epoch;
            if (epoch < prev) {
              return;
            }
        } while (!__sync_bool_compare_and_swap(&_pinned_epoch, prev, 0));
    }

  public:
    int _modifiers;
    std::shared_ptr<SharedLineNumberTable> _line_number_table;
    FrameTypeId _type;

    AbstractMethodInfo(FrameTypeId frame_type, const int modifiers, std::shared_ptr<SharedLineNumberTable> line_number_table, bool is_entry, bool is_empty) : _type(frame_type), _modifiers(modifiers), _line_number_table(line_number_table), _pinned_epoch(0) {
        _attributes = is_empty ? ATTRIBUTE_EMPTY : 0;
        _attributes |= is_entry ? ATTRIBUTE_ENTRY : 0;
    }

    bool isEmpty() {
        return _attributes & ATTRIBUTE_EMPTY;
    }

    bool isEntry() {
        return _attributes & ATTRIBUTE_ENTRY;
    }

    bool isPinned() {
        return loadAcquire(_pinned_epoch) > 0;
    }

    virtual bool isCacheable() {
        return _attributes & ATTRIBUTE_CACHEABLE;
    }

    bool isHidden() {
        // 0x1400 = ACC_SYNTHETIC(0x1000) | ACC_BRIDGE(0x0040)
        return _modifiers == 0 || (_modifiers & 0x1040);
    }

    virtual std::string className() = 0;
    virtual std::string methodName() = 0;
    virtual std::string methodSignature() = 0;
};

class CachedMethodInfo : public AbstractMethodInfo {
  friend MethodInfoCache;

  private:
    u32 _klass;
    u32 _name;
    u32 _signature;

  public:
    std::shared_ptr<StringMap> _string_map_ptr;

    u64 _used_epoch;
    
  public:
    CachedMethodInfo(std::shared_ptr<StringMap> string_map_ptr, FrameTypeId frame_type, u32 klass_idx, u32 name_idx, u32 signature_idx, const int modifiers, std::shared_ptr<SharedLineNumberTable> line_number_table, bool is_entry, bool is_empty) : AbstractMethodInfo(frame_type, modifiers, line_number_table, is_entry, is_empty), _string_map_ptr(string_map_ptr), _klass(klass_idx), _name(name_idx), _signature(signature_idx), _used_epoch(-1) {
        _attributes |= ATTRIBUTE_CACHEABLE;
    }

    virtual std::string className() {
        return isEmpty() ? _error_klass : (*_string_map_ptr.get())[_klass];
    }

    virtual std::string methodName() {
        return isEmpty() ? _error_name : (*_string_map_ptr.get())[_name];
    }

    virtual std::string methodSignature() {
        return isEmpty() ? _error_signature : (*_string_map_ptr.get())[_signature];
    }
};

class UncachedMethodInfo : public AbstractMethodInfo {
  friend MethodInfoCache;

  private:
    std::string _klass;
    std::string _name;
    std::string _signature;
  
  public:
    UncachedMethodInfo(FrameTypeId frame_type, std::string klass, std::string name, std::string signature, const int modifiers, std::shared_ptr<SharedLineNumberTable> line_number_table, bool is_entry, bool is_empty) : AbstractMethodInfo(frame_type, modifiers, line_number_table, is_entry, is_empty), _klass(klass), _name(name), _signature(signature) {}

    UncachedMethodInfo() : UncachedMethodInfo(FRAME_INTERPRETED, ";L", "jvmtiError", "()L;", 0, nullptr, true, true) {}

    virtual std::string className() {
        return _klass;
    }

    virtual std::string methodName() {
        return _name;
    }

    virtual std::string methodSignature() {
        return _signature;
    }

    virtual bool isCacheable() {
        return false;
    }

    virtual void pin() {}

    virtual void unpin() {}
};

struct MethodInfoCacheStats {
    u64 _string_count;
    u64 _string_bytes;
    u64 _map_size;
    u64 _map_bytes;
    int _map_limit;

    MethodInfoCacheStats(u64 string_count, u64 string_bytes, u64 map_size, u64 map_bytes, int map_limit) : _string_count(string_count), _string_bytes(string_bytes), _map_size(map_size), _map_bytes(map_bytes), _map_limit(map_limit) {};
    MethodInfoCacheStats(const MethodInfoCacheStats& other) : _string_count(other._string_count), _string_bytes(other._string_bytes), _map_size(other._map_size), _map_bytes(other._map_bytes), _map_limit(other._map_limit) {};
};

class MethodInfoCache {
  private:
    std::unordered_map<u64, std::shared_ptr<CachedMethodInfo>> _map;
    Dictionary _dictionary;
    std::shared_ptr<StringMap> _string_map_ptr = std::make_shared<StringMap>();

    SpinLock _lock;
    u64 _epoch;
    u64 _size;

    const bool _pass_through;
    const int _limit;

    size_t infoSize(CachedMethodInfo& info);
    u32 getOrAddStringIdx(const char* str);
  public:
    MethodInfoCache(int limit, bool pass_through = true) : _dictionary(), _pass_through(pass_through), _epoch(1), _size(0), _limit(limit) {}

    MethodInfoCache(Arguments& args) : MethodInfoCache(10000, false) {}

    inline bool passThrough() {
        return _pass_through;
    }

    std::shared_ptr<AbstractMethodInfo> get(const u64& id, bool pin = false);
    std::shared_ptr<AbstractMethodInfo> getOrAdd(u64 id, MethodInfoFunc func, bool sticky = false);

    std::shared_ptr<AbstractMethodInfo> newMethodInfo(FrameTypeId frame_type, char* klass, char* name, char* signature, const int modifiers, int line_number_table_size, void* line_number_table, bool is_entry, SharedLineNumberTableDeallocator line_number_table_deallocator, bool cached = true);

    inline std::shared_ptr<AbstractMethodInfo> newMethodInfo(char* klass, char* name, char* signature, const int modifiers, int line_number_table_size, void* line_number_table, SharedLineNumberTableDeallocator line_number_table_deallocator, bool cached = true) {
        return newMethodInfo(FRAME_INTERPRETED, klass, name, signature, modifiers, line_number_table_size, line_number_table, false, line_number_table_deallocator, cached);
    }

    size_t size() {
        _lock.lockShared();
        size_t ret = _map.size();
        _lock.unlockShared();
        return ret;
    }

    size_t deepSize();

    std::shared_ptr<AbstractMethodInfo> emptyInfo() {
        static std::shared_ptr<AbstractMethodInfo> empty= std::make_shared<UncachedMethodInfo>();
        return empty;
    }

    MethodInfoCacheStats stats() {
        _lock.lockShared();
        StringMap string_map = *_string_map_ptr.get();
        MethodInfoCacheStats stats(string_map.size(), string_map.deepSize(), _map.size(), _size, _limit);
        _lock.unlockShared();
        return stats;
    }

    void pin(const u64& id);
    void unpin(const u64& id);
    void release(const u64& epoch);
    inline u64 incrementEpoch() {
        return atomicInc(_epoch);
    }
    inline MethodInfoCacheStats newEpoch() {
        MethodInfoCacheStats cache_stats = stats();
        const u64 prev = incrementEpoch();
        release(prev);
        return cache_stats;
    }
};

#endif // _METHODCACHE_H
