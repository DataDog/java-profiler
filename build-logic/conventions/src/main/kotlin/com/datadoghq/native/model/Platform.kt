
package com.datadoghq.native.model

enum class Platform {
    LINUX,
    MACOS;

    override fun toString(): String = name.lowercase()

    companion object {
        fun current(): Platform {
            val osName = System.getProperty("os.name").lowercase()
            return when {
                osName.contains("mac") || osName.contains("darwin") -> MACOS
                osName.contains("linux") -> LINUX
                else -> throw IllegalStateException("Unsupported OS: $osName")
            }
        }
    }
}
