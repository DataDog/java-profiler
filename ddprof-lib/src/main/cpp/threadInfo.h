#include "mutex.h"
#include "os.h"
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>

class ThreadInfo {
  private:
    Mutex _ti_lock;
    std::map<int, std::string> _thread_names;
    std::map<int, u64> _thread_ids;

  public:
    // disallow copy and assign to avoid issues with the mutex
    ThreadInfo(const ThreadInfo&) = delete;
    ThreadInfo& operator=(const ThreadInfo&) = delete;

    ThreadInfo() {}

    void set(int tid, const char* name, u64 java_thread_id);
    std::pair<std::shared_ptr<std::string>, u64> get(int tid);

    void updateThreadName(int threadId, std::function<std::unique_ptr<char[]>(int)> resolver);

    int size();

    void clearAll(std::set<int> &live_thread_ids);
    void clearAll();

    void reportCounters();

    // For testing
    int getThreadId(int threadId);
};

