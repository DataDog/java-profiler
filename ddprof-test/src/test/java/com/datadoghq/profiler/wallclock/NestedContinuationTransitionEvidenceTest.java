// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/** Exercises parent completion without loading a profiler or applying the continuation patch. */
class NestedContinuationTransitionEvidenceTest {
  private static final byte[] LOG = "existing child output\n".getBytes(StandardCharsets.UTF_8);
  // Opaque copying fixture, not a valid JFR recording.
  private static final byte[] RECORDING = {7, 3, 1, 9};

  @TempDir Path root;

  private Path child(boolean recording) throws IOException {
    Path directory = Files.createTempDirectory(root, "nested-continuation-transition-");
    Files.write(directory.resolve("child.log"), LOG);
    if (recording) Files.write(directory.resolve("transition.jfr"), RECORDING);
    return directory;
  }

  private Path collected() {
    return root.resolve("recordings");
  }

  private List<Path> copies(String name) throws IOException {
    if (!Files.exists(collected())) return java.util.Collections.emptyList();
    try (Stream<Path> files = Files.walk(collected())) {
      return files
          .filter(path -> path.getFileName().toString().equals(name))
          .collect(Collectors.toList());
    }
  }

  private void complete(
      FakeChild process,
      Path directory,
      String mode,
      boolean keep,
      NestedContinuationTransitionTest.RecordingCheck check)
      throws Exception {
    NestedContinuationTransitionTest.completeChild(
        process, directory, mode, collected(), keep, check);
  }

  @Test
  void nonzeroExitPreservesExistingFilesBeforeFailureEscapes() throws Exception {
    Path directory = child(true);
    AssertionError failure =
        assertThrows(
            AssertionError.class,
            () ->
                complete(
                    new FakeChild(1, false),
                    directory,
                    "vm",
                    false,
                    recording -> fail("A failed child must not be verified")));
    assertTrue(failure.getMessage().contains("Child failed"));
    assertEquals(0, failure.getSuppressed().length);
    assertEquals(1, copies("child.log").size());
    assertEquals(1, copies("transition.jfr").size());
    assertArrayEquals(LOG, Files.readAllBytes(copies("child.log").get(0)));
    assertArrayEquals(RECORDING, Files.readAllBytes(copies("transition.jfr").get(0)));
    assertArrayEquals(LOG, Files.readAllBytes(directory.resolve("child.log")));
    assertArrayEquals(RECORDING, Files.readAllBytes(directory.resolve("transition.jfr")));
  }

  @Test
  void missingRecordingDoesNotMaskNonzeroExit() throws Exception {
    Path directory = child(false);
    AssertionError failure =
        assertThrows(
            AssertionError.class,
            () -> complete(new FakeChild(1, false), directory, "vmx", true, recording -> fail()));
    assertTrue(failure.getMessage().contains("Child failed"));
    assertEquals(0, failure.getSuppressed().length);
    assertEquals(1, copies("child.log").size());
    assertArrayEquals(LOG, Files.readAllBytes(copies("child.log").get(0)));
    assertTrue(copies("transition.jfr").isEmpty());
  }

  @Test
  void missingLogStillPreservesExistingRecording() throws Exception {
    Path directory = child(true);
    Files.delete(directory.resolve("child.log"));
    AssertionError failure =
        assertThrows(
            AssertionError.class,
            () -> complete(new FakeChild(1, false), directory, "vm", false, recording -> fail()));
    assertTrue(failure.getMessage().contains("Child failed"));
    assertEquals(0, failure.getSuppressed().length);
    assertTrue(copies("child.log").isEmpty());
    assertEquals(1, copies("transition.jfr").size());
    assertArrayEquals(RECORDING, Files.readAllBytes(copies("transition.jfr").get(0)));
  }

  @Test
  void modesAndRepeatedAttemptsHaveDistinctDestinations() throws Exception {
    Path directory = child(true);
    for (String mode : new String[] {"vm", "vmx", "vm"}) {
      assertThrows(
          AssertionError.class,
          () -> complete(new FakeChild(1, false), directory, mode, false, recording -> fail()));
    }
    List<Path> logs = copies("child.log");
    assertEquals(3, logs.size());
    assertEquals(3, logs.stream().map(Path::getParent).distinct().count());
    assertEquals(2, logs.stream().filter(p -> p.getParent().getParent().endsWith("vm")).count());
    assertEquals(1, logs.stream().filter(p -> p.getParent().getParent().endsWith("vmx")).count());
    for (Path log : logs) {
      assertTrue(
          log.getParent().getFileName().toString().startsWith(directory.getFileName().toString()));
      assertArrayEquals(LOG, Files.readAllBytes(log));
    }
  }

  @Test
  void timeoutTerminatesAndWaitsBeforeCopyingFinalOutput() throws Exception {
    Path directory = child(false);
    FakeChild process = new FakeChild(1, true);
    process.onTermination =
        () -> {
          Files.write(directory.resolve("child.log"), new byte[] {4, 2});
          Files.write(directory.resolve("transition.jfr"), RECORDING);
        };
    AssertionError failure =
        assertThrows(
            AssertionError.class,
            () -> complete(process, directory, "vm", false, recording -> fail()));
    assertTrue(failure.getMessage().contains("Child timed out"));
    assertEquals(0, failure.getSuppressed().length);
    assertTrue(process.destroyed);
    assertTrue(process.waitedAfterDestroy);
    assertFalse(process.isAlive());
    assertArrayEquals(new byte[] {4, 2}, Files.readAllBytes(copies("child.log").get(0)));
    assertArrayEquals(RECORDING, Files.readAllBytes(copies("transition.jfr").get(0)));
  }

  @Test
  void waitExceptionIsPrimaryAndStillTerminatesAndPreserves() throws Exception {
    Path directory = child(true);
    FakeChild process = new FakeChild(1, true);
    InterruptedException original = new InterruptedException("fixture wait");
    process.waitFailure = original;
    assertSame(
        original,
        assertThrows(
            InterruptedException.class,
            () -> complete(process, directory, "vm", false, recording -> fail())));
    assertTrue(process.waitedAfterDestroy);
    assertArrayEquals(LOG, Files.readAllBytes(copies("child.log").get(0)));
  }

  @Test
  void verificationExceptionIsPrimaryAndCopiesAlreadyExistAtCatch() throws Exception {
    Path directory = child(true);
    IOException original = new IOException("fixture verification");
    assertSame(
        original,
        assertThrows(
            IOException.class,
            () ->
                complete(
                    new FakeChild(0, false),
                    directory,
                    "vm",
                    false,
                    recording -> {
                      throw original;
                    })));
    assertArrayEquals(RECORDING, Files.readAllBytes(copies("transition.jfr").get(0)));
    assertTrue(Files.exists(directory));
  }

  @Test
  void copyFailureIsSuppressedUnderOriginalAssertion() throws Exception {
    Path directory = child(true);
    Files.write(collected(), new byte[] {1});
    AssertionError failure =
        assertThrows(
            AssertionError.class,
            () -> complete(new FakeChild(1, false), directory, "vm", false, recording -> fail()));
    assertTrue(failure.getMessage().contains("Child failed"));
    assertEquals(1, failure.getSuppressed().length);
    assertInstanceOf(IOException.class, failure.getSuppressed()[0]);
    assertTrue(Files.exists(directory.resolve("child.log")));
  }

  @Test
  void terminationFailureIsSuppressedAndDoesNotCopyLiveOutput() throws Exception {
    Path directory = child(true);
    FakeChild process = new FakeChild(1, true);
    process.refuseTermination = true;
    AssertionError failure =
        assertThrows(
            AssertionError.class,
            () -> complete(process, directory, "vm", false, recording -> fail()));
    assertTrue(failure.getMessage().contains("Child timed out"));
    assertEquals(1, failure.getSuppressed().length);
    assertTrue(failure.getSuppressed()[0].getMessage().contains("Child did not terminate"));
    assertTrue(process.waitedAfterDestroy);
    assertTrue(copies("child.log").isEmpty());
  }

  @Test
  void successfulVerificationCleansUnlessKeepIsRequested() throws Exception {
    for (boolean keep : new boolean[] {false, true}) {
      Path directory = child(true);
      boolean[] checked = {false};
      FakeChild process = new FakeChild(0, false);
      complete(
          process,
          directory,
          "vm",
          keep,
          recording -> {
            assertArrayEquals(RECORDING, Files.readAllBytes(recording));
            checked[0] = true;
          });
      assertTrue(checked[0]);
      assertEquals(keep, Files.exists(directory));
      assertFalse(process.destroyed);
    }
    assertFalse(Files.exists(collected()));
  }

  private interface TerminationOutput {
    void write() throws IOException;
  }

  /** Termination output is written only when the parent waits after destroyForcibly. */
  private static class FakeChild extends Process {
    private final int exit;
    private boolean alive;
    boolean destroyed;
    boolean waitedAfterDestroy;
    boolean refuseTermination;
    InterruptedException waitFailure;
    TerminationOutput onTermination = () -> {};

    FakeChild(int exit, boolean alive) {
      this.exit = exit;
      this.alive = alive;
    }

    @Override
    public boolean waitFor(long timeout, TimeUnit unit) throws InterruptedException {
      if (waitFailure != null && !destroyed) throw waitFailure;
      if (destroyed) {
        waitedAfterDestroy = true;
        if (refuseTermination) return false;
        try {
          onTermination.write();
        } catch (IOException e) {
          throw new AssertionError(e);
        }
        alive = false;
      }
      return !alive;
    }

    @Override
    public int waitFor() {
      throw new UnsupportedOperationException();
    }

    @Override
    public int exitValue() {
      if (alive) throw new IllegalThreadStateException();
      return exit;
    }

    @Override
    public boolean isAlive() {
      return alive;
    }

    @Override
    public Process destroyForcibly() {
      destroyed = true;
      return this;
    }

    @Override
    public void destroy() {
      throw new UnsupportedOperationException();
    }

    @Override
    public OutputStream getOutputStream() {
      return new ByteArrayOutputStream();
    }

    @Override
    public InputStream getInputStream() {
      return new ByteArrayInputStream(new byte[0]);
    }

    @Override
    public InputStream getErrorStream() {
      return new ByteArrayInputStream(new byte[0]);
    }
  }
}
