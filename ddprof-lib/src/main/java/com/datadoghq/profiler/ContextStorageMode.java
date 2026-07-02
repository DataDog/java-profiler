/*
 * Copyright 2026, Datadog, Inc
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
package com.datadoghq.profiler;

/**
 * Scope of the OTEL context {@link ThreadContext} storage actually in effect, as reported by
 * {@link JavaProfiler#contextStorageMode()}. See {@link OtelContextStorage} for how it is
 * selected.
 */
public enum ContextStorageMode {
  /** Carrier-scoped via {@code jdk.internal.misc.CarrierThreadLocal} (JDK 21+). */
  CARRIER,
  /** Legacy virtual-thread-scoped plain {@link ThreadLocal}. */
  THREAD
}
