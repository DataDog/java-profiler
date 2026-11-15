/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package io.netty.channel.epoll;

import io.netty.channel.unix.FileDescriptor;
import io.netty.util.Version;
import java.lang.reflect.Method;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.Callable;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

/** Uses the real transport's default select strategy, including its timed native wait. */
public final class ProfilerEpollFixture implements AutoCloseable {
  private final EpollEventLoopGroup group;
  private final String threadName;

  /** Fails on unavailable Linux epoll rather than silently substituting a NIO transport. */
  public ProfilerEpollFixture(String threadName) {
    Epoll.ensureAvailability();
    this.threadName = threadName;
    group =
        new EpollEventLoopGroup(1, (ThreadFactory) runnable -> new Thread(runnable, threadName));
  }

  /** Returns the resolved transport version, not the fixture's requested dependency version. */
  public String version() {
    return Version.identify(getClass().getClassLoader())
        .get("netty-transport-classes-epoll")
        .artifactVersion();
  }

  /** Leaves the default event loop idle until a genuine scheduled task becomes runnable. */
  public void timedWait() throws Exception {
    AtomicReference<Thread> worker = new AtomicReference<>();
    EpollEventLoop loop = (EpollEventLoop) group.next();
    loop.submit(() -> worker.set(Thread.currentThread())).get(5, TimeUnit.SECONDS);
    loop.schedule(
            () -> {
              if (!loop.inEventLoop() || !threadName.equals(Thread.currentThread().getName())) {
                throw new AssertionError("scheduled task did not run on the epoll thread");
              }
            },
            300,
            TimeUnit.MILLISECONDS)
        .get(5, TimeUnit.SECONDS);
    if (worker.get() == null || !worker.get().isAlive()) {
      throw new AssertionError("epoll event loop terminated");
    }
  }

  /** Runs every positive-timeout JNI wait on this fixture's actual Netty event-loop worker. */
  public void timedNativeWaits(int iterations) throws Exception {
    if (iterations <= 0) {
      throw new IllegalArgumentException("iterations must be positive");
    }
    EpollEventLoop worker = (EpollEventLoop) group.next();
    worker
        .submit(
            (Callable<Void>)
                () -> {
                  for (int i = 0; i < iterations; i++) timedNativeWait(worker);
                  return null;
                })
        .get(5, TimeUnit.SECONDS);
  }

  /** Enters JNI only after validating Netty executor membership, independently of thread naming. */
  private void timedNativeWait(EpollEventLoop worker) throws Exception {
    if (!worker.inEventLoop() || worker.parent() != group) {
      throw new AssertionError("timed JNI wait is not on this fixture's epoll event-loop worker");
    }
    String stat =
        new String(Files.readAllBytes(Paths.get("/proc/thread-self/stat")), StandardCharsets.UTF_8);
    System.out.println(
        "NETTY_TIMED_WORKER tid="
            + stat.substring(0, stat.indexOf(' '))
            + " name="
            + Thread.currentThread().getName()
            + " inEventLoop="
            + worker.inEventLoop()
            + " executor="
            + worker.getClass().getName());
    EpollEventArray events = new EpollEventArray(1);
    try {
      FileDescriptor epoll = Native.newEpollCreate();
      // Netty's descriptors do not implement AutoCloseable; adapters preserve suppressed closes.
      try (AutoCloseable epollOwner = epoll::close) {
        FileDescriptor timer = Native.newTimerFd();
        try (AutoCloseable timerOwner = timer::close) {
          long result = Native.epollWait(epoll, events, timer, 0, 300_000_000, 10);
          if (Native.epollReady(result) != 0) {
            throw new AssertionError("empty epoll set unexpectedly became ready");
          }
        }
      }
    } finally {
      events.free();
    }
  }

  /** Starts an independently owned real JNI wait and observes its kernel entry before returning. */
  public ControlledWait controlledWait(String name) throws Exception {
    ControlledWait wait = new ControlledWait(name);
    try {
      wait.assertBlocked();
      return wait;
    } catch (Exception | Error error) {
      try {
        wait.close();
      } catch (Exception | Error cleanup) {
        error.addSuppressed(cleanup);
      }
      throw error;
    }
  }

  /** Eventfd release makes stop/restart ordering independent of a timeout or scheduler delay. */
  public static final class ControlledWait implements AutoCloseable {
    private final EpollEventArray events = new EpollEventArray(1);
    private final AtomicReference<Throwable> failure = new AtomicReference<>();
    private FileDescriptor epoll;
    private FileDescriptor wakeup;
    private Thread worker;
    private volatile String tid;
    private boolean closed;

    private ControlledWait(String name) throws Exception {
      try {
        epoll = Native.newEpollCreate();
        wakeup = Native.newEventFd();
        Native.epollCtlAdd(epoll.intValue(), wakeup.intValue(), Native.EPOLLIN);
        worker =
            new Thread(
                () -> {
                  try {
                    String stat =
                        new String(
                            Files.readAllBytes(Paths.get("/proc/thread-self/stat")),
                            StandardCharsets.UTF_8);
                    tid = stat.substring(0, stat.indexOf(' '));
                    if (Native.epollWait(epoll, events, -1) != 1) {
                      throw new AssertionError("controlled epoll wait did not observe its eventfd");
                    }
                  } catch (Throwable error) {
                    failure.set(error);
                  }
                },
                name);
        worker.setDaemon(false);
        worker.start();
      } catch (Exception | Error error) {
        try {
          close();
        } catch (Exception | Error cleanup) {
          error.addSuppressed(cleanup);
        }
        throw error;
      }
    }

    /**
     * Requires this exact descriptor to be blocked in the kernel, not merely a runnable Java frame.
     */
    public void assertBlocked() throws Exception {
      long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
      while (System.nanoTime() - deadline < 0) {
        if (failure.get() != null || !worker.isAlive()) {
          throw new AssertionError("controlled epoll worker exited before release", failure.get());
        }
        String id = tid;
        if (id != null) {
          String syscall =
              new String(
                      Files.readAllBytes(Paths.get("/proc/self/task", id, "syscall")),
                      StandardCharsets.UTF_8)
                  .trim();
          String[] fields = syscall.split("\\s+");
          boolean arm64 = "aarch64".equals(System.getProperty("os.arch"));
          boolean epollSyscall =
              arm64 ? fields[0].equals("22") : fields[0].equals("232") || fields[0].equals("281");
          if (fields.length > 1 && epollSyscall && Long.decode(fields[1]) == epoll.intValue()) {
            System.out.println(
                "NETTY_CONTROLLED_WAIT tid="
                    + id
                    + " name="
                    + worker.getName()
                    + " syscall="
                    + syscall);
            return;
          }
        }
        Thread.yield();
      }
      throw new AssertionError("controlled worker did not enter its epoll syscall");
    }

    /**
     * Releases before joining and preserves interruption while owning every descriptor until exit.
     */
    @Override
    public void close() throws Exception {
      if (closed) return;
      boolean interrupted = Thread.interrupted();
      try {
        if (worker != null && worker.isAlive()) {
          Native.eventFdWrite(wakeup.intValue(), 1);
          long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
          while (worker.isAlive() && System.nanoTime() - deadline < 0) {
            try {
              TimeUnit.NANOSECONDS.timedJoin(worker, Math.max(1, deadline - System.nanoTime()));
            } catch (InterruptedException error) {
              interrupted = true;
            }
          }
          if (worker.isAlive())
            throw new AssertionError("controlled epoll worker survived release");
        }
        closed = true;
        try (AutoCloseable epollOwner =
                () -> {
                  if (epoll != null) epoll.close();
                };
            AutoCloseable wakeupOwner =
                () -> {
                  if (wakeup != null) wakeup.close();
                }) {
          if (failure.get() != null)
            throw new AssertionError("controlled epoll wait failed", failure.get());
        } finally {
          events.free();
        }
      } finally {
        if (interrupted) Thread.currentThread().interrupt();
      }
    }
  }

  /** Reads real JNI -errno using -1, which cannot race descriptor reuse after close. */
  public int invalidDescriptorErrno() throws Exception {
    EpollEventArray events = new EpollEventArray(1);
    try {
      Method wait =
          Native.class.getDeclaredMethod("epollWait", int.class, long.class, int.class, int.class);
      wait.setAccessible(true);
      return (Integer) wait.invoke(null, -1, events.memoryAddress(), events.length(), 1);
    } finally {
      events.free();
    }
  }

  /** Reads -errno through the actual timed JNI branch, including pwait2 when Netty supports it. */
  public int invalidTimedDescriptorErrno() throws Exception {
    EpollEventArray events = new EpollEventArray(1);
    try {
      Method wait =
          Native.class.getDeclaredMethod(
              "epollWait0",
              int.class,
              long.class,
              int.class,
              int.class,
              int.class,
              int.class,
              long.class);
      wait.setAccessible(true);
      long result =
          (Long)
              wait.invoke(
                  null, -1, events.memoryAddress(), events.length(), -1, 0, 300_000_000, 10L);
      return Native.epollReady(result);
    } finally {
      events.free();
    }
  }

  /** Joins the event loop even when worker cleanup restored the owner's interrupt flag. */
  @Override
  public void close() throws Exception {
    boolean interrupted = Thread.interrupted();
    InterruptedException joinInterruption = null;
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
    try {
      group.shutdownGracefully(0, 2, TimeUnit.SECONDS);
      while (!group.isTerminated()) {
        long remaining = deadline - System.nanoTime();
        if (remaining <= 0) {
          AssertionError failure = new AssertionError("epoll event loop failed to terminate");
          if (joinInterruption != null) {
            failure.addSuppressed(joinInterruption);
          }
          throw failure;
        }
        try {
          group.terminationFuture().await(remaining, TimeUnit.NANOSECONDS);
        } catch (InterruptedException error) {
          if (joinInterruption == null) {
            joinInterruption = error;
          }
        }
      }
      if (joinInterruption != null) {
        throw joinInterruption;
      }
    } finally {
      if (interrupted || joinInterruption != null) {
        Thread.currentThread().interrupt();
      }
    }
  }
}
