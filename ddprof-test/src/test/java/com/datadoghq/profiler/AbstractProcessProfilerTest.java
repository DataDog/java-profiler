/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;
import java.util.function.Function;

import static org.junit.jupiter.api.Assertions.*;


public abstract class AbstractProcessProfilerTest {
    // Upper bound for joining each output reader thread once the child has exited (or been
    // destroyed). The readers normally hit EOF right after the child ends; the bound only stops a
    // descendant that inherited the pipes from keeping launch() from returning.
    private static final long READER_JOIN_TIMEOUT_MS = 10_000;

    /**
     * JaCoCo agent jar path, set by the coverage test tasks via JACOCO_AGENT_JAR environment
     * variable. When non-null, child JVMs are instrumented for coverage.
     */
    private static final String JACOCO_AGENT_JAR = System.getenv("JACOCO_AGENT_JAR");

    /**
     * Directory where child JVM JaCoCo execution data is written, set via JACOCO_CHILD_DIR.
     */
    private static final String JACOCO_CHILD_DIR = System.getenv("JACOCO_CHILD_DIR");

    /**
     * JaCoCo {@code includes} pattern list (':'-separated) restricting child JVM instrumentation
     * to ddprof-lib's classes, set via JACOCO_INCLUDES. When null, the agent instruments every
     * class it loads.
     */
    private static final String JACOCO_INCLUDES = System.getenv("JACOCO_INCLUDES");

    public static final class LaunchResult {
        public final boolean inTime;
        public final int exitCode;

        public LaunchResult(boolean inTime, int exitCode) {
            this.inTime = inTime;
            this.exitCode = exitCode;
        }
    }

    public enum LineConsumerResult {
        CONTINUE,
        STOP,
        IGNORE
    }

    /**
     * Scales a child-process wait budget for sanitizer builds (asan/tsan), whose native code runs
     * several times slower than debug/release.
     */
    protected static long childTimeoutSeconds(long baseSeconds) {
        String config = System.getProperty("ddprof_test.config");
        return config != null && config.endsWith("san") ? baseSeconds * 3 : baseSeconds;
    }

    protected final LaunchResult launch(String target, List<String> jvmArgs, String commands, Function<String, LineConsumerResult> onStdoutLine, Function<String, LineConsumerResult> onStderrLine) throws Exception {
        return launch(target, jvmArgs, commands, Collections.emptyMap(), onStdoutLine, onStderrLine);
    }

    protected final LaunchResult launch(String target, List<String> jvmArgs, String commands, Map<String, String> env, Function<String, LineConsumerResult> onStdoutLine, Function<String, LineConsumerResult> onStderrLine) throws Exception {
        return launch(target, jvmArgs, commands, env, 10, onStdoutLine, onStderrLine);
    }

    /**
     * Same as the 6-arg overload above, but with a caller-supplied wait timeout instead of the
     * hardcoded 10 seconds - needed by scenarios that run substantially longer than a plain
     * attach/init check, e.g. {@code ExternalProcessReferenceChainTest}'s population-growth loop
     * (up to 25 rounds plus a grace period, ~20s+ observed in-process, plus a whole separate
     * JVM's own startup/classloading cost on top).
     */
    protected final LaunchResult launch(String target, List<String> jvmArgs, String commands, Map<String, String> env, long timeoutSeconds, Function<String, LineConsumerResult> onStdoutLine, Function<String, LineConsumerResult> onStderrLine) throws Exception {
        String javaHome = System.getenv("JAVA_TEST_HOME");
        if (javaHome == null) {
            javaHome = System.getenv("JAVA_HOME");
        }
        if (javaHome == null) {
            javaHome = System.getProperty("java.home");
        }
        assertNotNull(javaHome);

        List<String> args = new ArrayList<>();
        args.add(javaHome + "/bin/java");
        args.addAll(jvmArgs);
        // Forward JaCoCo agent to child JVM for coverage collection if configured. It goes after
        // the test's own JVM args because the JVM loads agents in command-line order: a test's
        // -agentpath keeps running its Agent_OnLoad first, as it does without coverage.
        if (JACOCO_AGENT_JAR != null && JACOCO_CHILD_DIR != null) {
            // The name must be unique across every test JVM of the run (each forked test JVM
            // starts with fresh static state), so a per-JVM counter is not enough.
            String execFile = JACOCO_CHILD_DIR + "/child-" + UUID.randomUUID() + ".exec";
            String includes = JACOCO_INCLUDES != null ? ",includes=" + JACOCO_INCLUDES : "";
            args.add("-javaagent:" + JACOCO_AGENT_JAR + "=destfile=" + execFile + ",append=false" + includes);
        }
        args.add("-cp");
        args.add(System.getProperty("java.class.path"));
        args.add(ExternalLauncher.class.getName());
        args.add(target);
        if (commands != null && !commands.isEmpty()) {
            args.add(commands);
        }

        ProcessBuilder pb = new ProcessBuilder(args);
        pb.environment().putAll(env);
        Process p = pb.start();
        try {
            return awaitChild(p, timeoutSeconds, onStdoutLine, onStderrLine);
        } finally {
            // Covers an interrupted launch() as well as a child that outlived destroyForcibly().
            if (p.isAlive()) {
                p.destroyForcibly();
            }
        }
    }

    private static LaunchResult awaitChild(Process p, long timeoutSeconds, Function<String, LineConsumerResult> onStdoutLine, Function<String, LineConsumerResult> onStderrLine) throws Exception {
        Thread stdoutReader = new Thread(() -> {
            Function<String, LineConsumerResult> lineProcessor = onStdoutLine != null ? onStdoutLine : l -> LineConsumerResult.CONTINUE;
            try (BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()))) {
                String line;
                while ((line = br.readLine()) != null) {
                    System.out.println("[out] " + line);
                    LineConsumerResult lResult = lineProcessor.apply(line);
                    switch (lResult) {
                        case STOP: {
                            try {
                                p.getOutputStream().write(1);
                                p.getOutputStream().flush();
                            } catch (IOException ignored) {
                            }
                            break;
                        }
                        case CONTINUE: {
                            if (line.contains("[ready]")) {
                                p.getOutputStream().write(1);
                                p.getOutputStream().flush();
                            }
                            break;
                        }
                        case IGNORE: {
                            // ignore
                            break;
                        }
                    }
                }
            } catch (IOException ignored) {
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }, "stdout-reader");
        Thread stderrReader = new Thread(() -> {
            Function<String, LineConsumerResult> lineProcessor = onStderrLine != null ? onStderrLine : l -> LineConsumerResult.CONTINUE;
            try (BufferedReader br = new BufferedReader(new InputStreamReader(p.getErrorStream()))) {
                String line;
                while ((line = br.readLine()) != null) {
                    System.out.println("[err] " + line);
                    LineConsumerResult lResult = lineProcessor.apply(line);
                    switch (lResult) {
                        case STOP: {
                            try {
                                p.getOutputStream().write(1);
                                p.getOutputStream().flush();
                            } catch (IOException ignored) {
                            }
                            break;
                        }
                        case CONTINUE: {
                            break;
                        }
                        case IGNORE: {
                            // ignore
                            break;
                        }
                    }
                }
            } catch (IOException ignored) {
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }, "stderr-reader");

        stdoutReader.setDaemon(true);
        stderrReader.setDaemon(true);

        stdoutReader.start();
        stderrReader.start();

        boolean val = p.waitFor(timeoutSeconds, TimeUnit.SECONDS);
        if (!val) {
            p.destroyForcibly();
            p.waitFor(5, TimeUnit.SECONDS);
        }
        // Process.waitFor() only orders the child's exit, not the readers' last callbacks. Child modes
        // that call System.exit(0) skip the [ready] handshake, so nothing else guarantees the final
        // marker lines have been handed to the callbacks before the caller asserts on the state they
        // set. Thread.join() makes every callback write visible to the caller; the join is bounded
        // and a reader still alive after the bound is left behind.
        stdoutReader.join(READER_JOIN_TIMEOUT_MS);
        stderrReader.join(READER_JOIN_TIMEOUT_MS);
        // exitValue() throws while the child is still alive (it survived destroyForcibly()); report
        // -1 instead so the caller still sees inTime=false rather than an IllegalThreadStateException.
        return new LaunchResult(val, p.isAlive() ? -1 : p.exitValue());
    }
}
