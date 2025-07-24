package com.datadoghq.profiler.stresstest.scenarios.counters;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Threads;

import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

public class GraphMutation {

    public static class GraphNode {
        private volatile ConcurrentLinkedQueue<GraphNode> nodes = new ConcurrentLinkedQueue<>();
        private final AtomicLong linkCount = new AtomicLong(0);

        public void link(GraphNode node) {
            nodes.add(node);
            
            // Switch to new data structure every 100,000 operations
            // Other threads can finish with the old one
            if (linkCount.incrementAndGet() % 100000 == 0) {
                nodes = new ConcurrentLinkedQueue<>();
            }
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
