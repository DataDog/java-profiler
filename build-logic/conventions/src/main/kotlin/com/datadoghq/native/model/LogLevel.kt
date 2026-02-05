// Copyright 2026, Datadog, Inc

package com.datadoghq.native.model

/**
 * Logging verbosity level for native build tasks.
 */
enum class LogLevel {
    /** Only errors */
    QUIET,

    /** Standard lifecycle messages (default) */
    NORMAL,

    /** Detailed progress information */
    VERBOSE,

    /** Full command lines and output */
    DEBUG
}
