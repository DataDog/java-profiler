package com.datadoghq.profiler;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.EnumSet;
import java.util.HashSet;
import java.util.Set;

/** A simple way to detect the current operating system */
enum OperatingSystem {
    linux("Linux", "linux"),
    macos("Mac OS X", "macOS", "mac"),
    unknown();
  
    private final Set<String> identifiers;
  
    OperatingSystem(String... identifiers) {
      this.identifiers = new HashSet<>(Arrays.asList(identifiers));
    }
  
    public static OperatingSystem of(String identifier) {
      for (OperatingSystem os : EnumSet.allOf(OperatingSystem.class)) {
        if (os.identifiers.contains(identifier)) {
          return os;
        }
      }
      return unknown;
    }
  
    public static OperatingSystem current() {
      return OperatingSystem.of(System.getProperty("os.name"));
    }

    public boolean isMusl() throws IOException {
        // check the Java exe then fall back to proc/self maps
        try {
            return isMuslJavaExecutable();
        } catch (IOException e) {
            try {
                return isMuslProcSelfMaps();
            } catch (IOException ignore) {
                // not finding the Java exe is more interesting than failing to parse /proc/self/maps
                throw e;
            }
        }
    }

    // package-private access for testing only
    boolean isMuslProcSelfMaps() throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader("/proc/self/maps"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.contains("-musl-")) {
                    return true;
                }
                if (line.contains("/libc.")) {
                    return false;
                }
            }
        }
        return false;
    }

    /**
     * There is information about the linking in the ELF file. Since properly parsing ELF is not
     * trivial this code will attempt a brute-force approach and will scan the first 4096 bytes
     * of the 'java' program image for anything prefixed with `/ld-` - in practice this will contain
     * `/ld-musl` for musl systems and probably something else for non-musl systems (eg. `/ld-linux-...`).
     * However, if such string is missing should indicate that the system is not a musl one.
     */
    // package-private access for testing only
    boolean isMuslJavaExecutable() throws IOException {

        byte[] magic = new byte[]{(byte)0x7f, (byte)'E', (byte)'L', (byte)'F'};
        byte[] prefix = new byte[]{(byte)'/', (byte)'l', (byte)'d', (byte)'-'}; // '/ld-*'
        byte[] musl = new byte[]{(byte)'m', (byte)'u', (byte)'s', (byte)'l'}; // 'musl'

        Path binary = Paths.get(System.getProperty("java.home"), "bin", "java");
        byte[] buffer = new byte[4096];

        try (InputStream is = Files.newInputStream(binary)) {
            int read = is.read(buffer, 0, 4);
            if (read != 4 || !containsArray(buffer, 0, magic)) {
                throw new IOException(Arrays.toString(buffer));
            }
            read = is.read(buffer);
            if (read <= 0) {
                throw new IOException();
            }
            int prefixPos = 0;
            for (int i = 0; i < read; i++) {
                if (buffer[i] == prefix[prefixPos]) {
                    if (++prefixPos == prefix.length) {
                        return containsArray(buffer, i + 1, musl);
                    }
                } else {
                    prefixPos = 0;
                }
            }
        }
        return false;
    }

    private static boolean containsArray(byte[] container, int offset, byte[] contained) {
        for (int i = 0; i < contained.length; i++) {
            int leftPos = offset + i;
            if (leftPos >= container.length) {
                return false;
            }
            if (container[leftPos] != contained[i]) {
                return false;
            }
        }
        return true;
    }
  }
