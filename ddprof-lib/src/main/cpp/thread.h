#ifndef _THREAD_H
#define _THREAD_H

#include <atomic>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>
#include "os.h"
#include <jvmti.h>
#include "threadState.h"

class ProfiledThread {
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
    u64 _cpu_epoch;
    u64 _wall_epoch;
    u64 _skipped_samples;
    u64 _context_key;
    JavaThreadState _thread_state;

    ProfiledThread(int buffer_pos, int tid) :
        _buffer_pos(buffer_pos),
        _tid(tid),
        _cpu_epoch(0),
        _wall_epoch(0),
        _skipped_samples(0),
        _context_key(0),
        _thread_state(JAVA_THREAD_RUNNABLE){};

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

    inline u64 noteCPUSample() {
        return ++_cpu_epoch;
    }
    bool noteWallSample(u64 context_key, u64* skipped_samples);

    JavaThreadState getThreadState() {
        return _thread_state;
    }

    void setThreadState(JavaThreadState state) {
        _thread_state = state;
    }

    static void signalHandler(int signo, siginfo_t* siginfo, void* ucontext);

    static void JNICALL MonitorContendedEnter(jvmtiEnv* jvmti, JNIEnv* env, jthread thread, jobject object);
    static void JNICALL MonitorContendedEntered(jvmtiEnv* jvmti, JNIEnv* env, jthread thread, jobject object);
    static void JNICALL MonitorWait(jvmtiEnv* jvmti, JNIEnv* env, jthread thread, jobject object, jlong timeout);
    static void JNICALL MonitorWaited(jvmtiEnv* jvmti, JNIEnv* env, jthread thread, jobject object, jboolean timed_out);
};

#endif // _THREAD_H
