package com.datadoghq.profiler;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;

/**
 * Encapsulates dynamic library loading logic.
 * It is used to load the native library from the classpath or from a custom location.
 * When loading from the classpath, the library is extracted to a temporary file and loaded from there.
 *
 */
public final class LibraryLoader {
    enum LoadingState {
        NOT_LOADED,
        LOADING,
        LOADED,
        UNAVAILABLE
    }

    /**
     * Represents the result of a library loading operation.
     */
    public static final class Result {
        public static final Result SUCCESS = new Result(true, null);
        public static final Result UNAVAILABLE = new Result(false, null);

        public final boolean success;
        public final Throwable error;

        public Result(boolean success, Throwable error) {
            this.success = success;
            this.error = error;
        }
    }

    /**
     * Builder for {@link LibraryLoader}. It allows to specify the library location and the scratch directory.
     */
    public static final class Builder {
        private String libraryLocation;
        private String scratchDir;

        private Builder() {}

        /**
         * Sets the library location.
         * @param libraryLocation the library location
         * @return this builder
         */
        public Builder withLibraryLocation(String libraryLocation) {
            this.libraryLocation = libraryLocation;
            return this;
        }

        /**
         * Sets the scratch directory where the temp library file can be created.
         * @param scratchDir the scratch directory
         * @return this builder
         */
        public Builder withScratchDir(String scratchDir) {
            this.scratchDir = scratchDir;
            return this;
        }

        /**
         * Loads the library.
         * @return the result of the library loading operation
         */
        public Result load() {
            return loadLibrary(libraryLocation, scratchDir);
        }
    }

    private static final String NATIVE_LIBS = "/META-INF/native-libs";
    private static final String JAVA_PROFILER_LIBRARY_NAME_BASE = "libjavaProfiler";
    private static final String JAVA_PROFILER_LIBRARY_NAME = JAVA_PROFILER_LIBRARY_NAME_BASE + "." + (OperatingSystem.current() == OperatingSystem.macos ? "dylib" : "so");

    private static final Map<String, AtomicReference<LoadingState>> loadingStateMap = new ConcurrentHashMap<>();

    public static Builder builder() {
        return new Builder();
    }

    private static Result loadLibrary(final String libraryLocation, String scratchDir) {
        String key = libraryLocation == null ? JAVA_PROFILER_LIBRARY_NAME : libraryLocation;
        AtomicReference<LoadingState> state = loadingStateMap.computeIfAbsent(key, (k) -> new AtomicReference<>(LoadingState.NOT_LOADED));

        try {
            // first thread to arrive will set the flag to 'loading' and will load the library
            if (!state.compareAndSet(LoadingState.NOT_LOADED, LoadingState.LOADING)) {
                // if there is already a different thread loading the library we will wait for it to finish
                while (state.get() == LoadingState.LOADING) {
                    LockSupport.parkNanos(5_000_000L); // 5ms
                }
                // the library has been loaded by another thread, we can return
                return state.get() == LoadingState.LOADED ? Result.SUCCESS : Result.UNAVAILABLE;
            }
            // if the attempt to load the library failed do not try again
            if (state.get() == LoadingState.UNAVAILABLE) {
                return Result.UNAVAILABLE;
            }
            Path libraryPath = libraryLocation != null ? Paths.get(libraryLocation) : null;
            if (libraryPath == null) {
                OperatingSystem os = OperatingSystem.current();
                String qualifier = (os == OperatingSystem.linux && os.isMusl()) ? "musl" : null;

                libraryPath = libraryFromClasspath(os, Arch.current(), qualifier, Paths.get(scratchDir != null ? scratchDir : System.getProperty("java.io.tmpdir")));
            }
            System.load(libraryPath.toAbsolutePath().toString());
            return Result.SUCCESS;
        } catch (Throwable t) {
            state.set(LoadingState.UNAVAILABLE);
            return new Result(false, t);
        } finally {
            state.compareAndSet(LoadingState.LOADED, LoadingState.LOADED);
        }
    }

    /**
     * Locates a library on class-path (eg. in a JAR) and creates a publicly accessible temporary copy
     * of the library which can then be used by the application by its absolute path.
     *
     * @param os The operating system
     * @param arch The architecture
     * @param qualifier An optional qualifier (eg. musl)
     * @param tempDir The working scratch dir where to store the temp library file
     * @return The library absolute path. The caller should properly dispose of the file once it is
     *     not needed. The file is marked for 'delete-on-exit' so it won't survive a JVM restart.
     * @throws IOException, IllegalStateException if the resource is not found on the classpath
     */
    private static Path libraryFromClasspath(OperatingSystem os, Arch arch, String qualifier, Path tempDir) throws IOException {
        String resourcePath = NATIVE_LIBS + "/" + os.name().toLowerCase() + "-" + arch.name().toLowerCase() + ((qualifier != null && !qualifier.isEmpty()) ? "-" + qualifier : "") + "/" + JAVA_PROFILER_LIBRARY_NAME;

        InputStream libraryData =  JavaProfiler.class.getResourceAsStream(resourcePath);

        if (libraryData != null) {
            Path libFile = Files.createTempFile(tempDir, JAVA_PROFILER_LIBRARY_NAME_BASE + "-dd-tmp", ".so");
            Files.copy(libraryData, libFile, StandardCopyOption.REPLACE_EXISTING);
            libFile.toFile().deleteOnExit();
            return libFile;
        }
        throw new IllegalStateException(resourcePath + " not found on classpath");
    }
}
