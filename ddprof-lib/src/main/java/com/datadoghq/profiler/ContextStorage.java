/*
 * Copyright 2026 Datadog, Inc
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

import java.nio.ByteBuffer;

/**
 * Support-only access to the native OTEP thread-local context storage.
 * <p>
 * Backed by {@code libJavaSupport}, so it is loadable independently of the
 * full profiler library.
 */
final class ContextStorage {
    private ContextStorage() {}

    static {
        LibraryLoader.builder().library(LibraryLoader.Library.SUPPORT).load();
    }

    /**
     * Initializes context TLS for the current thread and returns a single DirectByteBuffer
     * spanning the OTEP record + tag-encoding sidecar + LRS (688 bytes, contiguous in
     * ProfiledThread). Sets otel_thread_ctx_v1 permanently to the thread's
     * OtelThreadContextRecord.
     *
     * @param metadata output array filled with absolute offsets into the returned buffer:
     *   [0] VALID_OFFSET — offset of 'valid' field
     *   [1] TRACE_ID_OFFSET — offset of 'trace_id' field
     *   [2] SPAN_ID_OFFSET — offset of 'span_id' field
     *   [3] ATTRS_DATA_SIZE_OFFSET — offset of 'attrs_data_size' field
     *   [4] ATTRS_DATA_OFFSET — offset of 'attrs_data' field
     *   [5] LRS_OFFSET — offset of local_root_span_id
     * @return a direct {@link ByteBuffer} view over the current thread's OTEP
     *         context record, or {@literal null} if initialization failed
     */
    static native ByteBuffer initializeContextTLS0(long[] metadata);
}
