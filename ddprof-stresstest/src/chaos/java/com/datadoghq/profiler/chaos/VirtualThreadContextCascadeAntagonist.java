/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler.chaos;

import datadog.trace.api.Trace;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.time.Duration;
import java.util.concurrent.Executor;
import java.util.concurrent.Semaphore;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Simulates a tracer's context propagation across a cascade of short-lived virtual threads, and
 * deliberately races the carrier-thread churn needed to expose a stale-carrier use-after-free.
 *
 * <p>Unlike a hand-rolled context simulation, every context write here is driven by the real
 * Datadog tracer: {@link #runCascadeNode}/{@link #nestedOp}/{@link #staleRacerBefore}/{@link
 * #staleRacerAfter} are {@link Trace}-annotated methods. Under a {@code dd-java-agent}-
 * instrumented JVM the tracer intercepts each one, activating a real span on entry ({@code
 * JavaProfiler.setContext}) and deactivating it on exit ({@code clearContext}) — exactly what a
 * genuinely-instrumented application does. {@code dd-trace-api} is a {@code compileOnly}
 * dependency (see {@code TraceContextAntagonist}): at runtime the patched {@code dd-java-agent}
 * provides the (relocated) classes and intercepts the annotation, so this antagonist never touches
 * {@code com.datadoghq.profiler.*} directly.
 *
 * <p>Each cascade node ({@link #runCascadeNode}) runs a handful of nested sub-operations, each
 * activating a new child span and sleeping briefly ({@link #forceUnmount}) to force the virtual
 * thread off its current carrier before the span's exit (and the next nested entry) write context
 * again — the high context-change-rate dimension. It then fans out to child virtual threads while
 * its own span is still active, handing the tracer's own async/virtual-thread instrumentation the
 * job of propagating that span as parent context onto the next hop (the chain continues on a new
 * thread/carrier). On exit, the span's close restores whatever was logically active underneath it.
 *
 * <p>A second, independent driver ({@link #pinningChurnLoop()}) continuously pins short-lived
 * virtual threads to their carrier (a {@code synchronized} block held across a blocking sleep)
 * across a rotating set of monitors, forcing the JDK's virtual-thread scheduler to spin up extra
 * compensating carrier platform threads while the pins are held.
 *
 * <p>Targets: {@code com.datadoghq.profiler.OtelContextStorage}'s {@code ContextStorageMode.THREAD}
 * fallback (the default on JDK 21+ without {@code --add-exports
 * java.base/jdk.internal.misc=ALL-UNNAMED}). Under that mode the {@code DirectByteBuffer} conduit
 * for a virtual thread's OTEL context (which backs both the span id fields written by {@code
 * setContext} and any custom attributes) is cached in a plain {@code ThreadLocal} the first time
 * the thread writes context, bound to whichever carrier happened to be mounted at that moment; the
 * conduit wraps memory embedded directly inside that carrier's native {@code ProfiledThread}
 * (see {@code threadLocalData.h}), which is {@code delete}d — a real {@code free()} — the moment
 * the carrier's JVMTI {@code ThreadEnd} fires. The nested-op loop in {@link #runCascadeNode} races
 * this cheaply: a nested span's entry writes, {@link #forceUnmount} forces a short real unmount,
 * then the span's exit (or the next nested entry) writes again — if the virtual thread was
 * remounted elsewhere, that second write reuses the (possibly now-stale) cached conduit.
 *
 * <p>Catching genuine memory reuse (not just misattribution) needs the <em>original</em> carrier
 * to actually be torn down first. {@link #driverLoop} runs a duty cycle for the cascade/pin-churn
 * side only (a short active burst followed by a quiet phase with no new work, long enough for the
 * JDK's default {@code ForkJoinPool} scheduler — 30s keep-alive, see {@code
 * java.lang.VirtualThread#createDefaultScheduler()} — to actually reap idle carriers). Stale-
 * buffer racers ({@link #runStaleBufferRacer}) don't wait on that: every racer runs on a virtual
 * thread bound to a purpose-built {@link #fastCarrierScheduler} — a {@link ThreadPoolExecutor}
 * with a 200ms keep-alive — via the package-private {@code VirtualThread(Executor, String, int,
 * Runnable)} constructor (JDK 21+; see {@code java.lang.VirtualThread}, requires {@code
 * --add-opens java.base/java.lang=ALL-UNNAMED}). {@link #staleRacerLoop} keeps up to {@link
 * #MAX_STALE_RACERS} of these racers in flight continuously, independent of the cascade/pin duty
 * cycle above — sustained concurrent hammering rather than one batch per cycle, since more
 * concurrent carrier churn means more chances for a freed {@code ProfiledThread} slot to actually
 * get reused before a stale racer touches it. Each racer writes context once ({@link
 * #staleRacerBefore}), sleeps a randomized interval straddling the scheduler's keep-alive ({@link
 * #FAST_STALE_RACER_SLEEP_MIN_MILLIS}–{@link #FAST_STALE_RACER_SLEEP_MAX_MILLIS}), then writes
 * again ({@link #staleRacerAfter}) — varying the wait means a run samples both "carrier likely
 * still tearing down" and "carrier long gone, memory possibly already reused" timings, instead of
 * only ever probing one fixed instant.
 *
 * <p>Reflectively detects {@code Thread.ofVirtual()} (Java 21+); gracefully no-ops the whole
 * antagonist on older runtimes where it's absent. But on a JDK where it <em>is</em> present, the
 * {@code VirtualThread} constructor above is required, not optional: it's this antagonist's only
 * way to reach the stale-carrier UAF without a slow duty-cycle wait, so {@link #start} fails fast
 * with an {@link IllegalStateException} (crashing the chaos harness process, which the CI runner
 * already treats as a failure) rather than silently losing that coverage if a missing {@code
 * --add-opens} flag or a JDK build that changed the constructor's signature makes it
 * unreachable. Live virtual thread count is bounded by semaphore permit pools so cascades,
 * pinning churn, and stale-buffer racers cannot runaway the JVM.
 */
public final class VirtualThreadContextCascadeAntagonist implements Antagonist {

    private static final Method OF_VIRTUAL = resolveOfVirtual();
    private static final Method BUILDER_START = resolveBuilderStart();

    private static final int FAN_OUT = 3;
    private static final int MAX_DEPTH = 4;
    private static final int NESTED_OPS_PER_HOP = 3;
    private static final int MAX_LIVE_VTHREADS = 512;
    private static final int ROOT_BATCH = 16;

    // Carrier-pinning churn: rotating monitors held across a blocking sleep to force the
    // scheduler to spin up (and later reap) compensating carrier platform threads.
    private static final int PIN_LOCK_COUNT = 32;
    private static final int PIN_BATCH = 24;
    private static final int MAX_PIN_VTHREADS = 128;
    private static final Object[] PIN_LOCKS = new Object[PIN_LOCK_COUNT];

    static {
        for (int i = 0; i < PIN_LOCK_COUNT; i++) {
            PIN_LOCKS[i] = new Object();
        }
    }

    // Duty cycle driving genuine carrier teardown: an active burst of cascade/pin-churn work,
    // then a quiet phase long enough to clear the JDK's default 30s carrier keep-alive so idle
    // carriers actually exit before the stale-buffer racers spawned in the burst wake back up.
    private static final long ACTIVE_PHASE_MILLIS = 8_000L;
    private static final long QUIET_PHASE_MILLIS = 40_000L;

    // Stale-buffer racers run continuously on their own driver, decoupled from the cascade/pin
    // duty cycle above — that cycle only exists to let the JDK default scheduler's 30s keep-alive
    // reap cascade/pin carriers, which is irrelevant to racers bound to fastCarrierScheduler.
    private static final int STALE_RACER_BATCH = 64;
    private static final int MAX_STALE_RACERS = 1024;

    // A short keep-alive forces genuine carrier-thread exit (and thus a real ProfiledThread
    // free()) in well under a second instead of 30s. The racer's sleep is randomized across a
    // range straddling this keep-alive so runs cover both "carrier likely still exiting" and
    // "carrier long gone, memory possibly already reused" timings instead of one fixed instant.
    private static final long FAST_SCHEDULER_KEEPALIVE_MILLIS = 200L;
    private static final long FAST_STALE_RACER_SLEEP_MIN_MILLIS = 50L;
    private static final long FAST_STALE_RACER_SLEEP_MAX_MILLIS = FAST_SCHEDULER_KEEPALIVE_MILLIS * 4;

    // Caps the fast-carrier pool's platform-thread growth. MAX_STALE_RACERS is
    // already the hard ceiling on concurrent virtual threads that could each
    // need a carrier, so this doesn't reduce headroom — it just removes the
    // unbounded-growth characteristic of Integer.MAX_VALUE.
    private static final int MAX_FAST_CARRIER_THREADS = MAX_STALE_RACERS;

    private static final Constructor<?> VTHREAD_CTOR = resolveVirtualThreadCtor();

    private final Semaphore liveVthreads = new Semaphore(MAX_LIVE_VTHREADS);
    private final Semaphore livePinVthreads = new Semaphore(MAX_PIN_VTHREADS);
    private final Semaphore liveStaleRacers = new Semaphore(MAX_STALE_RACERS);
    private final Executor fastCarrierScheduler = VTHREAD_CTOR != null ? newFastCarrierScheduler() : null;
    private volatile boolean running;
    private volatile boolean activePhase = true;
    private Thread driver;
    private Thread pinningDriver;
    private Thread staleRacerDriver;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "vthread-context-cascade";
    }

    @Override
    public void start() {
        if (OF_VIRTUAL != null && BUILDER_START != null && VTHREAD_CTOR == null) {
            // We're on a VT-capable JDK, so the fast-carrier constructor should be reachable —
            // its absence (missing --add-opens, or a JDK build that changed the constructor)
            // would otherwise silently drop stale-racer coverage instead of failing the run.
            throw new IllegalStateException(
                    "vthread-context-cascade: java.lang.VirtualThread(Executor, String, int, "
                            + "Runnable) is unreachable on a VT-capable JDK — pass --add-opens "
                            + "java.base/java.lang=ALL-UNNAMED, or this antagonist loses its core "
                            + "stale-carrier UAF coverage");
        }
        running = true;
        driver = new Thread(this::driverLoop, "chaos-vthread-cascade-driver");
        driver.setDaemon(true);
        driver.start();
        pinningDriver = new Thread(this::pinningChurnLoop, "chaos-vthread-cascade-pin-driver");
        pinningDriver.setDaemon(true);
        pinningDriver.start();
        staleRacerDriver = new Thread(this::staleRacerLoop, "chaos-vthread-cascade-racer-driver");
        staleRacerDriver.setDaemon(true);
        staleRacerDriver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        long deadlineNanos = System.nanoTime() + timeout.toNanos();
        // Driver threads are only non-null once start() has actually spawned them; guard against
        // stopGracefully being called when start() never ran or failed partway through.
        if (driver != null) {
            try {
                driver.join(remainingMillis(deadlineNanos));
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        if (pinningDriver != null) {
            try {
                pinningDriver.join(remainingMillis(deadlineNanos));
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        if (staleRacerDriver != null) {
            try {
                staleRacerDriver.join(remainingMillis(deadlineNanos));
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        // Best-effort drain of in-flight cascades so the JVM doesn't exit mid-fan-out.
        try {
            liveVthreads.tryAcquire(MAX_LIVE_VTHREADS, remainingMillis(deadlineNanos), TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        try {
            livePinVthreads.tryAcquire(MAX_PIN_VTHREADS, remainingMillis(deadlineNanos), TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        // Stale-buffer racers sleep well past stopGracefully's own timeout budget, so this is
        // best-effort only — outstanding racers are daemon threads and die with the JVM.
        try {
            liveStaleRacers.tryAcquire(MAX_STALE_RACERS, remainingMillis(deadlineNanos), TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    /** Milliseconds remaining until {@code deadlineNanos}, clamped to zero (never negative). */
    private static long remainingMillis(long deadlineNanos) {
        long remainingNanos = deadlineNanos - System.nanoTime();
        return remainingNanos <= 0L ? 0L : TimeUnit.NANOSECONDS.toMillis(remainingNanos);
    }

    /**
     * Independently pins short-lived virtual threads to their carrier and releases them again,
     * forcing the scheduler to grow and shrink its compensating carrier pool while cascade nodes
     * are racing carrier migration on the other driver.
     */
    private void pinningChurnLoop() {
        if (OF_VIRTUAL == null || BUILDER_START == null) {
            return;
        }
        while (running) {
            if (!activePhase) {
                // Quiet phase: stay out of the way so idle carriers can actually be reaped.
                try {
                    Thread.sleep(50L);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
                continue;
            }
            for (int i = 0; i < PIN_BATCH && running && activePhase; i++) {
                if (!livePinVthreads.tryAcquire()) {
                    continue;
                }
                final Object lock = PIN_LOCKS[ThreadLocalRandom.current().nextInt(PIN_LOCK_COUNT)];
                try {
                    Object builder = OF_VIRTUAL.invoke(null);
                    BUILDER_START.invoke(
                            builder,
                            (Runnable)
                                    () -> {
                                        try {
                                            synchronized (lock) {
                                                // Sleeping while holding a monitor pins the
                                                // carrier: the scheduler must compensate with an
                                                // extra platform thread for other runnable
                                                // virtual threads, then reap it once idle.
                                                Thread.sleep(2L);
                                            }
                                        } catch (InterruptedException e) {
                                            Thread.currentThread().interrupt();
                                        } finally {
                                            livePinVthreads.release();
                                        }
                                    });
                } catch (Throwable t) {
                    livePinVthreads.release();
                }
            }
            try {
                Thread.sleep(1L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    private void driverLoop() {
        if (OF_VIRTUAL == null || BUILDER_START == null) {
            System.out.println("[chaos] vthread-context-cascade: skipping (Thread.ofVirtual not available)");
            return;
        }
        while (running) {
            // Active phase: mint cascade work.
            activePhase = true;
            long activeDeadlineNanos = System.nanoTime() + Duration.ofMillis(ACTIVE_PHASE_MILLIS).toNanos();
            while (running && System.nanoTime() < activeDeadlineNanos) {
                for (int i = 0; i < ROOT_BATCH && running; i++) {
                    // Mint one chain-of-operations: a fresh synthetic trace, its root span
                    // activated by the tracer the moment runCascadeNode is entered.
                    spawnCascadeNode(0);
                }
                try {
                    Thread.sleep(1L);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
            if (!running) {
                return;
            }
            // Quiet phase: mint nothing new so short-lived virtual threads drain and carriers
            // can actually sit idle past the scheduler's 30s keep-alive and get reaped.
            activePhase = false;
            try {
                Thread.sleep(QUIET_PHASE_MILLIS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    /**
     * Independent driver that keeps the stale-buffer racer population saturated at {@link
     * #MAX_STALE_RACERS} for as long as the antagonist runs, regardless of the cascade/pin duty
     * cycle — the fast-carrier scheduler needs no quiet phase to reap its carriers, so there's no
     * reason to gate racer spawning on one. This is the "many vthreads hammering" dimension:
     * sustained concurrent pressure on the fast-carrier scheduler's pool, not periodic bursts.
     */
    private void staleRacerLoop() {
        while (running) {
            boolean spawnedAny = spawnStaleBufferRacers();
            try {
                // Once the pool is fully saturated, back off instead of re-polling 1000x/sec for
                // permits that free up far slower (racers sleep up to FAST_STALE_RACER_SLEEP_MAX_MILLIS).
                Thread.sleep(spawnedAny ? 1L : 20L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    /** Returns whether at least one racer was actually started this pass. */
    private boolean spawnStaleBufferRacers() {
        boolean spawnedAny = false;
        for (int i = 0; i < STALE_RACER_BATCH && running; i++) {
            if (!liveStaleRacers.tryAcquire()) {
                continue;
            }
            if (startFastCarrierVirtualThread(this::runStaleBufferRacer) == null) {
                liveStaleRacers.release();
            } else {
                spawnedAny = true;
            }
        }
        return spawnedAny;
    }

    /**
     * Activates a span once, sleeps past the carrier's keep-alive, then activates another. Under
     * {@code ContextStorageMode.THREAD} the second activation reuses whatever {@code
     * DirectByteBuffer} was cached on the first — if the original carrier has since been reaped
     * and its {@code ProfiledThread} memory reused, this is a genuine use-after-free.
     *
     * <p>The sleep is randomized per racer across [{@link #FAST_STALE_RACER_SLEEP_MIN_MILLIS},
     * {@link #FAST_STALE_RACER_SLEEP_MAX_MILLIS}] rather than fixed, so a sustained run samples a
     * spread of timings relative to {@link #FAST_SCHEDULER_KEEPALIVE_MILLIS} instead of only ever
     * probing the same instant.
     */
    private void runStaleBufferRacer() {
        try {
            staleRacerBefore();
            long sleepMillis =
                    ThreadLocalRandom.current()
                            .nextLong(
                                    FAST_STALE_RACER_SLEEP_MIN_MILLIS,
                                    FAST_STALE_RACER_SLEEP_MAX_MILLIS + 1);
            Thread.sleep(sleepMillis);
            staleRacerAfter();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            liveStaleRacers.release();
        }
    }

    @Trace(operationName = "chaos.stale.before", resourceName = "chaos.stale.before")
    private void staleRacerBefore() {
        // Entry/exit alone is the "write" — the tracer activates/deactivates a span around this
        // no-op body, exactly like TraceContextAntagonist's inner()/outer().
    }

    @Trace(operationName = "chaos.stale.after", resourceName = "chaos.stale.after")
    private void staleRacerAfter() {}

    /** Spawns one virtual thread to run a cascade node, respecting the live-thread budget. */
    private void spawnCascadeNode(int depth) {
        if (!running || !liveVthreads.tryAcquire()) {
            return;
        }
        try {
            Object builder = OF_VIRTUAL.invoke(null);
            BUILDER_START.invoke(
                    builder,
                    (Runnable)
                            () -> {
                                try {
                                    runCascadeNode(depth);
                                } finally {
                                    liveVthreads.release();
                                }
                            });
        } catch (Throwable t) {
            liveVthreads.release();
        }
    }

    /**
     * One hop of the cascade, run as its own {@link Trace}-annotated span on a fresh virtual
     * thread. The tracer activates this span on entry and deactivates it on exit; while it's
     * active, this hop fans out to child hops on new virtual threads, handing the tracer's own
     * virtual-thread instrumentation the job of propagating it as parent context onto each child.
     */
    @Trace(operationName = "chaos.cascade.hop", resourceName = "chaos.cascade.hop")
    private void runCascadeNode(int depth) {
        long r = ThreadLocalRandom.current().nextLong() ^ ((long) depth << 48);
        for (int op = 0; op < NESTED_OPS_PER_HOP && running; op++) {
            r = nestedOp(r);
        }
        sink.addAndGet(r);

        // Propagate the chain to the next hop before this thread's own span is torn down.
        if (depth < MAX_DEPTH && running) {
            for (int i = 0; i < FAN_OUT; i++) {
                spawnCascadeNode(depth + 1);
            }
        }
    }

    /**
     * A nested sub-operation within a hop: the tracer activates a child span on entry, {@link
     * #forceUnmount} sleeps briefly to force the virtual thread off its current carrier, then the
     * span's exit (or the next nested entry) writes context again — racing carrier migration
     * against the cached context conduit.
     */
    @Trace(operationName = "chaos.cascade.op", resourceName = "chaos.cascade.op")
    private long nestedOp(long seed) {
        return forceUnmount(seed);
    }

    /**
     * Burns some CPU (a stand-in for real work) then blocks briefly, forcing the virtual thread
     * to genuinely unmount. On resumption it may be remounted on a different carrier than the
     * one it was on when the context before this call was written.
     */
    private static long forceUnmount(long seed) {
        long r = seed;
        for (int i = 0; i < 2_000; i++) {
            r = r * 6364136223846793005L + 1442695040888963407L;
        }
        try {
            Thread.sleep(1L + (r & 1));
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        return r;
    }

    /**
     * Resolves {@code java.lang.VirtualThread}'s package-private {@code (Executor, String, int,
     * Runnable)} constructor, the only way to bind a virtual thread to a custom scheduler on
     * mainline OpenJDK 21+ (there is no public {@code Thread.ofVirtual().scheduler(Executor)}
     * API). Requires {@code --add-opens java.base/java.lang=ALL-UNNAMED}; returns {@code null}
     * (caller falls back to the default-scheduler path) if that flag is absent, the JVM is
     * pre-21, or the constructor's signature changes on some future JDK build.
     */
    private static Constructor<?> resolveVirtualThreadCtor() {
        try {
            Class<?> vthreadClass = Class.forName("java.lang.VirtualThread");
            Constructor<?> ctor =
                    vthreadClass.getDeclaredConstructor(
                            Executor.class, String.class, int.class, Runnable.class);
            ctor.setAccessible(true);
            return ctor;
        } catch (Throwable t) {
            return null;
        }
    }

    /**
     * A carrier pool with a short keep-alive instead of the JDK default scheduler's fixed 30s, so
     * an idle carrier's OS thread actually exits (and its {@code ProfiledThread} is freed) in
     * well under a second.
     */
    private static Executor newFastCarrierScheduler() {
        return new ThreadPoolExecutor(
                0,
                MAX_FAST_CARRIER_THREADS,
                FAST_SCHEDULER_KEEPALIVE_MILLIS,
                TimeUnit.MILLISECONDS,
                new SynchronousQueue<>(),
                r -> {
                    Thread carrier = new Thread(r, "chaos-vthread-cascade-fast-carrier");
                    carrier.setDaemon(true);
                    return carrier;
                });
    }

    /**
     * Starts {@code task} on a virtual thread bound to {@link #fastCarrierScheduler}. Returns
     * {@code null} (never starts anything) if {@link #VTHREAD_CTOR} wasn't resolved or the
     * reflective construction fails; {@link #start} already fails fast when {@link #VTHREAD_CTOR}
     * is unreachable on a VT-capable JDK, so callers here only need to handle the rarer
     * construction-failure case (e.g. transient reflection errors).
     *
     * <p>{@code 0} for the characteristics argument mirrors {@code Thread.ofVirtual()}'s default
     * (the only known bit, {@code Thread.NO_INHERIT_THREAD_LOCALS}, is unset).
     */
    private Thread startFastCarrierVirtualThread(Runnable task) {
        if (VTHREAD_CTOR == null) {
            return null;
        }
        try {
            Thread t = (Thread) VTHREAD_CTOR.newInstance(fastCarrierScheduler, null, 0, task);
            t.start();
            return t;
        } catch (Throwable t) {
            return null;
        }
    }

    private static Method resolveOfVirtual() {
        try {
            return Thread.class.getMethod("ofVirtual");
        } catch (NoSuchMethodException e) {
            return null;
        }
    }

    private static Method resolveBuilderStart() {
        try {
            Class<?> builder = Class.forName("java.lang.Thread$Builder");
            return builder.getMethod("start", Runnable.class);
        } catch (ClassNotFoundException | NoSuchMethodException e) {
            return null;
        }
    }
}
