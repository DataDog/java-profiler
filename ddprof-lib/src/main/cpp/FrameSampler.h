#ifndef JAVA_PROFILER_FRAMESAMPLER_H
#define JAVA_PROFILER_FRAMESAMPLER_H

#include "arch.h"
#include "vmStructs.h"

class FrameSampler {
private:
    static FrameSampler* const _instance;
    void do_sample(int tid, u64 counter, void* ucontext);
    void forget_sampled_methods();
    void record_sampled_method(int tid, NMethod* nmethod);
public:
    static void sample(int tid, u64 counter, void* ucontext);
    static void clear();

};


#endif //JAVA_PROFILER_FRAMESAMPLER_H
