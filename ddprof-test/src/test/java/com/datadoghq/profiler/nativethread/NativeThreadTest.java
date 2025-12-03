/*
 * Copyright 2025, Datadog, Inc
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
package com.datadoghq.profiler.nativethread;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;


public class NativeThreadTest extends AbstractProfilerTest {

  static {
      System.loadLibrary("ddproftest");
  }

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms,wall=1ms";
  }

  @RetryingTest(3)
  public void test() {
      long[] threads = new long[128];
      for (int index = 0; index < threads.length; index++) {
          threads[index] = createNativeThread();
      }

      for (int index = 0; index < threads.length; index++) {
          waitNativeThread(threads[index]);
      }

      Map<String, AtomicInteger> modeCounters = new HashMap<>();
      Map<String, AtomicInteger> libraryCounters = new HashMap<>();
      for (IItemIterable cpuSamples : verifyEvents("datadog.ExecutionSample")) {
          IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
          IMemberAccessor<String, IItem> modeAccessor = THREAD_EXECUTION_MODE.getAccessor(cpuSamples.getType());
          for (IItem item : cpuSamples) {
              String stacktrace = stacktraceAccessor.getMember(item);
              String mode = modeAccessor.getMember(item);
              modeCounters.computeIfAbsent(mode, x -> new AtomicInteger()).incrementAndGet();
              System.out.println(stacktrace);
          }
      }

  }

  private static native long createNativeThread();
  private static native void waitNativeThread(long threadId);
}
