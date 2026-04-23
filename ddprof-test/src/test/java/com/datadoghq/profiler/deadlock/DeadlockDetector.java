/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.datadoghq.profiler.deadlock;

import com.datadoghq.profiler.JavaProfiler;

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadInfo;
import java.lang.management.ThreadMXBean;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Test-only deadlock detector for exercising the native deadlock event recording.
 * Production detection is handled by dd-trace-java's DeadlockEventFactory;
 * java-profiler only provides the {@link JavaProfiler#recordDeadlock} recording API.
 */
final class DeadlockDetector {
    private final JavaProfiler profiler;
    private final ThreadMXBean threadMXBean;
    private final boolean synchronizerSupported;
    private final AtomicLong deadlockIdGenerator = new AtomicLong(0);
    private final Set<List<Long>> reportedCycles = ConcurrentHashMap.newKeySet();

    private ScheduledExecutorService executor;
    private ScheduledFuture<?> task;

    DeadlockDetector(JavaProfiler profiler) {
        this.profiler = profiler;
        this.threadMXBean = ManagementFactory.getThreadMXBean();
        this.synchronizerSupported = threadMXBean.isSynchronizerUsageSupported();
    }

    synchronized void start(long intervalMs) {
        if (executor != null) {
            return;
        }
        reportedCycles.clear();
        ScheduledExecutorService exec = Executors.newSingleThreadScheduledExecutor(r -> {
            Thread t = new Thread(r, "dd-deadlock-detector");
            t.setDaemon(true);
            return t;
        });
        executor = exec;
        task = exec.scheduleAtFixedRate(this::check, intervalMs, intervalMs, TimeUnit.MILLISECONDS);
    }

    synchronized void stop() {
        ScheduledFuture<?> f = task;
        if (f != null) {
            f.cancel(false);
            task = null;
        }
        ScheduledExecutorService exec = executor;
        if (exec != null) {
            exec.shutdownNow();
            executor = null;
        }
        reportedCycles.clear();
    }

    void check() {
        try {
            long[] deadlockedIds = synchronizerSupported
                    ? threadMXBean.findDeadlockedThreads()
                    : threadMXBean.findMonitorDeadlockedThreads();
            if (deadlockedIds == null) {
                return;
            }

            List<Long> cycleKey = toCycleKey(deadlockedIds);
            if (!reportedCycles.add(cycleKey)) {
                return;
            }

            ThreadInfo[] infos = synchronizerSupported
                    ? threadMXBean.getThreadInfo(deadlockedIds, true, true)
                    : threadMXBean.getThreadInfo(deadlockedIds, Integer.MAX_VALUE);
            if (infos == null) {
                return;
            }

            // Collect all thread IDs we need to resolve (deadlocked + lock owners)
            Set<Long> needed = new HashSet<>();
            for (long id : deadlockedIds) {
                needed.add(id);
            }
            for (ThreadInfo info : infos) {
                if (info != null && info.getLockOwnerId() >= 0) {
                    needed.add(info.getLockOwnerId());
                }
            }

            Map<Long, Thread> threadsById = findThreadsById(needed);

            long deadlockId = deadlockIdGenerator.incrementAndGet();

            for (ThreadInfo info : infos) {
                if (info == null) {
                    continue;
                }
                long lockOwnerId = info.getLockOwnerId();
                if (lockOwnerId < 0) {
                    continue;
                }

                Thread thread = threadsById.get(info.getThreadId());
                Thread lockOwnerThread = threadsById.get(lockOwnerId);
                if (thread == null || lockOwnerThread == null) {
                    continue;
                }

                String lockName = info.getLockName() != null ? info.getLockName() : "unknown";
                profiler.recordDeadlock(thread, lockName, lockOwnerThread, deadlockId);
            }
        } catch (Exception e) {
            // Swallow — detector must not crash the daemon thread
        }
    }

    private static List<Long> toCycleKey(long[] ids) {
        List<Long> sorted = new ArrayList<>(ids.length);
        for (long id : ids) {
            sorted.add(id);
        }
        Collections.sort(sorted);
        return sorted;
    }

    private static Map<Long, Thread> findThreadsById(Set<Long> needed) {
        Map<Long, Thread> result = new HashMap<>();
        for (Thread t : Thread.getAllStackTraces().keySet()) {
            if (needed.contains(t.getId())) {
                result.put(t.getId(), t);
            }
        }
        return result;
    }
}
