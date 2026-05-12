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

import java.time.Duration;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

/**
 * Long-running chaos harness driving the reliability CI cell.
 *
 * <p>The harness is fully black-box with respect to the profiler: it runs as a
 * regular application under a {@code dd-java-agent.jar} that has been patched
 * with the locally built {@code ddprof.jar} (see {@code utils/patch-dd-java-agent.sh}).
 * That keeps the runtime classloader/relocation path identical to production
 * and avoids parallel-classloader conflicts when the agent loads its own
 * (relocated) profiler classes.
 *
 * <p>The only failure signal is a JVM crash (SIGSEGV/SIGABRT in the profiler
 * native code), which propagates as a non-zero exit code and an
 * {@code hs_err_pid*.log} captured by the reliability runner script.
 *
 * <p>Lifecycle:
 * <ol>
 *   <li>parse {@code --duration} (e.g. {@code 30m}, {@code 2h}) and {@code --antagonists}
 *   <li>start the requested antagonists, sleep until the deadline
 *   <li>stop antagonists, exit 0 on clean shutdown
 * </ol>
 */
public final class Main {

    public static void main(String[] args) throws Exception {
        Args parsed = Args.parse(args);
        log("starting duration=" + parsed.duration + " antagonists=" + parsed.antagonists);

        List<Antagonist> running = new ArrayList<>();
        for (String name : parsed.antagonists) {
            Antagonist a = create(name);
            a.start();
            running.add(a);
            log("antagonist started: " + a.name());
        }

        long deadlineNanos = System.nanoTime() + parsed.duration.toNanos();
        try {
            while (System.nanoTime() < deadlineNanos) {
                Thread.sleep(1_000L);
            }
        } finally {
            for (Antagonist a : running) {
                a.stopGracefully(Duration.ofSeconds(10));
            }
        }

        log("completed cleanly");
    }

    private static Antagonist create(String name) {
        switch (name) {
            case "thread-churn":
                return new ThreadChurnAntagonist();
            case "alloc-storm":
                return new AllocStormAntagonist();
            case "vthread-churn":
                return new VirtualThreadChurnAntagonist();
            case "classloader-churn":
                return new ClassLoaderChurnAntagonist();
            case "trace-context":
                return new TraceContextAntagonist();
            // Deferred: dlopen-churn (needs per-arch dummy .so built in CI prep).
            default:
                throw new IllegalArgumentException("unknown antagonist: " + name);
        }
    }

    private static void log(String msg) {
        System.out.println("[chaos] " + msg);
    }

    private static final class Args {
        Duration duration = Duration.ofMinutes(5);
        List<String> antagonists = new ArrayList<>(Arrays.asList("thread-churn"));

        static Args parse(String[] argv) {
            Args a = new Args();
            for (int i = 0; i < argv.length; i++) {
                switch (argv[i]) {
                    case "--duration":
                        a.duration = parseDuration(argv[++i]);
                        break;
                    case "--antagonists":
                        a.antagonists = Arrays.asList(argv[++i].split(","));
                        break;
                    default:
                        throw new IllegalArgumentException("unknown arg: " + argv[i]);
                }
            }
            return a;
        }

        // Accepts: 90s, 30m, 2h, or ISO-8601 like PT30M.
        private static Duration parseDuration(String s) {
            String t = s.trim().toLowerCase(Locale.ROOT);
            if (t.startsWith("pt")) return Duration.parse(t.toUpperCase(Locale.ROOT));
            char unit = t.charAt(t.length() - 1);
            long n = Long.parseLong(t.substring(0, t.length() - 1));
            switch (unit) {
                case 's': return Duration.ofSeconds(n);
                case 'm': return Duration.ofMinutes(n);
                case 'h': return Duration.ofHours(n);
                default: throw new IllegalArgumentException("bad duration: " + s);
            }
        }
    }
}
