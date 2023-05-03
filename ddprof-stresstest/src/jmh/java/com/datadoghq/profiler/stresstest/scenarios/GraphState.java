package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.*;

import java.util.Arrays;

@State(Scope.Benchmark)
public class GraphState extends Configuration {
    @Param("1024")
    int nodeCount;

    public GraphMutation.GraphNode[] nodes;

    @Setup(Level.Iteration)
    public void setup() {
        nodes = new GraphMutation.GraphNode[nodeCount];
        Arrays.setAll(nodes, i -> new GraphMutation.GraphNode());
    }
}
