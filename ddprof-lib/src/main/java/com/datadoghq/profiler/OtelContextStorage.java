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

import java.util.Locale;

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
 * <p>{@link ContextStorageMode#CARRIER} scopes storage to the carrier via
 * {@code jdk.internal.misc.CarrierThreadLocal} (JDK 21+), whose {@code get()/set()/remove()}
 * operate on the current carrier's map even when called from a mounted virtual thread. A
 * mounted virtual thread then always resolves to its current carrier's record, which is
 * exactly what the sampler reads; storage lifetime matches the native record's lifetime,
 * so the dangling-buffer window is eliminated.
 *
 * <p>{@code CarrierThreadLocal} lives in a non-exported package, so {@link ContextStorageMode#CARRIER}
 * needs {@code --add-exports java.base/jdk.internal.misc=ALL-UNNAMED} at runtime (a
 * {@code -javaagent} can grant this via {@code Instrumentation.redefineModule}). When the
 * type is missing (older JDK) or inaccessible (export not granted), we degrade to
 * {@link ContextStorageMode#THREAD} — today's plain {@code ThreadLocal} behavior — never failing hard.
 *
 * <p>The instance is held as a {@link ThreadLocal} (the supertype, available on the Java 8
 * baseline) and constructed reflectively, so calls dispatch virtually to the carrier-scoped
 * overrides with no per-call reflection and no compile-time dependency on the internal type.
 */
final class OtelContextStorage {

    /**
     * Selector system property: {@code auto} (default) | {@code carrier} | {@code thread}.
     * Named under {@code ddprof.debug.*} because it is an internal knob, not part of the
     * supported configuration surface.
     * <ul>
     *   <li>{@code auto} — use {@link ContextStorageMode#CARRIER} when available, else
     *       {@link ContextStorageMode#THREAD} (logged loudly on JDK 21+, where the fallback is
     *       unsafe under virtual threads).</li>
     *   <li>{@code carrier} — require carrier scoping; {@link #create()} throws if unavailable.</li>
     *   <li>{@code thread} — force legacy behavior (disables carrier scoping entirely).</li>
     * </ul>
     */
    static final String MODE_PROPERTY = "ddprof.debug.context.storage.mode";

    private static final String INTERNAL_CTL = "jdk.internal.misc.CarrierThreadLocal";

    private OtelContextStorage() {}

    /**
     * The scope of a storage instance returned by {@link #create()} — a property of the
     * instance itself (its concrete type), so there is no shared mutable state to leak
     * between callers.
     */
    static ContextStorageMode modeOf(ThreadLocal<?> storage) {
        return storage != null && INTERNAL_CTL.equals(storage.getClass().getName())
                ? ContextStorageMode.CARRIER : ContextStorageMode.THREAD;
    }

    /**
     * Build the backing thread-local according to {@link #MODE_PROPERTY}.
     *
     * <ul>
     *   <li>{@code thread} — always plain thread-scoped storage (legacy). Never throws.</li>
     *   <li>{@code carrier} — carrier scoping is required: <b>throws</b> if
     *       {@code CarrierThreadLocal} is not accessible, rather than silently reintroducing
     *       the virtual-thread-pinned storage this class exists to remove.</li>
     *   <li>{@code auto} (default) — carrier scoping when available; otherwise falls back to
     *       thread-scoped storage. The fallback is expected on JDK &lt; 21 (silent); on a
     *       Loom-capable JVM it is logged loudly because it is the pre-fix behavior and is
     *       unsafe if virtual threads carry context.</li>
     * </ul>
     *
     * <p>Rationale for not failing hard by default: at profiler init we only know the JVM is
     * Loom-capable, not whether virtual threads will actually route context here, and the
     * runtime export that carrier scoping needs is granted by the agent — which may land after
     * this library. Failing hard by default would break profiler startup for every JDK 21+
     * deployment (including non-Loom apps) until that grant is in place. Callers that can
     * guarantee the export (and know they use Loom) should opt into {@code carrier} to get
     * fail-fast behavior.
     */
    static ThreadLocal<ThreadContext> create() {
        // Resolved once per JavaProfiler instance — this is the tlsContextStorage field
        // initializer, not a per-thread path. The per-thread get-or-init in JavaProfiler
        // (currentContext) never reads this property, so parsing it here is not a hot path.
        // Locale.ROOT: the values are ASCII keywords, so lower-casing must be locale-independent
        // (a default-locale toLowerCase() maps "CARRIER" to "carrıer" under tr_TR, breaking the match).
        String requested = System.getProperty(MODE_PROPERTY, "auto").trim().toLowerCase(Locale.ROOT);
        boolean forceThread = "thread".equals(requested);
        boolean requireCarrier = "carrier".equals(requested);

        if (forceThread) {
            return new ThreadLocal<>();
        }

        // "auto" or "carrier": prefer carrier scoping when the internal type is reachable.
        ThreadLocal<ThreadContext> carrier = tryCreateCarrierLocal();
        if (carrier != null) {
            return carrier;
        }

        // Carrier scoping unavailable (JDK < 21, or the jdk.internal.misc export not granted).
        if (requireCarrier) {
            throw new IllegalStateException("ddprof: -D" + MODE_PROPERTY + "=carrier requires "
                    + INTERNAL_CTL + ", which is not accessible. On JDK 21+ add "
                    + "--add-exports java.base/jdk.internal.misc=ALL-UNNAMED (a -javaagent can grant "
                    + "this via Instrumentation.redefineModule). Falling back to thread-scoped storage "
                    + "would re-expose the virtual-thread context use-after-free; set -D"
                    + MODE_PROPERTY + "=thread to explicitly accept legacy thread-scoped storage.");
        }

        // auto: degrade so profiling still loads, but be loud on Loom-capable JVMs where the
        // fallback can misattribute or corrupt context under virtual threads.
        if (Platform.isJavaVersionAtLeast(21)) {
            System.out.println("[WARN] ddprof: carrier-scoped OTEL context storage is unavailable on a "
                    + "JDK 21+ JVM (" + INTERNAL_CTL + " not accessible); falling back to thread-scoped "
                    + "storage. Under virtual threads this can misattribute context and, if a carrier "
                    + "thread exits, corrupt native memory. Add "
                    + "--add-exports java.base/jdk.internal.misc=ALL-UNNAMED, set -D" + MODE_PROPERTY
                    + "=carrier to fail fast instead, or -D" + MODE_PROPERTY + "=thread to silence this.");
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
