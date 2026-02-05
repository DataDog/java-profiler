/*
 * Copyright 2026, Datadog, Inc.
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

/**
 * Utility class for compiler detection and configuration.
 * Provides simple, reliable methods to find compilers without parsing version strings.
 */
class CompilerUtils {

    /**
     * Find an available C++ compiler on the system PATH.
     * Tries clang++ first (generally better error messages), then g++.
     *
     * @return The compiler executable name or full path
     */
    static String findCxxCompiler() {
        // Preference order: clang++ (better errors), then g++
        def candidates = ['clang++', 'g++', 'c++']

        for (compiler in candidates) {
            if (isCompilerAvailable(compiler)) {
                return compiler
            }
        }

        // Default fallback - let it fail with a clear error if not found
        return 'g++'
    }

    /**
     * Find an available C compiler on the system PATH.
     *
     * @return The compiler executable name or full path
     */
    static String findCCompiler() {
        def candidates = ['clang', 'gcc', 'cc']

        for (compiler in candidates) {
            if (isCompilerAvailable(compiler)) {
                return compiler
            }
        }

        return 'gcc'
    }

    /**
     * Check if a compiler is available and executable.
     *
     * @param compiler The compiler name or path
     * @return true if the compiler can be executed
     */
    static boolean isCompilerAvailable(String compiler) {
        try {
            def proc = [compiler, '--version'].execute()
            proc.waitForOrKill(5000)
            return proc.exitValue() == 0
        } catch (Exception e) {
            return false
        }
    }

    /**
     * Get the system include directories for a compiler.
     * Parses the output of `compiler -E -Wp,-v -xc++ /dev/null`.
     *
     * @param compiler The compiler to query
     * @return List of system include directory paths
     */
    static List<String> getSystemIncludes(String compiler) {
        try {
            def nullDevice = System.getProperty('os.name').toLowerCase().contains('win')
                ? 'NUL'
                : '/dev/null'

            def proc = [compiler, '-E', '-Wp,-v', '-xc++', nullDevice].execute()
            def stderr = new StringBuilder()
            proc.consumeProcessErrorStream(stderr)
            proc.waitForOrKill(10000)

            def includes = []
            def inIncludeSection = false

            stderr.toString().eachLine { line ->
                if (line.contains('#include <...>')) {
                    inIncludeSection = true
                } else if (line.contains('End of search list')) {
                    inIncludeSection = false
                } else if (inIncludeSection && line.trim()) {
                    def path = line.trim()
                    // Remove framework suffix if present (macOS)
                    if (path.endsWith(' (framework directory)')) {
                        path = path.replace(' (framework directory)', '')
                    }
                    if (new File(path).isDirectory()) {
                        includes.add(path)
                    }
                }
            }

            return includes
        } catch (Exception e) {
            return []
        }
    }

    /**
     * Check if the current system is macOS.
     *
     * @return true if running on macOS
     */
    static boolean isMacOS() {
        return System.getProperty('os.name').toLowerCase().contains('mac')
    }

    /**
     * Check if the current system is Linux.
     *
     * @return true if running on Linux
     */
    static boolean isLinux() {
        return System.getProperty('os.name').toLowerCase().contains('linux')
    }

    /**
     * Get the shared library extension for the current platform.
     *
     * @return '.dylib' on macOS, '.so' on Linux
     */
    static String getSharedLibExtension() {
        return isMacOS() ? 'dylib' : 'so'
    }

    /**
     * Get the JNI include directories for the current JAVA_HOME.
     *
     * @param javaHome The JAVA_HOME directory (or null to use environment)
     * @return List of JNI include directories
     */
    static List<String> getJniIncludes(String javaHome = null) {
        def home = javaHome ?: System.getenv('JAVA_HOME') ?: System.getProperty('java.home')

        if (!home) {
            return []
        }

        def includes = []
        def baseInclude = new File(home, 'include')

        if (baseInclude.isDirectory()) {
            includes.add(baseInclude.absolutePath)

            // Platform-specific subdirectory
            def platformDir = isMacOS() ? 'darwin' : 'linux'
            def platformInclude = new File(baseInclude, platformDir)
            if (platformInclude.isDirectory()) {
                includes.add(platformInclude.absolutePath)
            }
        }

        return includes
    }

    /**
     * Locate a library file using the compiler's library search path.
     * Uses `gcc -print-file-name=<lib>` to find library locations.
     *
     * @param compiler The compiler to use for lookup
     * @param libName The library name (e.g., 'libasan.so')
     * @return The full path to the library, or null if not found
     */
    static String locateLibrary(String compiler, String libName) {
        try {
            def proc = [compiler, "-print-file-name=${libName}"].execute()
            def result = proc.text.trim()
            proc.waitForOrKill(5000)

            // If the compiler just returns the library name, it wasn't found
            if (result && result != libName && new File(result).exists()) {
                return result
            }
        } catch (Exception e) {
            // Ignore - library not found
        }
        return null
    }

    /**
     * Locate the AddressSanitizer library.
     *
     * @param compiler The compiler to use for lookup
     * @return The full path to libasan, or null if not found
     */
    static String locateLibasan(String compiler = 'gcc') {
        return locateLibrary(compiler, 'libasan.so')
    }

    /**
     * Locate the ThreadSanitizer library.
     *
     * @param compiler The compiler to use for lookup
     * @return The full path to libtsan, or null if not found
     */
    static String locateLibtsan(String compiler = 'gcc') {
        return locateLibrary(compiler, 'libtsan.so')
    }
}
