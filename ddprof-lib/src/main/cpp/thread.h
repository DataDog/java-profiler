#ifndef _THREAD_H
#define _THREAD_H

#include <atomic>
#include <deque>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>
#include "os.h"
#include <jvmti.h>
#include "threadLocalData.h"

typedef void (*StackWalkerFunc)(std::deque<u64>::iterator stack_iterator_start, std::deque<u64>::iterator stack_iterator_end);

class ShadowStack {
  private:
    static const int STACK_LIMIT = 4096;
    std::deque<u64> _stack;
    u8 _state = 0;
    StackWalkerFunc _stackWalker;

  public:
    ShadowStack() : _state(0), _stackWalker(nullptr) {}

    void pushFrame(u64 id) {
        _state |= 1;
        if (_stack.size() == STACK_LIMIT) {
            _stack.pop_front();
        }
        _stack.push_back(id);
        if (_state & 2) {
            // collect sample
            if (_stackWalker != nullptr) {
                _stackWalker(_stack.begin(), _stack.end());
            }
        }
        _state = 0;
    }

    u64 popFrame() {
        _state |= 1;
        u64 id = 0;
        if (!_stack.empty()) {
            id = _stack.back();
            _stack.pop_back();
        }
        if (_state & 2) {
            // collect sample
            if (_stackWalker != nullptr) {
                _stackWalker(_stack.begin(), _stack.end());
            }
        }
        _state = 0;
        return id;
    }

    void getStack(StackWalkerFunc stackWalker) {
        if (_state == 1) {
            // trying to collect sample while the stack is modified; postpone
            _state |= 2;
            _stackWalker = stackWalker;
        } else {
            stackWalker(_stack.begin(), _stack.end());
        }
    }
};

class ProfiledThread : public ThreadLocalData {
  private:
    static pthread_key_t _tls_key;
    static int _buffer_size;
    static std::atomic<int> _running_buffer_pos;
    static std::vector<ProfiledThread*> _buffer;

    static void initTLSKey();
    static void doInitTLSKey();
    static inline void freeKey(void *key);
    static void initCurrentThreadWithBuffer();
    static void doInitExistingThreads();
    static void prepareBuffer(int size);
    static void* delayedUninstallUSR1(void* unused);

    int _buffer_pos;
    int _tid;
    u32 _cpu_epoch;
    u32 _wall_epoch;
    u64 _pc;
    u32 _call_trace_id;
    u32 _recording_epoch;
    u64 _span_id;
    ShadowStack _stack;

    ProfiledThread(int buffer_pos, int tid) :
        ThreadLocalData(),
        _buffer_pos(buffer_pos),
        _tid(tid),
        _cpu_epoch(0),
        _wall_epoch(0),
        _pc(0),
        _call_trace_id(0),
        _recording_epoch(0),
        _span_id(0) {};

    void releaseFromBuffer();
  public:
    static ProfiledThread* forTid(int tid) {
        return new ProfiledThread(-1, tid);
    }
    static ProfiledThread* inBuffer( int buffer_pos) {
        return new ProfiledThread(buffer_pos, 0);
    }

    static void initCurrentThread();
    static void initExistingThreads();

    static void release();
    
    static ProfiledThread* current();
    static int currentTid();

    inline int tid() {
        return _tid;
    }

    inline u64 noteCPUSample(u32 recording_epoch) {
        _recording_epoch = recording_epoch;
        return ++_cpu_epoch;
    }

    u32 lookupWallclockCallTraceId(u64 pc, u32 recording_epoch, u64 span_id) {
        if (_wall_epoch == _cpu_epoch
        && _pc == pc
        && _span_id == span_id
        && _recording_epoch == recording_epoch
        && _call_trace_id != 0) {
            return _call_trace_id;
        }
        _wall_epoch = _cpu_epoch;
        _pc = pc;
        _recording_epoch = recording_epoch;
        return 0;
    }

    inline void recordCallTraceId(u32 call_trace_id) {
        _call_trace_id = call_trace_id;
    }

    static void signalHandler(int signo, siginfo_t* siginfo, void* ucontext);

    ShadowStack& shadowStack() {
        return _stack;
    }
};

#endif // _THREAD_H
