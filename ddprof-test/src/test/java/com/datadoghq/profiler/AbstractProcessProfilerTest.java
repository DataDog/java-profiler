package com.datadoghq.profiler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;
import java.util.function.Function;

import static org.junit.jupiter.api.Assertions.*;


public abstract class AbstractProcessProfilerTest {
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

    protected final LaunchResult launch(String target, List<String> jvmArgs, String commands, Function<String, LineConsumerResult> onStdoutLine, Function<String, LineConsumerResult> onStderrLine) throws Exception {
        return launch(target, jvmArgs, commands, Collections.emptyMap(), onStdoutLine, onStderrLine);
    }

    protected final LaunchResult launch(String target, List<String> jvmArgs, String commands, Map<String, String> env, Function<String, LineConsumerResult> onStdoutLine, Function<String, LineConsumerResult> onStderrLine) throws Exception {
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

        boolean val = p.waitFor(10, TimeUnit.SECONDS);
        if (!val) {
            p.destroyForcibly();
        }
        return new LaunchResult(val, p.exitValue());
    }
}