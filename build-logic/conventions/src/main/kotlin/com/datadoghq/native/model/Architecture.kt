
package com.datadoghq.native.model

enum class Architecture {
    X64,
    ARM64;

    override fun toString(): String = when (this) {
        X64 -> "x64"
        ARM64 -> "arm64"
    }

    companion object {
        fun current(): Architecture {
            val osArch = System.getProperty("os.arch").lowercase()
            return when {
                osArch.contains("amd64") || osArch.contains("x86_64") -> X64
                osArch.contains("aarch64") || osArch.contains("arm64") -> ARM64
                else -> throw IllegalStateException("Unsupported architecture: $osArch")
            }
        }
    }
}
