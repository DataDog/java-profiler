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

import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Guards against drift between the Java custom-attribute slot bound
 * ({@link JavaProfiler#MAX_CONTEXT_SLOTS}) and its native source of truth, {@code DD_TAGS_CAPACITY}
 * in {@code context.h}. The Java bound is a literal (it cannot be derived via JNI at class-init
 * time, before the library is loaded), so nothing but this test catches the two falling out of sync.
 */
public class MaxContextSlotsTest {

    @Test
    public void javaBoundMatchesNativeCapacity() throws IOException {
        JavaProfiler.getInstance(); // ensure the native library is loaded
        assertEquals(JavaProfiler.maxContextSlots0(), JavaProfiler.MAX_CONTEXT_SLOTS,
                "JavaProfiler.MAX_CONTEXT_SLOTS drifted from native DD_TAGS_CAPACITY");
        // ThreadContext mirrors the same native bound on the deprecated path; keep them aligned too.
        assertEquals(JavaProfiler.MAX_CONTEXT_SLOTS, ThreadContext.MAX_CUSTOM_SLOTS,
                "MAX_CONTEXT_SLOTS drifted from ThreadContext.MAX_CUSTOM_SLOTS");
    }
}
