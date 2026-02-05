// Copyright 2026, Datadog, Inc

package com.datadoghq.native.model

/**
 * Error handling strategy for compilation.
 */
enum class ErrorHandlingMode {
    /** Stop on first error (default) */
    FAIL_FAST,

    /** Compile all files, collect all errors, report at end */
    COLLECT_ALL
}
