package jfr;

import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.flightrecorder.CouldNotLoadRecordingException;
import org.openjdk.jmc.flightrecorder.JfrAttributes;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.FileVisitResult;
import java.nio.file.FileVisitor;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.PosixFilePermissions;
import java.time.Duration;
import java.time.Instant;
import java.util.Arrays;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

public class JfrSmokeTest {
    private static final Logger LOGGER = LoggerFactory.getLogger(JfrSmokeTest.class);

    @Test
    public void test() throws Exception {
        Path tempDir = Files.createTempDirectory("jfr_test-");
        try {
            File whereami = new File(JfrSmokeTest.class.getResource("JfrSmokeTest.class").toURI()).getParentFile();
            while (!whereami.getName().equals("java-profiler")) {
                whereami = whereami.getParentFile();
            }
            File launcher = Paths.get(whereami.toURI()).resolve("test/run_renaissance.sh").toFile();
            ProcessBuilder pb = new ProcessBuilder(
                    launcher.getAbsolutePath(),
                    "-pa", "cpu,wall,file=" + tempDir.toString() + "/profile.jfr",
                    "-r", "2", "akka-uct");
            pb = pb.redirectError(ProcessBuilder.Redirect.PIPE).redirectOutput(ProcessBuilder.Redirect.PIPE);
            Instant startTs = Instant.now();
            Process process = pb.start();
            redirectToLog(process, "akka-uct");
            int rslt = process.waitFor();
            Instant endTs = Instant.now();
            assertEquals(0, rslt);
            assertJfrs(tempDir, startTs, endTs);
        } finally {
            Files.walkFileTree(tempDir, new FileVisitor<Path>() {
                @Override
                public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
                    return FileVisitResult.CONTINUE;
                }

                @Override
                public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                    Files.deleteIfExists(file);
                    return FileVisitResult.CONTINUE;
                }

                @Override
                public FileVisitResult visitFileFailed(Path file, IOException exc) throws IOException {
                    return FileVisitResult.TERMINATE;
                }

                @Override
                public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                    Files.deleteIfExists(dir);
                    return FileVisitResult.CONTINUE;
                }
            });
        }
    }

    private static void assertJfrs(Path location, Instant start, Instant end) throws IOException {
        Files.walk(location, 1).filter(Files::isRegularFile).forEach(file -> assertJfr(file, start, end));
    }

    private static void assertJfr(Path jfr, Instant start, Instant end) {
        try {
            IItemCollection events = JfrLoaderToolkit.loadEvents(jfr.toFile());
            assertCpuSamples(events, start, end);
            assertWallSamples(events, start, end);
        } catch (IOException | CouldNotLoadRecordingException e) {
            fail(e);
        }
    }

    private static void assertCpuSamples(IItemCollection events, Instant start, Instant end) {
        IItemCollection cpuSamples = events.apply(ItemFilters.type("datadog.ExecutionSample"));

        assertCpuSampleCounts(cpuSamples, start, end);
        assertHiddenLambdaFrames(cpuSamples);
    }

    private static void assertCpuSampleCounts(IItemCollection cpuSamples, Instant start, Instant end) {
        assertTrue(cpuSamples.hasItems());
        long collectedSamples = cpuSamples.stream().flatMap(iterable -> iterable.stream()).count();
        long estimatedCpuTimeRateMs =
            Duration.between(start, end)
                .multipliedBy(Runtime.getRuntime().availableProcessors())
                .toMillis()
                    / collectedSamples;
        // make sure that the sampling interval is not shorter than requested
        // the reported cores may include HT cores - they don't contribute to available CPU time linearly so we also try to normalize to HW cores
        assertTrue(estimatedCpuTimeRateMs - 10 >= 0 || (estimatedCpuTimeRateMs / 2) - 10 >= 0, "Expected: >10ms, observed: " + estimatedCpuTimeRateMs + "ms");
    }

    private static void assertWallSamples(IItemCollection events, Instant start, Instant end) {
        IItemCollection wallSamples = events.apply(ItemFilters.type("datadog.MethodSample"));

        assertWallSampleCounts(wallSamples, start, end);
        assertHiddenLambdaFrames(wallSamples);
    }

    private static void assertWallSampleCounts(IItemCollection wallSamples, Instant start, Instant end) {
        long nthreads =
            wallSamples
                .stream()
                .flatMap(iterable -> {
                    IMemberAccessor<IMCThread, IItem> threadAccessor =
                        JfrAttributes.EVENT_THREAD.getAccessor(iterable.getType());
                    if (threadAccessor == null) {
                        return Stream.empty();
                    }
                    return iterable.stream().map(threadAccessor::getMember);
                })
                .filter(t -> t != null)
                .distinct()
                .count();
        assertTrue(wallSamples.hasItems());
        long collectedSamples = wallSamples.stream().flatMap(iterable -> iterable.stream()).count();
        long estimatedWallTimeRateMs =
            Duration.between(start, end)
                .multipliedBy(nthreads)
                .toMillis()
                    / collectedSamples;
        // make sure that the sampling interval is not shorter than requested
        // the reported cores may include HT cores - they don't contribute to available WALL time linearly so we also try to normalize to HW cores
        assertTrue(estimatedWallTimeRateMs - 50 >= 0 || (estimatedWallTimeRateMs / 2) - 50 >= 0, "Expected: >50ms, observed: " + estimatedWallTimeRateMs + "ms");
    }

    private static void assertHiddenLambdaFrames(IItemCollection samples) {
        samples.stream().forEach(iterable -> {
            IMemberAccessor<IMCStackTrace, IItem> stacktraceAccessor = JfrAttributes.EVENT_STACKTRACE.getAccessor(iterable.getType());
            assertTrue(iterable.stream().flatMap(event -> stacktraceAccessor.getMember(event).getFrames().stream()).allMatch(frame -> {
                    boolean rslt = !frame.getMethod().getType().getFullName().contains("$Lambda$") || frame.getMethod().isHidden();
                    if (!rslt) {
                        System.err.println(frame.getMethod().getType().getFullName() + "." + frame.getMethod().getMethodName());
                    }
                    return rslt;
                }), "Lambda frames are supposed to be hidden");
        });
    }

    private static void redirectToLog(Process process, String processName) {
        Thread stdout = new Thread(() -> {
            try (BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line = null;
                while ((line = bufferedReader.readLine()) != null) {
                    LOGGER.debug(line);
                }
            } catch (IOException e) {
                if (!e.getMessage().contains("Stream closed")) {
                    LOGGER.error("", e);
                }
            }
        }, processName + " stdout");

        Thread stderr = new Thread(() -> {
            try (BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line = null;
                while ((line = bufferedReader.readLine()) != null) {
                    LOGGER.info(line);
                }
            } catch (IOException e) {
                if (!e.getMessage().contains("Stream closed")) {
                    LOGGER.error("", e);
                }
            }
        }, processName + " stderr");
        stdout.setDaemon(true);
        stderr.setDaemon(true);
        stdout.start();
        stderr.start();
    }
}
