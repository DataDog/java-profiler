---
spec_id: REQ-PROF-14548
source: jira
source_ref: PROF-14548
title: "SIGSEGV in Profiler::updateThreadName"
status: implemented
clarity_score: 85
created: 2026-05-08
implementing_session: impl-20260508-184031
implemented_pr: "DataDog/java-profiler#518"
---

# SIGSEGV in Profiler::updateThreadName

```
Profiler::updateThreadName(_jvmtiEnv*, JNIEnv_*, _jobject*, bool)+0x9d
Profiler::dump(char const*, int)+0x109
Java_com_datadoghq_profiler_JavaProfiler_dump0+0x45
com.datadoghq.profiler.JavaProfiler.dump0(Ljava/lang/String;)V
com.datadoghq.profiler.JavaProfiler.dump(Ljava/nio/file/Path;)V (11)
com.datadog.profiling.ddprof.DatadogProfiler.dump(Ljava/nio/file/Path;)V (5)
com.datadog.profiling.ddprof.DatadogProfilerRecording.snapshot(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;)Ldatadog/trace/api/profiling/RecordingData; (17)
com.datadog.profiling.controller.ddprof.DatadogProfilerOngoingRecording.snapshot(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;)Ldatadog/trace/api/profiling/RecordingData; (10)
com.datadog.profiling.agent.CompositeController$CompositeOngoingRecording.lambda$snapshot$0(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;Lcom/datadog/profiling/controller/OngoingRecording;)Ldatadog/trace/api/profiling/RecordingData; (3)
com.datadog.profiling.agent.CompositeController$CompositeOngoingRecording$$Lambda
0x000070376284537c java.util.stream.ReferencePipeline$3$1.accept(Ljava/lang/Object;)V
0x0000703763652620 java.util.ArrayList$ArrayListSpliterator.forEachRemaining(Ljava/util/function/Consumer;)V
0x0000703762e73938 java.util.stream.AbstractPipeline.copyInto(Ljava/util/stream/Sink;Ljava/util/Spliterator;)V
0x00007037634bb1cc java.util.stream.ReferencePipeline.collect(Ljava/util/stream/Collector;)Ljava/lang/Object;
com.datadog.profiling.agent.CompositeController$CompositeOngoingRecording.compose(Ljava/util/function/Function;)Ldatadog/trace/api/profiling/RecordingData; (22)
com.datadog.profiling.agent.CompositeController$CompositeOngoingRecording.snapshot(Ljava/time/Instant;Ldatadog/trace/api/profiling/ProfilingSnapshot$Kind;)Ldatadog/trace/api/profiling/RecordingData; (8)
com.datadog.profiling.controller.ProfilingSystem$SnapshotRecording.snapshot(Z)V (38)
com.datadog.profiling.controller.ProfilingSystem$SnapshotRecording.snapshot()V (2)
com.datadog.profiling.controller.ProfilingSystem$$Lambda
0x0000703762e9604c datadog.trace.util.AgentTaskScheduler$PeriodicTask.run()V
datadog.trace.util.AgentTaskScheduler$Worker.run()V (27)
java.lang.Thread.runWith(Ljava/lang/Object;Ljava/lang/Runnable;)V
java.lang.Thread.run()V
```
