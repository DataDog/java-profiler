#include "countingAllocator.h"
#include "mutex.h"
#include "nativeMem.h"
#include "os.h"
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>

class ThreadInfo {
private:
  using ThreadNamesMap =
      std::map<int, std::string, std::less<int>,
               CountingAllocator<std::pair<const int, std::string>, NM_THREAD_LOCAL>>;
  using ThreadIdsMap =
      std::map<int, u64, std::less<int>,
               CountingAllocator<std::pair<const int, u64>, NM_THREAD_LOCAL>>;

  Mutex _ti_lock;
  ThreadNamesMap _thread_names;
  ThreadIdsMap _thread_ids;

public:
  // disallow copy and assign to avoid issues with the mutex
  ThreadInfo(const ThreadInfo &) = delete;
  ThreadInfo &operator=(const ThreadInfo &) = delete;

  ThreadInfo() {}

  void set(int tid, const char *name, u64 java_thread_id);
  std::pair<std::shared_ptr<std::string>, u64> get(int tid);

  void updateThreadName(int tid, std::function<std::string(int)> resolver);

  int size();

  void clearAll(std::set<int> &live_thread_ids);
  void clearAll();

  void reportCounters();

  // For testing
  int getThreadId(int threadId);
};
