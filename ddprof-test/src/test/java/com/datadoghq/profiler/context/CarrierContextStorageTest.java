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
package com.datadoghq.profiler.context;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ThreadContext;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.lang.reflect.Method;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Verifies that {@link ThreadContext} storage is scoped to the <em>carrier</em> thread when
 * carrier scoping is active ({@link com.datadoghq.profiler.OtelContextStorage.Mode#CARRIER}).
 *
 * <p>The OTEP record a {@code ThreadContext} writes to is embedded in the carrier's native
 * {@code ProfiledThread} and is what the (carrier-bound) sampler reads. Under carrier scoping,
 * every virtual thread mounted on a given carrier must resolve to the <em>same</em>
 * {@code ThreadContext} — the one whose buffer targets that carrier's live record — regardless
 * of how many virtual threads time-share the carrier. Under the legacy plain-{@code ThreadLocal}
 * behavior each virtual thread gets its own, pinned to whatever carrier it first ran on.
 *
 * <p>Requires JDK 21+ (virtual threads) and {@code jdk.internal.misc.CarrierThreadLocal} being
 * accessible (the build adds {@code --add-exports java.base/jdk.internal.misc=ALL-UNNAMED} on
 * 21+). When carrier scoping is not active the test is skipped rather than failing, so it never
 * gives false confidence on JDKs/configs where the fix cannot engage.
 */
public class CarrierContextStorageTest {

    private static JavaProfiler profiler;

    @BeforeAll
    public static void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
    }

    /** {@code Thread.ofVirtual().start(task)} via reflection so this compiles with --release 8. */
    private static Thread startVirtualThread(Runnable task) throws Exception {
        Method ofVirtual = Thread.class.getMethod("ofVirtual");
        Object builder = ofVirtual.invoke(null);
        Class<?> builderInterface = Class.forName("java.lang.Thread$Builder");
        Method start = builderInterface.getMethod("start", Runnable.class);
        return (Thread) start.invoke(builder, task);
    }

    /** Extracts the carrier name from a mounted VirtualThread's toString, e.g. {@code ...@ForkJoinPool-1-worker-2}. */
    private static String carrierOf(Thread current) {
        String s = current.toString();
        int at = s.lastIndexOf('@');
        return at >= 0 ? s.substring(at + 1) : "<unmounted>";
    }

    @Test
    public void contextIsSharedPerCarrierAcrossVirtualThreads() throws Exception {
        assumeTrue(Platform.isJavaVersionAtLeast(21), "virtual threads require JDK 21+");
        assumeTrue("CARRIER".equals(profiler.contextStorageMode()),
                "carrier-scoped storage not active (mode=" + profiler.contextStorageMode()
                        + "); needs JDK 21+ and --add-exports java.base/jdk.internal.misc=ALL-UNNAMED");

        // Map each observed carrier to the set of distinct ThreadContext identities seen on it.
        final Map<String, Set<Integer>> carrierToContexts = new ConcurrentHashMap<>();
        final int nThreads = 2000;
        final CountDownLatch done = new CountDownLatch(nThreads);

        for (int i = 0; i < nThreads; i++) {
            startVirtualThread(() -> {
                try {
                    // Two touches with a park in between: encourages the vthread to be scheduled
                    // and carriers to be reused across many vthreads, and checks the identity is
                    // stable within a mount.
                    ThreadContext c1 = profiler.getThreadContext();
                    String carrier = carrierOf(Thread.currentThread());
                    carrierToContexts
                            .computeIfAbsent(carrier, k -> ConcurrentHashMap.newKeySet())
                            .add(System.identityHashCode(c1));
                } finally {
                    done.countDown();
                }
            });
        }

        assertTrue(done.await(60, TimeUnit.SECONDS), "virtual threads did not finish in time");

        int carriers = carrierToContexts.size();
        Set<Integer> allContexts = ConcurrentHashMap.newKeySet();
        for (Map.Entry<String, Set<Integer>> e : carrierToContexts.entrySet()) {
            // The crux: every virtual thread that ran on this carrier saw the SAME ThreadContext.
            assertEquals(1, e.getValue().size(),
                    "carrier " + e.getKey() + " must expose exactly one ThreadContext, saw " + e.getValue().size());
            allContexts.addAll(e.getValue());
        }

        // One distinct context per carrier, and far fewer contexts than virtual threads — i.e.
        // storage did NOT key by the virtual thread.
        assertEquals(carriers, allContexts.size(), "expected exactly one ThreadContext per carrier");
        assertTrue(carriers > 0 && carriers < nThreads,
                "expected carrier count (" + carriers + ") to be well below vthread count (" + nThreads + ")");
    }
}
