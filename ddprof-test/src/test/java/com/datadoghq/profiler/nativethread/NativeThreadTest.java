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
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.nativethread.NativeThreadCreator;

import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.HashMap;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class NativeThreadTest extends AbstractProfilerTest {


  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms";
  }

  @RetryingTest(3)
  public void test() {
      long[] threads = new long[8];
      for (int index = 0; index < threads.length; index++) {
          threads[index] = NativeThreadCreator.createNativeThread();
      }

      for (int index = 0; index < threads.length; index++) {
          NativeThreadCreator.waitNativeThread(threads[index]);
      }
      stopProfiler();
      int count = 0;
      boolean stacktrace_printed = false;
      for (IItemIterable cpuSamples : verifyEvents("datadog.ExecutionSample")) {
          IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
          IMemberAccessor<String, IItem> modeAccessor = THREAD_EXECUTION_MODE.getAccessor(cpuSamples.getType());
          for (IItem item : cpuSamples) {
              String stacktrace = stacktraceAccessor.getMember(item);
              if (stacktrace.indexOf("do_primes()") != -1) {
                if (!stacktrace_printed) {
                    stacktrace_printed = true;
                    System.out.println("Native thread stack:");
                    System.out.println(stacktrace);
                }
                count++;
              }
          }
      }
      assertTrue(count > 0, "no native thread sample");
  }

}
