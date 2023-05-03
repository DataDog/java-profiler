package com.datadoghq.profiler.stresstest.scenarios;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Threads;

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

    @Benchmark
    @Threads(8)
    public void mutateGraph(GraphState graph) {
        int object = ThreadLocalRandom.current().nextInt(graph.nodeCount);
        int subject = ThreadLocalRandom.current().nextInt(graph.nodeCount);
        graph.nodes[subject].link(graph.nodes[object]);
    }
}
