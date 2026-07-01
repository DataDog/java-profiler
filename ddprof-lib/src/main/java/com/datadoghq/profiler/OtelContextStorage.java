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
package com.datadoghq.profiler;

/**
 * Factory for the thread-local that backs {@link ThreadContext} storage, and the
 * home of the context-storage <em>mode</em> selection.
 *
 * <p>Why this exists: the OTEP record a {@link ThreadContext} writes to is embedded in
 * the <em>carrier's</em> native {@code ProfiledThread}, and that carrier's record is what
 * the sampler (an async-signal handler bound to the carrier OS thread) reads. A plain
 * {@link ThreadLocal} keys the {@code ThreadContext} — and therefore its
 * {@code DirectByteBuffer} conduit — by the <em>virtual</em> thread, pinning it to
 * whichever carrier was mounted at first use. That is wrong once the virtual thread
 * migrates (writes land on the old carrier, so a sampler on the new carrier sees stale
 * or empty context) and unsafe once the old carrier's OS thread exits (the record is
 * freed while the buffer keeps being written — a use-after-free that can corrupt
 * JVM-owned native memory). See {@code ThreadContext} and the design note.
 *
 * <p>{@link Mode#CARRIER} scopes storage to the carrier via
 * {@code jdk.internal.misc.CarrierThreadLocal} (JDK 21+), whose {@code get()/set()/remove()}
 * operate on the current carrier's map even when called from a mounted virtual thread. A
 * mounted virtual thread then always resolves to its current carrier's record, which is
 * exactly what the sampler reads; storage lifetime matches the native record's lifetime,
 * so the dangling-buffer window is eliminated.
 *
 * <p>{@code CarrierThreadLocal} lives in a non-exported package, so {@link Mode#CARRIER}
 * needs {@code --add-exports java.base/jdk.internal.misc=ALL-UNNAMED} at runtime (a
 * {@code -javaagent} can grant this via {@code Instrumentation.redefineModule}). When the
 * type is missing (older JDK) or inaccessible (export not granted), we degrade to
 * {@link Mode#THREAD} — today's plain {@code ThreadLocal} behavior — never failing hard.
 *
 * <p>The instance is held as a {@link ThreadLocal} (the supertype, available on the Java 8
 * baseline) and constructed reflectively, so calls dispatch virtually to the carrier-scoped
 * overrides with no per-call reflection and no compile-time dependency on the internal type.
 */
final class OtelContextStorage {

    /** Resolved storage scope. */
    enum Mode {
        /** Carrier-scoped via {@code jdk.internal.misc.CarrierThreadLocal} (JDK 21+). */
        CARRIER,
        /** Legacy virtual-thread-scoped plain {@link ThreadLocal}. */
        THREAD
    }

    /**
     * Kill-switch / selector system property: {@code auto} (default) | {@code carrier} | {@code thread}.
     * <ul>
     *   <li>{@code auto} — use {@link Mode#CARRIER} when available, else {@link Mode#THREAD}.</li>
     *   <li>{@code carrier} — request carrier scoping; warn and fall back if unavailable.</li>
     *   <li>{@code thread} — force legacy behavior (disables carrier scoping entirely).</li>
     * </ul>
     */
    static final String MODE_PROPERTY = "ddprof.context.storage.mode";

    private static final String INTERNAL_CTL = "jdk.internal.misc.CarrierThreadLocal";

    private OtelContextStorage() {}

    /**
     * The scope of a storage instance returned by {@link #create()} — a property of the
     * instance itself (its concrete type), so there is no shared mutable state to leak
     * between callers.
     */
    static Mode modeOf(ThreadLocal<?> storage) {
        return storage != null && INTERNAL_CTL.equals(storage.getClass().getName())
                ? Mode.CARRIER : Mode.THREAD;
    }

    /**
     * Build the backing thread-local according to {@link #MODE_PROPERTY}, degrading to
     * {@link Mode#THREAD} whenever carrier scoping is unavailable. Never throws.
     */
    static ThreadLocal<ThreadContext> create() {
        String requested = System.getProperty(MODE_PROPERTY, "auto").trim().toLowerCase();

        if ("thread".equals(requested)) {
            return new ThreadLocal<>();
        }

        // "auto" or "carrier": prefer carrier scoping when the internal type is reachable.
        ThreadLocal<ThreadContext> carrier = tryCreateCarrierLocal();
        if (carrier != null) {
            return carrier;
        }

        if ("carrier".equals(requested)) {
            System.out.println("[WARN] ddprof: carrier-scoped context storage requested via -D"
                    + MODE_PROPERTY + "=carrier but " + INTERNAL_CTL + " is unavailable; "
                    + "falling back to thread-scoped storage. On JDK 21+ add "
                    + "--add-exports java.base/jdk.internal.misc=ALL-UNNAMED.");
        }
        return new ThreadLocal<>();
    }

    /**
     * Returns a {@code CarrierThreadLocal} (as its {@link ThreadLocal} supertype) or
     * {@code null} if the type is absent (JDK &lt; 21) or not accessible (export not granted).
     */
    @SuppressWarnings("unchecked")
    private static ThreadLocal<ThreadContext> tryCreateCarrierLocal() {
        try {
            Class<?> ctl = Class.forName(INTERNAL_CTL);
            // Public no-arg constructor of a public type; the newInstance access check
            // is what fails (IllegalAccessException) when the package is not exported.
            Object instance = ctl.getConstructor().newInstance();
            return (ThreadLocal<ThreadContext>) instance;
        } catch (Throwable t) {
            // ClassNotFoundException (JDK < 21), IllegalAccessException (no --add-exports),
            // or any other reflective failure — degrade silently to thread scoping.
            return null;
        }
    }
}
