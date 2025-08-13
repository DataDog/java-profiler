#ifndef STUB_UNWIND_STATS_H
#define STUB_UNWIND_STATS_H

#include "common.h"
#include "spinLock.h"

#include <stddef.h>
#include <string.h>

enum UnwindFailureKind {
  UNWIND_FAILURE_STUB = 1,
  UNWIND_FAILURE_COMPILED = 2,
  UNWIND_FAILURE_ANY = 3, // UNWIND_FAILURE_STUB | UNWIND_FAILURE_COMPILED
};

// Maximum number of unique names that can be tracked
#define MAX_UNWIND_FAILURE_NAMES 1024
// Maximum length of a name string
#define MAX_NAME_LENGTH 256

class UnwindFailures {
 private:
   char (*_names)[MAX_NAME_LENGTH];
   volatile int _nameCount;
   volatile u64 (*_counters)[UNWIND_FAILURE_ANY + 1];

 public:
   UnwindFailures() : _nameCount(0) {
     _names = new char[MAX_UNWIND_FAILURE_NAMES][MAX_NAME_LENGTH];
     _counters = new u64[MAX_UNWIND_FAILURE_NAMES][UNWIND_FAILURE_ANY + 1];
     memset((void*)_names, 0, MAX_UNWIND_FAILURE_NAMES * MAX_NAME_LENGTH);
     memset((void*)_counters, 0, MAX_UNWIND_FAILURE_NAMES * (UNWIND_FAILURE_ANY + 1) * sizeof(u64));
   }

   ~UnwindFailures() {
     delete[] _names;
     delete[] _counters;
   }

   // Disable copy constructor and assignment operator
   UnwindFailures(const UnwindFailures&) = delete;
   UnwindFailures& operator=(const UnwindFailures&) = delete;

   void record(UnwindFailureKind kind, const char *name) {
     if (!name) return;

     // Fast path: try to find existing name first
     int index = findName(name);
     if (index >= 0) {
       _counters[index][kind - 1]++;
       return;
     }

     // Slow path: create new entry if needed
     index = findOrCreateName(name);
     if (index >= 0) {
       _counters[index][kind - 1]++;
     }
   }

   int findName(const char *name) const {
     for (int i = 0; i < _nameCount; i++) {
       if (strcmp(_names[i], name) == 0) {
         return i;
       }
     }
     return -1;
   }

   int findOrCreateName(const char *name) {
     int index = findName(name);
     if (index >= 0) {
       return index;
     }

     int newIndex = _nameCount++;
     if (newIndex < MAX_UNWIND_FAILURE_NAMES) {
       size_t len = strlen(name);
       if (len >= MAX_NAME_LENGTH) {
         len = MAX_NAME_LENGTH - 1;
       }
       memcpy(_names[newIndex], name, len);
       _names[newIndex][len] = '\0';
       return newIndex;
     }

     return -1;
   }

   u64 count(const char *name, UnwindFailureKind kind = UNWIND_FAILURE_ANY) const {
     int index = findName(name);
     if (index < 0) {
       return 0;
     }

     if (kind == UNWIND_FAILURE_ANY) {
       return _counters[index][UNWIND_FAILURE_STUB - 1] + 
              _counters[index][UNWIND_FAILURE_COMPILED - 1];
     }
     return _counters[index][kind - 1];
   }

   void clear() {
     _nameCount = 0;
     memset((void*)_names, 0, MAX_UNWIND_FAILURE_NAMES * MAX_NAME_LENGTH);
     memset((void*)_counters, 0, MAX_UNWIND_FAILURE_NAMES * (UNWIND_FAILURE_ANY + 1) * sizeof(u64));
   }

   bool empty() const {
     return _nameCount == 0;
   }

   void merge(const UnwindFailures &other) {
     for (int i = 0; i < other._nameCount; i++) {
       int index = findOrCreateName(other._names[i]);
       if (index >= 0) {
         for (int j = 0; j < UNWIND_FAILURE_ANY; j++) {
           _counters[index][j] += other._counters[i][j];
         }
       }
     }
   }

   void swap(UnwindFailures &other) {
     // Swap pointers
     char (*temp_names)[MAX_NAME_LENGTH] = const_cast<char(*)[MAX_NAME_LENGTH]>(_names);
     _names = other._names;
     other._names = temp_names;

     u64 (*temp_counters)[UNWIND_FAILURE_ANY + 1] = const_cast<u64(*)[UNWIND_FAILURE_ANY + 1]>(_counters);
     _counters = other._counters;
     other._counters = temp_counters;

     // Swap name count
     int temp_count = _nameCount;
     _nameCount = other._nameCount;
     other._nameCount = temp_count;
   }

   template <typename Func>
   void forEach(Func fn) const
   {
     for (int i = 0; i < _nameCount; i++)
     {
       const char *name = _names[i];
       for (int j = 0; j < 2; j++)
       {
         UnwindFailureKind kind = static_cast<UnwindFailureKind>(j + 1);
         u64 count = _counters[i][j];
         if (count > 0)
         {
           fn(kind, name, count);
         }
       }
     }
   }
};

class ExclusiveLock {
 private:
  SpinLock &_lock;
 public:
  explicit ExclusiveLock(SpinLock &lock) : _lock(lock) {
    _lock.lock();
  }
  ~ExclusiveLock() {
    _lock.unlock();
  }

  ExclusiveLock(const ExclusiveLock &) = delete;
  ExclusiveLock &operator=(const ExclusiveLock &) = delete;
};

class SharedLock {
 private:
  SpinLock &_lock;
 public:
  explicit SharedLock(SpinLock &lock) : _lock(lock) {
    _lock.lockShared();
  }
  ~SharedLock() {
    _lock.unlockShared();
  }

  SharedLock(const SharedLock &) = delete;
  SharedLock &operator=(const SharedLock &) = delete;
};

class UnwindStats
{
 private:
  static SpinLock _lock;
  static UnwindFailures _unwind_failures;
 public:
  static void recordFailures(UnwindFailures &failures) {
    if (_lock.tryLock()) {
      _unwind_failures.merge(failures);
      _lock.unlock();
    }
  }

  static void recordFailures(UnwindFailures *failures) {
    if (failures) {
      recordFailures(*failures);
    }
  }

  static u64 countFailures(const char* name, UnwindFailureKind kind = UNWIND_FAILURE_ANY) {
    SharedLock l(_lock);
    return _unwind_failures.count(name, kind);
  }

  static void collectAndReset(UnwindFailures& result) {
    ExclusiveLock l(_lock);
    result.swap(_unwind_failures);
  }

  static void reset() {
    ExclusiveLock l(_lock);
    _unwind_failures.clear();
  }
};

#endif // STUB_UNWIND_STATS_H
