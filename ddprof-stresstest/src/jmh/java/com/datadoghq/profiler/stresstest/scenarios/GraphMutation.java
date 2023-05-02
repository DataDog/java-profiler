package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Threads;

import java.util.Arrays;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ThreadLocalRandom;

public class GraphMutation {

    public static class GraphNode {
        private final Queue<GraphNode> nodes = new ConcurrentLinkedQueue<>();

        public void link(GraphNode node) {
            nodes.add(node);
        }
    }

    @State(Scope.Benchmark)
    public static class GraphState extends Configuration {
        @Param("1024")
        int nodeCount;

        public GraphNode[] nodes;

        @Setup(Level.Iteration)
        public void setup() {
            nodes = new GraphNode[nodeCount];
            Arrays.setAll(nodes, i -> new GraphNode());
        }
    }

    @Benchmark
    @Threads(8)
    public void mutateGraph(GraphState graph) {
        int object = ThreadLocalRandom.current().nextInt(graph.nodeCount);
        int subject = ThreadLocalRandom.current().nextInt(graph.nodeCount);
        graph.nodes[subject].link(graph.nodes[object]);
    }
}
