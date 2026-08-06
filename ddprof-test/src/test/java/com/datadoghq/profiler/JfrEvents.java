/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import io.jafar.parser.api.JafarParser;
import io.jafar.parser.api.UntypedJafarParser;
import io.jafar.parser.api.Values;

import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Stream;

/**
 * A queryable collection of parsed JFR events, backed by the jafar parser instead of JDK
 * Mission Control's {@code FlightRecordingLoader}.
 *
 * <p>JMC's loader parses chunks on an internal thread pool via an
 * {@code ExecutorCompletionService}; if a worker dies from an uncaught {@link OutOfMemoryError}
 * mid-parse, the main thread's {@code take()} blocks forever waiting for a result that will never
 * arrive (confirmed root cause of CI hangs in {@code BoundMethodHandleProfilerTest} on
 * aarch64/JDK25 debug builds). jafar's {@code UntypedJafarParser.run()} is synchronous and single-
 * threaded from the caller's perspective — a worker failure surfaces as a propagated exception
 * from {@code run()}, never a silent hang.
 */
public final class JfrEvents implements Iterable<JfrEvent> {
    private final List<JfrEvent> events;

    private JfrEvents(List<JfrEvent> events) {
        this.events = events;
    }

    /**
     * Parses every event in {@code recording} into memory. Prefer {@link #load(Path, String)} or
     * {@link #load(Path, Predicate)} when only specific event types are needed: this loads and
     * deep-resolves every event of every type in the recording, which for a high-volume
     * recording (e.g. allocation/GC-heavy runs) can exceed a constrained test heap even when the
     * caller only cares about one small event type.
     */
    public static JfrEvents load(Path recording) throws Exception {
        return load(recording, typeName -> true);
    }

    /** Parses only events whose type name equals {@code eventType}, skipping resolution of the rest. */
    public static JfrEvents load(Path recording, String eventType) throws Exception {
        return load(recording, eventType::equals);
    }

    /** Retries for a recording read right after {@code JavaProfiler.stop()}/{@code dump()} racing the JFR chunk flush. */
    private static final int LOAD_RETRIES = 5;
    private static final long LOAD_RETRY_BACKOFF_MILLIS = 20;

    /**
     * Parses only events whose type name matches {@code typeFilter}, skipping resolution of the
     * rest. For more than one type, pass a {@code Set<String>::contains} or an {@code
     * Arrays.asList(...)::contains}. Checking {@code type.getName()} against the filter before
     * calling {@code Values.resolvedDeep()} is what keeps this streaming rather than
     * materializing the whole recording: the expensive deep per-field walk only runs for events
     * we actually keep.
     *
     * <p>Retries with a small linear backoff on {@link IOException}: a test reading the recording
     * immediately after {@code stopProfiler()}/{@code dump()} can race the native side finishing
     * its last chunk flush, which jafar's single-pass streaming parser surfaces as a hard parse
     * failure rather than tolerating (confirmed by re-opening the exact same file moments later —
     * it parses cleanly once the flush has landed).
     */
    public static JfrEvents load(Path recording, Predicate<String> typeFilter) throws Exception {
        return load(recording, typeFilter, e -> false);
    }

    /**
     * Like {@link #load(Path, Predicate)}, but stops parsing early once {@code stopWhen} returns
     * {@code true} for a kept event — via jafar's {@code Control.abort()}, checked by
     * {@code EventStream.onEvent()} right after our handler returns. This skips the rest of the
     * <em>current</em> chunk only: {@code StreamingChunkParser.parse()} submits every chunk's
     * parsing task up front, so any chunk already queued still runs to completion. For the
     * single-{@code dump()} recordings this test suite produces (one dump is one chunk in
     * practice), that makes {@code stopWhen} an effective full early-exit — useful for callers
     * like {@code verifyStackTraces()} that only need a prefix of a high-volume event type.
     *
     * <p>A multi-chunk recording has each chunk's {@code parser.handle()} callback invoked from a
     * different worker of jafar's internal chunk-parsing thread pool ({@code
     * StreamingChunkParser} submits one parsing task per chunk before joining any of them), so the
     * per-event handling below is wrapped in a {@code synchronized} block to serialize the shared
     * {@code events} list mutation (and the {@code stopWhen}/{@code ctl.abort()} pair, so a
     * concurrent chunk can't abort mid-check) across chunks.
     */
    public static JfrEvents load(Path recording, Predicate<String> typeFilter, Predicate<JfrEvent> stopWhen)
            throws Exception {
        IOException lastFailure = null;
        for (int attempt = 0; attempt < LOAD_RETRIES; attempt++) {
            if (attempt > 0) {
                Thread.sleep(LOAD_RETRY_BACKOFF_MILLIS * attempt);
            }
            List<JfrEvent> events = new ArrayList<>();
            Object lock = new Object();
            try (UntypedJafarParser parser = JafarParser.newUntypedParser(recording)) {
                parser.handle((type, value, ctl) -> {
                    if (typeFilter.test(type.getName())) {
                        JfrEvent event = new JfrEvent(type.getName(), collapseSimpleTypes(Values.resolvedDeep(value)));
                        synchronized (lock) {
                            events.add(event);
                            if (stopWhen.test(event)) {
                                ctl.abort();
                            }
                        }
                    }
                });
                parser.run();
                return new JfrEvents(events);
            } catch (IOException e) {
                lastFailure = e;
                System.err.println("JfrEvents.load: retrying " + recording + " after parse failure (attempt "
                        + (attempt + 1) + "/" + LOAD_RETRIES + "): " + e);
            }
        }
        throw lastFailure;
    }

    /**
     * Streams matching events through {@code consumer} one at a time without ever retaining more
     * than one in memory, for callers that only need per-event checks and/or a count (e.g.
     * {@code NativememSampledProfilerTest}'s per-sample field validation) rather than the
     * materialized collection {@link #load} returns. Retries the whole parse on {@link IOException}
     * exactly like {@link #load}, so {@code consumer} may see a subset of a failed attempt's events
     * before a retry starts over from zero — it must be idempotent (e.g. plain per-event
     * assertions), not accumulate state that would double-count across attempts. Returns the
     * number of events streamed from the attempt that ultimately succeeded.
     *
     * <p>As with {@link #load(Path, Predicate, Predicate)}, a multi-chunk recording can invoke this
     * per-event callback from several jafar chunk-parsing worker threads at once, so the call to
     * {@code consumer} and the shared counter update are wrapped in a {@code synchronized} block:
     * {@code consumer} is thus never invoked concurrently, and only needs to be idempotent across
     * retries (see above), not thread-safe.
     */
    public static long forEach(Path recording, Predicate<String> typeFilter, Consumer<JfrEvent> consumer)
            throws Exception {
        IOException lastFailure = null;
        for (int attempt = 0; attempt < LOAD_RETRIES; attempt++) {
            if (attempt > 0) {
                Thread.sleep(LOAD_RETRY_BACKOFF_MILLIS * attempt);
            }
            long[] count = {0};
            Object lock = new Object();
            try (UntypedJafarParser parser = JafarParser.newUntypedParser(recording)) {
                parser.handle((type, value, ctl) -> {
                    if (typeFilter.test(type.getName())) {
                        JfrEvent event = new JfrEvent(type.getName(), collapseSimpleTypes(Values.resolvedDeep(value)));
                        synchronized (lock) {
                            consumer.accept(event);
                            count[0]++;
                        }
                    }
                });
                parser.run();
                return count[0];
            } catch (IOException e) {
                lastFailure = e;
                System.err.println("JfrEvents.forEach: retrying " + recording + " after parse failure (attempt "
                        + (attempt + 1) + "/" + LOAD_RETRIES + "): " + e);
            }
        }
        throw lastFailure;
    }

    /**
     * Like {@link #forEach}, but for callers that fold matching events into an accumulator (e.g.
     * {@code NativeLibrariesTest}'s per-mode/per-library sample counts) instead of running
     * independent per-event checks. {@code initial} is called fresh at the start of every attempt
     * so a retry after an {@link IOException} starts accumulation over, rather than double-counting
     * events an earlier, failed attempt already folded in.
     *
     * <p>As with {@link #load(Path, Predicate, Predicate)}, a multi-chunk recording can invoke this
     * per-event callback from several jafar chunk-parsing worker threads at once, so the call to
     * {@code accumulator} is wrapped in a {@code synchronized} block: {@code accumulator} is thus
     * never invoked concurrently, so folding into {@code acc} (e.g. a plain {@code HashMap}) is
     * safe without {@code acc} itself needing to be a concurrent collection.
     */
    public static <T> T reduce(Path recording, Predicate<String> typeFilter, Supplier<T> initial,
            BiConsumer<T, JfrEvent> accumulator) throws Exception {
        IOException lastFailure = null;
        for (int attempt = 0; attempt < LOAD_RETRIES; attempt++) {
            if (attempt > 0) {
                Thread.sleep(LOAD_RETRY_BACKOFF_MILLIS * attempt);
            }
            T acc = initial.get();
            Object lock = new Object();
            try (UntypedJafarParser parser = JafarParser.newUntypedParser(recording)) {
                parser.handle((type, value, ctl) -> {
                    if (typeFilter.test(type.getName())) {
                        JfrEvent event = new JfrEvent(type.getName(), collapseSimpleTypes(Values.resolvedDeep(value)));
                        synchronized (lock) {
                            accumulator.accept(acc, event);
                        }
                    }
                });
                parser.run();
                return acc;
            } catch (IOException e) {
                lastFailure = e;
                System.err.println("JfrEvents.reduce: retrying " + recording + " after parse failure (attempt "
                        + (attempt + 1) + "/" + LOAD_RETRIES + "): " + e);
            }
        }
        throw lastFailure;
    }

    /**
     * Collapses any single-entry {@code Map} produced by {@code Values.resolvedDeep()} down to
     * its lone value, recursively. JFR's own metadata marks certain constant-pool-referenced
     * types "simple" (JDK's own {@code jdk.types.Symbol}/{@code java.lang.String} CPOOL entries,
     * and this profiler's own {@code jdk.types.ThreadState}/{@code datadog.types.ExecutionMode}/
     * {@code profiler.types.CounterName}/{@code profiler.types.AttributeValue} single-field
     * wrapper types) meaning they should read as a plain scalar, not a wrapper struct. jafar's
     * {@code MetadataClass.isSimpleType()} tracks this internally, but the untyped/{@code Values}
     * API doesn't expose or apply it — so we collapse structurally instead: every "simple" type
     * this profiler emits happens to be single-field, and no genuine multi-field JFR type is
     * ever single-field, so "exactly one entry" is an exact (not heuristic) match for "simple".
     */
    private static Map<String, Object> collapseSimpleTypes(Map<String, Object> root) {
        for (Map.Entry<String, Object> e : root.entrySet()) {
            e.setValue(collapseValue(e.getValue()));
        }
        return root;
    }

    /**
     * Mutates {@code v} in place rather than building a parallel copy: {@code Values.resolvedDeep()}
     * (see its source) always allocates fresh, exclusively-owned {@code Map}/{@code Object[]}
     * instances at every recursion level, so nothing else retains a reference to them and
     * overwriting entries/elements here is safe.
     */
    @SuppressWarnings("unchecked")
    private static Object collapseValue(Object v) {
        if (v instanceof Map) {
            Map<String, Object> m = (Map<String, Object>) v;
            if (m.size() == 1) {
                return collapseValue(m.values().iterator().next());
            }
            for (Map.Entry<String, Object> e : m.entrySet()) {
                e.setValue(collapseValue(e.getValue()));
            }
            return m;
        }
        if (v instanceof Object[]) {
            Object[] arr = (Object[]) v;
            for (int i = 0; i < arr.length; i++) {
                arr[i] = collapseValue(arr[i]);
            }
            return arr;
        }
        return v;
    }

    /** {@code true} if this collection contains at least one event. */
    public boolean hasItems() {
        return !events.isEmpty();
    }

    /** The number of events in this collection. */
    public long count() {
        return events.size();
    }

    /** A new collection containing only events whose type name equals {@code typeName}. */
    public JfrEvents byType(String typeName) {
        return filter(e -> e.typeName().equals(typeName));
    }

    /** A new collection containing only the events for which {@code predicate} returns {@code true}. */
    public JfrEvents filter(Predicate<JfrEvent> predicate) {
        List<JfrEvent> filtered = new ArrayList<>();
        for (JfrEvent e : events) {
            if (predicate.test(e)) {
                filtered.add(e);
            }
        }
        return new JfrEvents(filtered);
    }

    /** A {@link Stream} over this collection's events, for callers preferring stream-style access. */
    public Stream<JfrEvent> stream() {
        return events.stream();
    }

    @Override
    public Iterator<JfrEvent> iterator() {
        return Collections.unmodifiableList(events).iterator();
    }
}
