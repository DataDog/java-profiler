package com.datadoghq.profiler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.function.Function;

import static org.junit.jupiter.api.Assertions.*;


public abstract class AbstractProcessProfilerTest {
    protected final boolean launch(String target, List<String> jvmArgs, String commands, Function<String, Boolean> onStdoutLine, Function<String, Boolean> onStderrLine) throws Exception {
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
        Process p = pb.start();
        Thread stdoutReader = new Thread(() -> {
            Function<String, Boolean> lineProcessor = onStdoutLine != null ? onStdoutLine : l -> true;
            try (BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()))) {
                String line;
                while ((line = br.readLine()) != null) {
                    System.out.println("[out] " + line);
                    if (!lineProcessor.apply(line)) {
                        try {
                            p.getOutputStream().write(1);
                            p.getOutputStream().flush();
                        } catch (IOException ignored) {
                        }
                    } else {
                        if (line.contains("[ready]")) {
                            p.getOutputStream().write(1);
                            p.getOutputStream().flush();
                        }
                    }
                }
            } catch (IOException ignored) {
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }, "stdout-reader");
        Thread stderrReader = new Thread(() -> {
            Function<String, Boolean> lineProcessor = onStderrLine != null ? onStderrLine : l -> true;
            try (BufferedReader br = new BufferedReader(new InputStreamReader(p.getErrorStream()))) {
                String line;
                while ((line = br.readLine()) != null) {
                    System.out.println("[err] " + line);
                    if (!lineProcessor.apply(line)) {
                        try {
                            p.getOutputStream().write(1);
                            p.getOutputStream().flush();
                        } catch (IOException ignored) {
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
        return val;
    }
}