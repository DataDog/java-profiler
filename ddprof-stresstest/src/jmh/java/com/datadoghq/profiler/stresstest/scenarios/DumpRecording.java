package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Threads;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.UUID;
import java.util.concurrent.ThreadLocalRandom;

@State(Scope.Benchmark)
public class DumpRecording extends Configuration {

    @Param(BASE_COMMAND + ",memory=1048576:a")
    public String command;

    @Benchmark
    @Threads(2)
    public Object dumpRecording(GraphState graph) throws IOException {
        for (int i = 0; i < 100; i++) {
            int object = ThreadLocalRandom.current().nextInt(graph.nodeCount);
            int subject = ThreadLocalRandom.current().nextInt(graph.nodeCount);
            graph.nodes[subject].link(graph.nodes[object]);
        }
        Path tmpRecording = Files.createTempFile(UUID.randomUUID().toString(), ".jfr");
        JavaProfiler.getInstance().dump(tmpRecording);
        return Files.deleteIfExists(tmpRecording);
    }
}
