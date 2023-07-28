#ifndef _METHODCACHE_H
#define _METHODCACHE_H

#include <cassert>
#include <climits>
#include <unordered_map>
#include <memory>
#include <string>

#include <string.h>
#include <sys/types.h>

#include "arguments.h"
#include "dictionary.h"
#include "frame.h"
#include "log.h"
#include "spinLock.h"

class AbstractMethodInfo;
class MethodInfoCache;

typedef void (*SharedLineNumberTableDeallocator)(void*);
typedef std::shared_ptr<AbstractMethodInfo> (*MethodInfoFunc)(u64 id, MethodInfoCache* cache);

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
    SpinLock _lock;
    std::map<u32, std::string> _map;
  public:
    std::string operator[](u32 index) {
        _lock.lockShared();
        std::string ret = _map[index];
        _lock.unlockShared();
        return ret;
    }

    void set(u32 index, std::string value) {
        _lock.lock();
        _map[index] = value;
        _lock.unlock();
    }
};
class MethodInfoCache;

class AbstractMethodInfo {
  public:
    static std::string _error_klass;
    static std::string _error_name;
    static std::string _error_signature;

  protected:
    const static char ATTRIBUTE_EMPTY = 1;
    const static char ATTRIBUTE_UNLOADED = 2;
    const static char ATTRIBUTE_ENTRY = 4;
    const static char ATTRIBUTE_CACHEABLE = 8;

    char _attributes;

  public:
    int _modifiers;
    std::shared_ptr<SharedLineNumberTable> _line_number_table;
    FrameTypeId _type;

    AbstractMethodInfo(FrameTypeId frame_type, const int modifiers, std::shared_ptr<SharedLineNumberTable> line_number_table, bool is_entry, bool is_empty) : _type(frame_type), _modifiers(modifiers), _line_number_table(line_number_table) {
        _attributes = is_empty ? ATTRIBUTE_EMPTY : 0;
        _attributes |= is_entry ? ATTRIBUTE_ENTRY : 0;
    }

    bool empty() {
        return _attributes & ATTRIBUTE_EMPTY;
    }

    bool isEntry() {
        return _attributes & ATTRIBUTE_ENTRY;
    }

    virtual bool isUnloaded() {
        return _attributes & ATTRIBUTE_UNLOADED;
    }

    virtual bool isCacheable() {
        return _attributes & ATTRIBUTE_CACHEABLE;
    }

    virtual void markUnloaded() {
        _attributes |= ATTRIBUTE_UNLOADED;
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
        return empty() ? _error_klass : (*_string_map_ptr.get())[_klass];
    }

    virtual std::string methodName() {
        return empty() ? _error_name : (*_string_map_ptr.get())[_name];
    }

    virtual std::string methodSignature() {
        return empty() ? _error_signature : (*_string_map_ptr.get())[_signature];
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

    virtual void markUnloaded() {}
};

class CachedItem {
  public:
    std::shared_ptr<CachedMethodInfo> _value_ptr;

    CachedItem(CachedMethodInfo& value) : _value_ptr(std::make_shared<CachedMethodInfo>(value)) {};
    CachedItem(std::shared_ptr<CachedMethodInfo> value_ptr) : _value_ptr(value_ptr) {}

    void evict() {
        _value_ptr.reset();
    }
};

class MethodInfoCache {
  private:
    std::unordered_map<u64, CachedItem> _map;
    Dictionary _dictionary;
    std::shared_ptr<StringMap> _string_map_ptr = std::make_shared<StringMap>();

    SpinLock _lock;
    size_t _unloaded;
    u64 _epoch;
    const int _threshold;
    const int _retention;
    const bool _pass_through;

    void cleanup();
    size_t itemSize(CachedItem& item);
    bool shouldCleanup(CachedItem& item);
    u32 getOrAddStringIdx(char* str);
  public:
    MethodInfoCache(int threshold, int retention) : _dictionary(), _unloaded(0), _epoch(0), _threshold(threshold), _retention(retention), _pass_through(retention < 0 || threshold < 0) {}

    MethodInfoCache(Arguments& args) : MethodInfoCache(args._method_info_cache_threshold, args._method_info_cache_retention) {}

    inline bool passThrough() {
        return _pass_through;
    }

    std::shared_ptr<AbstractMethodInfo> get(const u64& id, bool markUsage = true);
    std::shared_ptr<AbstractMethodInfo> getOrAdd(u64 id, MethodInfoFunc func);

    // used only from gtests
    bool add(u64 id, std::shared_ptr<CachedMethodInfo> cmi_ptr);

    std::shared_ptr<AbstractMethodInfo> newMethodInfo(FrameTypeId frame_type, char* klass, char* name, char* signature, const int modifiers, int line_number_table_size, void* line_number_table, bool is_entry, SharedLineNumberTableDeallocator line_number_table_deallocator, bool cached = true);

    inline std::shared_ptr<AbstractMethodInfo> newMethodInfo(char* klass, char* name, char* signature, const int modifiers, int line_number_table_size, void* line_number_table, SharedLineNumberTableDeallocator line_number_table_deallocator, bool cached = true) {
        return newMethodInfo(FRAME_INTERPRETED, klass, name, signature, modifiers, line_number_table_size, line_number_table, false, line_number_table_deallocator, cached);
    }

    void incEpoch();

    void markUnloaded(u64 id);

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
};

#endif // _METHODCACHE_H
