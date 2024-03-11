#include "event.h"
#include "FrameSampler.h"
#include "profiler.h"
#include "vmEntry.h"
#include "stackFrame.h"


#include <iostream>

FrameSampler* const FrameSampler::_instance = new FrameSampler();

void FrameSampler::forget_sampled_methods() {
    // TODO clear out methods seen in the last recording interval
}

void FrameSampler::record_sampled_method(int tid, NMethod* nmethod) {
    // TODO record once per method per recording interval,
    //  requires a signal safe concurrent set<u64>
    u64 methodId = (u64) nmethod->method()->id();
    int codeSize = nmethod->codeSize();
    // we can't work with the code blob unless we know where it ends
    // it is not null terminated so releasing a pointer to it as a
    // c string is dangerous - calls to strlen may segfault etc.
    if (codeSize >= 0) {
        CodeEvent code;
        code._id = methodId;
        code._name = Profiler::instance()->stringLabelMap()->lookup(nmethod->name());
        code._code_size = codeSize;
        code._code = nmethod->code();
        std::cout << "recording code" << std::endl;
        Profiler::instance()->recordCode(tid, &code);
    } else {
        std::cout << "no code size" << std::endl;
    }
}

void FrameSampler::do_sample(int tid, u64 counter, void *ucontext) {
    JNIEnv* jni = VM::jni();
    if (jni == NULL) {
        return; // not Java
    }
    StackFrame frame(ucontext);
    uintptr_t pc = frame.pc();
    bool inCodeHeap = CodeHeap::contains((const void*) pc);
    if (!inCodeHeap) {
        std::cout << "using last Java PC" << std::endl;
        VMThread* vmThread = VMThread::current();
        if (vmThread == NULL) {
            return;
        }
        pc = vmThread->lastJavaPC();
    }
    if (pc == 0) {
        std::cout << "null PC" << std::endl;
        return;
    }
    NMethod* nm = CodeHeap::findNMethod((const void*) pc);
    if (nm != NULL) {
        if (!nm->isNMethod()) {
            std::cout << "not nmethod" << std::endl;
        } else if (!nm->isFrameCompleteAt((const void*) pc)) {
            std::cout << "not complete" << std::endl;
        }
        if (nm->isNMethod() && nm->isFrameCompleteAt((const void*) pc)) {
            int compilationTier = nm->level();
            jmethodID methodID = nm->method()->id();
            assert((u64)pc > (u64)nm->code());
            record_sampled_method(tid, nm);
            FrameEvent event(methodID, (u64)nm->code() - (u64)pc, compilationTier);
            std::cout << "sampling" << std::endl;
            Profiler::instance()->recordFrameSample(counter, tid, &event);
        }
    } else {
        std::cout << "null nmethod" << std::endl;
    }
}

void FrameSampler::sample(int tid, u64 counter, void *ucontext) {
    _instance->do_sample(tid, counter, ucontext);
}

void FrameSampler::clear() {
    _instance->forget_sampled_methods();
}
