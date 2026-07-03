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

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Unit tests for {@link OtelContextStorage} mode selection and the {@code thread} kill-switch.
 *
 * <p>{@link OtelContextStorage#create()} reads {@link OtelContextStorage#MODE_PROPERTY} on each
 * call and returns an instance whose concrete type determines its {@link ContextStorageMode}
 * — there is no shared mutable state — so these tests can drive it directly via the system
 * property without disturbing the profiler's already-constructed storage.
 */
public class OtelContextStorageTest {

    private String saved;

    @AfterEach
    public void restore() {
        if (saved == null) {
            System.clearProperty(OtelContextStorage.MODE_PROPERTY);
        } else {
            System.setProperty(OtelContextStorage.MODE_PROPERTY, saved);
        }
    }

    private void setMode(String mode) {
        saved = System.getProperty(OtelContextStorage.MODE_PROPERTY);
        System.setProperty(OtelContextStorage.MODE_PROPERTY, mode);
    }

    /** The kill-switch: {@code mode=thread} always yields plain thread-scoped storage. */
    @Test
    public void threadModeForcesPlainThreadLocal() {
        setMode("thread");
        ThreadLocal<ThreadContext> storage = OtelContextStorage.create();
        assertNotNull(storage);
        assertEquals(ContextStorageMode.THREAD, OtelContextStorage.modeOf(storage));
        // A forced-thread instance must be a plain ThreadLocal, never CarrierThreadLocal.
        assertEquals(ThreadLocal.class, storage.getClass(),
                "thread mode must not use jdk.internal.misc.CarrierThreadLocal");
    }

    /**
     * On JDK 21+ with {@code jdk.internal.misc} exported (the build adds the flag), {@code auto}
     * resolves to carrier scoping. Skipped otherwise, since the fallback is environment-driven.
     */
    @Test
    public void autoModeUsesCarrierWhenAvailable() {
        assumeTrue(Platform.isJavaVersionAtLeast(21), "carrier scoping needs JDK 21+");
        // Confirm CarrierThreadLocal is actually reachable in this run; if not (export not
        // granted), auto legitimately falls back to THREAD and there is nothing to assert.
        assumeTrue(carrierThreadLocalAccessible(),
                "jdk.internal.misc.CarrierThreadLocal not accessible; needs --add-exports");

        setMode("auto");
        ThreadLocal<ThreadContext> storage = OtelContextStorage.create();
        assertEquals(ContextStorageMode.CARRIER, OtelContextStorage.modeOf(storage),
                "auto must select carrier scoping when CarrierThreadLocal is accessible");
    }

    /** {@code carrier} succeeds and yields carrier-scoped storage when CarrierThreadLocal is accessible. */
    @Test
    public void carrierModeUsesCarrierWhenAvailable() {
        assumeTrue(carrierThreadLocalAccessible(),
                "CarrierThreadLocal not accessible; the fail-fast path is covered by the throw test");
        setMode("carrier");
        ThreadLocal<ThreadContext> storage = OtelContextStorage.create();
        assertEquals(ContextStorageMode.CARRIER, OtelContextStorage.modeOf(storage));
    }

    /**
     * {@code carrier} fails hard when CarrierThreadLocal is unavailable, rather than silently
     * falling back to the virtual-thread-pinned storage the fix removes.
     */
    @Test
    public void carrierModeThrowsWhenUnavailable() {
        assumeTrue(!carrierThreadLocalAccessible(),
                "CarrierThreadLocal IS accessible here; the fail-fast path only applies when it is not (older JDKs / no export)");
        setMode("carrier");
        assertThrows(IllegalStateException.class, OtelContextStorage::create);
    }

    private static boolean carrierThreadLocalAccessible() {
        try {
            Class<?> c = Class.forName("jdk.internal.misc.CarrierThreadLocal");
            c.getConstructor().newInstance();
            return true;
        } catch (Throwable t) {
            return false;
        }
    }
}
