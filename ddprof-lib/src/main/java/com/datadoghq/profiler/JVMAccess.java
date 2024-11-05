package com.datadoghq.profiler;

import java.util.function.Consumer;

/**
 * An internal JVM access support.
 * <p>
 * We are using vmstructs and dynamic symbol lookups to provide access to some JVM internals.
 * There will be dragons here. We are touching and possibly mutating JVM internals. Do not use
 * unless you know what you are doing.
 * </p>
 */
public final class JVMAccess {
    private static final class SingletonHolder {
        static final JVMAccess INSTANCE = new JVMAccess();
    }

    /**
     * Flags interface to access JVM flags.
     * In general, the flags are read-only. However, some flags can be modified at runtime.
     * Currently, only string and boolean flags can be modified. Allowing modification of numeric
     * flags would require exact specification of the flag type (int, long, float, double) such
     * that the correct number of bytes would be written to the flag and not overwrite the surrounding
     * memory.
     */
    public interface Flags {
        Flags NONE = new Flags() {
            @Override
            public String getStringFlag(String name) {
                return null;
            }

            @Override
            public void setStringFlag(String name, String value) {
            }

            @Override
            public boolean getBooleanFlag(String name) {
                return false;
            }

            @Override
            public void setBooleanFlag(String name, boolean value) {
            }

            @Override
            public long getIntFlag(String name) {
                return 0;
            }

            @Override
            public double getFloatFlag(String name) {
                return 0;
            }
        };

        String getStringFlag(String name);
        void setStringFlag(String name, String value);
        boolean getBooleanFlag(String name);
        void setBooleanFlag(String name, boolean value);
        long getIntFlag(String name);
        double getFloatFlag(String name);
    }

    private class FlagsImpl implements Flags {
        public String getStringFlag(String name) {
            return findStringJVMFlag0(name);
        }

        public void setStringFlag(String name, String value) {
            setStringJVMFlag0(name, value);
        }

        public boolean getBooleanFlag(String name) {
            return findBooleanJVMFlag0(name);
        }

        public void setBooleanFlag(String name, boolean value) {
            setBooleanJVMFlag0(name, value);
        }

        public long getIntFlag(String name) {
            return findIntJVMFlag0(name);
        }

        public double getFloatFlag(String name) {
            return findFloatJVMFlag0(name);
        }
    }

    public static JVMAccess getInstance() {
        return SingletonHolder.INSTANCE;
    }

    private final LibraryLoader.Result libraryLoadResult;
    private final Flags flags;

    private JVMAccess() {
        LibraryLoader.Result result = LibraryLoader.builder().load();;
        if (result.success) {
            // library loaded successfully, check if we can access JVM
            try {
                healthCheck0();
            } catch (Throwable t) {
                // failed to access JVM; update the result
                result = new LibraryLoader.Result(false, t);
            }

        }
        if (!result.success && result.error != null) {
            System.out.println("[WARNING] Failed to obtain JVM access.\n" + result.error);
        }
        flags = result.success ? new FlagsImpl() : Flags.NONE;
        libraryLoadResult = result;
    }

    public JVMAccess(String libLocation, String scratchDir, Consumer<Throwable> errorHandler) {
        LibraryLoader.Result result = LibraryLoader.builder().withLibraryLocation(libLocation).withScratchDir(scratchDir).load();
        if (result.success) {
            // library loaded successfully, check if we can access JVM
            try {
                healthCheck0();
            } catch (Throwable t) {
                // failed to access JVM; update the result
                result = new LibraryLoader.Result(false, t);
            }

        }
        if (!result.success && result.error != null) {
            if (errorHandler != null) {
                errorHandler.accept(result.error);
            } else {
                System.out.println("[WARNING] Failed to obtain JVM access.\n" + result.error);
            }
        }
        flags = result.success ? new FlagsImpl() : Flags.NONE;
        libraryLoadResult = result;
    }

    public Flags flags() {
        return flags;
    }

    public boolean isActive() {
        return libraryLoadResult.success;
    }

    // a dummy method to check if the library has loaded properly
    private native boolean healthCheck0();

    private native String findStringJVMFlag0(String name);
    private native void setStringJVMFlag0(String name, String value);
    private native boolean findBooleanJVMFlag0(String name);
    private native void setBooleanJVMFlag0(String name, boolean value);
    private native long findIntJVMFlag0(String name);
    private native double findFloatJVMFlag0(String name);
}
