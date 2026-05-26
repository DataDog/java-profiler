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

/**
 * A long-running workload that deliberately exercises a profiler failure surface
 * (thread teardown vs. signal, classloader unloading mid-walk, dlclose during
 * symbol resolution, calltrace storage contention, ...).
 *
 * <p>Implementations must be safe to start, run for an arbitrary duration, and
 * shut down on demand. They are NOT measured — the only failure signal is a JVM
 * crash (the harness exits non-zero via SIGSEGV/SIGABRT propagation).
 */
public interface Antagonist {

    String name();

    /** Spawn driver threads. Must return promptly. */
    void start();

    /** Signal driver threads to stop and wait up to {@code timeout}. */
    void stopGracefully(Duration timeout);
}
