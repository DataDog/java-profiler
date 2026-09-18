---
spec_id: REQ-PROF-14549
source: jira
source_ref: PROF-14549
title: "SIGSEGV in Recording::writeClasses"
status: draft
clarity_score: null
created: 2026-05-07
implementing_session: null
implemented_pr: null
---

# SIGSEGV in Recording::writeClasses

```
Dictionary::collect(std::map<unsigned int, char const*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, char const*> > >&, DictTable*)+0x2b
Dictionary::collect(std::map<unsigned int, char const*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, char const*> > >&, DictTable*)+0x144
Dictionary::collect(std::map<unsigned int, char const*, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, char const*> > >&, DictTable*)+0x144
Recording::writeClasses(Buffer*, Lookup*)+0x4f
Recording::writeCpool(Buffer*)+0x2c4
Recording::finishChunk(bool)+0x267
Recording::switchChunk(int)+0x17
FlightRecorder::dump(char const*, int)+0x6f
Profiler::dump(char const*, int)+0x188
Java_com_datadoghq_profiler_JavaProfiler_dump0+0x47
0x00007c9d64d85811 com.datadoghq.profiler.JavaProfiler.dump0(Ljava/lang/String;)V
0x00007c9d6504c114 com.datadog.profiling.ddprof.DatadogProfilerRecording.snapshot(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;)Ldatadog/trace/api/profiling/RecordingData;
0x00007c9d6504ba14 com.datadog.profiling.controller.ddprof.DatadogProfilerOngoingRecording.snapshot(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;)Ldatadog/trace/api/profiling/RecordingData;
0x00007c9d64e2722c com.datadog.profiling.agent.CompositeController$CompositeOngoingRecording$$Lambda+0x00000000c4b8a000.apply(Ljava/lang/Object;)Ljava/lang/Object;
0x00007c9d636c955c java.util.stream.ReferencePipeline$3$1.accept(Ljava/lang/Object;)V
0x00007c9d63d0395c java.util.ArrayList$ArrayListSpliterator.forEachRemaining(Ljava/util/function/Consumer;)V
0x00007c9d6399dddc java.util.stream.AbstractPipeline.copyInto(Ljava/util/stream/Sink;Ljava/util/Spliterator;)V
0x00007c9d6399da5c java.util.stream.AbstractPipeline.wrapAndCopyInto(Ljava/util/stream/Sink;Ljava/util/Spliterator;)Ljava/util/stream/Sink;
0x00007c9d63c3a1fc java.util.stream.ReduceOps$ReduceOp.evaluateSequential(Ljava/util/stream/PipelineHelper;Ljava/util/Spliterator;)Ljava/lang/Object;
0x00007c9d6387f1a4 java.util.stream.AbstractPipeline.evaluate(Ljava/util/stream/TerminalOp;)Ljava/lang/Object;
0x00007c9d63ccb494 java.util.stream.ReferencePipeline.collect(Ljava/util/stream/Collector;)Ljava/lang/Object;
0x00007c9d64fae5c4 com.datadog.profiling.agent.CompositeController$CompositeOngoingRecording.snapshot(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;)Ldatadog/trace/api/profiling/RecordingData;
0x00007c9d64ec10fc com.datadog.profiling.controller.ProfilingSystem$SnapshotRecording.snapshot(Z)V
0x00007c9d64ec0a04 com.datadog.profiling.controller.ProfilingSystem$$Lambda+0x00000000c31c0800.run(Ljava/lang/Object;)V
0x00007c9d63bf9c8c datadog.trace.util.AgentTaskScheduler$PeriodicTask.run()V
datadog.trace.util.AgentTaskScheduler$Worker.run()V (27)
java.lang.Thread.runWith(Ljava/lang/Object;Ljava/lang/Runnable;)V
java.lang.Thread.run()V
~StubRoutines::call_stub
JavaCalls::call_helper(JavaValue*, methodHandle const&, JavaCallArguments*, JavaThread*)+0x2ce
JavaCalls::call_virtual(JavaValue*, Handle, Klass*, Symbol*, Symbol*, JavaThread*)+0x1d6
thread_entry(JavaThread*, JavaThread*)+0x8b
JavaThread::thread_main_inner()+0x1d8
Thread::call_run()+0xa8
thread_native_entry(Thread*)+0xdb
start_routine_wrapper(void*)+0x9f
```
