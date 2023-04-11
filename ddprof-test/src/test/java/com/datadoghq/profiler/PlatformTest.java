package com.datadoghq.profiler;

import java.util.stream.Stream;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;


import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.*;

class PlatformTest {
    @Test
    void isAtLeastJava7() {
        assertTrue(Platform.isJavaVersionAtLeast(7));
    }

    @Test
    void isAtLeastJava8() {
        assumeTrue(!System.getProperty("java.version").startsWith("1.")
            || System.getProperty("java.version").startsWith("1.8."));
        assertTrue(Platform.isJavaVersionAtLeast(8) && Platform.isJavaVersionAtLeast(7));
    }

    @Test
    void isAtLeastJava11() {
        assumeTrue(!System.getProperty("java.version").startsWith("1.")
            && !(System.getProperty("java.version").startsWith("9.")
            || System.getProperty("java.version").startsWith("10.")));
        assertTrue(Platform.isJavaVersionAtLeast(11) && Platform.isJavaVersionAtLeast(8));
    }

    @ParameterizedTest
    @MethodSource("parseArgsExact")
    void testParse(String version, int major, int minor, int update) {
        Platform.Version javaVersion = Platform.parseJavaVersion(version);

        assertEquals(major, javaVersion.major);
        assertEquals(minor, javaVersion.minor);
        assertEquals(update, javaVersion.update);
        assertTrue(javaVersion.is(major));
        assertTrue(javaVersion.is(major, minor));
        assertTrue(javaVersion.is(major, minor, update));
        assertTrue(javaVersion.isAtLeast(major, minor, update));
        assertTrue(javaVersion.isBetween(major, minor, update, Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE));
        assertFalse(javaVersion.isBetween(major, minor, update, major, minor, update));
        assertFalse(javaVersion.isBetween(major, minor, update, major - 1, 0, 0));
        assertFalse(javaVersion.isBetween(major, minor, update, major, minor -1, 0));
        assertFalse(javaVersion.isBetween(major, minor, update, major, minor, update - 1));
        assertTrue(javaVersion.isBetween(major, minor, update, major + 1, 0, 0));
        assertTrue(javaVersion.isBetween(major, minor, update, major, minor + 1, 0));
        assertTrue(javaVersion.isBetween(major, minor, update, major, minor, update + 1));
    }

    @ParameterizedTest
    @MethodSource("parseArgsAtLeast")
    void testParseAtLeast(String version, int major, int minor, int update) {
        Platform.Version javaVersion = Platform.parseJavaVersion(version);
        assertTrue(javaVersion.isAtLeast(major, minor, update));
    }

    @ParameterizedTest
    @MethodSource("parseArgsWeird")
    void tetParseWeird(String propVersion, String rtVersion, String propName, String propVendor, String version, String patch, String name, String vendor) {
        Platform.JvmRuntime runtime = new Platform.JvmRuntime(propVersion, rtVersion, propName, propVendor);

        assertEquals(version, runtime.version);
        assertEquals(patch, runtime.patches);
        assertEquals(name, runtime.name);
        assertEquals(vendor, runtime.vendor);
    }

    private static Stream<Arguments> parseArgsExact() {
        return Stream.of(
            Arguments.of(""          , 0     , 0     , 0),
            Arguments.of("a.0.0"     , 0     , 0     , 0),
            Arguments.of("0.a.0"     , 0     , 0     , 0),
            Arguments.of("0.0.a"     , 0     , 0     , 0),
            Arguments.of("1.a.0_0"   , 0     , 0     , 0),
            Arguments.of("1.8.a_0"   , 0     , 0     , 0),
            Arguments.of("1.8.0_a"   , 0     , 0     , 0),
            Arguments.of("1.7"       , 7     , 0     , 0),
            Arguments.of("1.7.0"     , 7     , 0     , 0),
            Arguments.of("1.7.0_221" , 7     , 0     , 221),
            Arguments.of("1.8"       , 8     , 0     , 0),
            Arguments.of("1.8.0"     , 8     , 0     , 0),
            Arguments.of("1.8.0_212" , 8     , 0     , 212),
            Arguments.of("1.8.0_292" , 8     , 0     , 292),
            Arguments.of("9-ea"      , 9     , 0     , 0),
            Arguments.of("9.0.4"     , 9     , 0     , 4),
            Arguments.of("9.1.2"     , 9     , 1     , 2),
            Arguments.of("10.0.2"    , 10    , 0     , 2),
            Arguments.of("11"        , 11    , 0     , 0),
            Arguments.of("11.0.6"    , 11    , 0     , 6),
            Arguments.of("11.0.11"   , 11    , 0     , 11),
            Arguments.of("12.0.2"    , 12    , 0     , 2),
            Arguments.of("13.0.2"    , 13    , 0     , 2),
            Arguments.of("14"        , 14    , 0     , 0),
            Arguments.of("14.0.2"    , 14    , 0     , 2),
            Arguments.of("15"        , 15    , 0     , 0),
            Arguments.of("15.0.2"    , 15    , 0     , 2),
            Arguments.of("16.0.1"    , 16    , 0     , 1),
            Arguments.of("11.0.9.1+1", 11    , 0     , 9),
            Arguments.of("11.0.6+10" , 11    , 0     , 6),
            Arguments.of("17.0.4-x"  , 17    , 0     , 4)
        );
    }

    private static Stream<Arguments> parseArgsAtLeast() {
        return Stream.of(
            Arguments.of("17.0.5+8"  , 17    , 0     , 5),
            Arguments.of("17.0.5"    , 17    , 0     , 5),
            Arguments.of("17.0.6+8"  , 17    , 0     , 5),
            Arguments.of("11.0.17+8" , 11    , 0     , 17),
            Arguments.of("11.0.18+8" , 11    , 0     , 17),
            Arguments.of("11.0.17"   , 11    , 0     , 17),
            Arguments.of("1.8.0_352" , 8     , 0     , 352),
            Arguments.of("1.8.0_362" , 8     , 0     , 352)
        );
    }

    private static Stream<Arguments> parseArgsWeird() {
        return Stream.of(
            Arguments.of("1.8.0_265" , "1.8.0_265-b01" , "OpenJDK"        , "AdoptOpenJDK" , "1.8.0_265" , "b01" , "OpenJDK"        , "AdoptOpenJDK"),
            Arguments.of("1.8.0_265" , "1.8-b01"       , "OpenJDK"        , "AdoptOpenJDK" , "1.8.0_265" , ""    , "OpenJDK"        , "AdoptOpenJDK"),
            Arguments.of("19"        , "19"            , "OpenJDK 64-Bit" , "Homebrew"     , "19"        , ""    , "OpenJDK 64-Bit" , "Homebrew"),
            Arguments.of("17"        , null            , null             , null           , "17"        , ""    , ""               , ""),
            Arguments.of(null        , "17"            , null             , null           , ""          , ""    , ""               , "")
        );
    }
}