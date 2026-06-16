/*
 * Copyright 2026, Datadog, Inc
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
package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Method;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that {@code VMMethod::getLinenumberTable()} produces the same entries as the JVM's
 * JVMTI {@code GetLineNumberTable} on the same method.
 *
 * <p>The comparison is only executed on JDK &lt;= 25 where {@code jmethodID} can be safely
 * dereferenced to a {@code VMMethod*}. On JDK &gt; 25 (after JDK-8268406) the VMMethod path
 * returns {@code null} and the test limits itself to validating the JVMTI table alone.
 */
public class LineNumberTableTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        // Minimal profiling: we only need the agent loaded so VMStructs are initialized.
        return "cpu=100ms";
    }

    // ---- target method with multiple distinct line-number table entries ----

    @SuppressWarnings("unused")
    private static int multiLineMethod(int x) {
        int a = x + 1;
        int b = a * 2;
        if (b > 10) {
            return b;
        }
        return a;
    }

    @SuppressWarnings("unused")
    private static void emptyVoidMethod() {
    }

    // ---- tests ----

    /**
     * Core contract: VMMethod::getLinenumberTable() must return the same (bci, lineNumber) pairs
     * as JVMTI GetLineNumberTable for the same method.
     */
    @Test
    public void testVMMethodTableMatchesJvmti() throws Exception {
        stopProfiler();

        Method method = LineNumberTableTest.class.getDeclaredMethod("multiLineMethod", int.class);

        long[] jvmtiTable = JavaProfiler.getJvmtiLineNumberTable0(method);
        assertNotNull(jvmtiTable, "JVMTI GetLineNumberTable returned null for multiLineMethod");
        assertTrue(jvmtiTable.length > 0, "JVMTI line number table must not be empty");

        long[] vmMethodTable = JavaProfiler.getVMMethodLineNumberTable0(method);
        if (vmMethodTable == null) {
            // JDK > 25: jmethodID dereference is not supported, skip VMMethod comparison.
            return;
        }

        assertArrayEquals(jvmtiTable, vmMethodTable,
                "VMMethod::getLinenumberTable() must match JVMTI GetLineNumberTable.\n"
                        + "JVMTI:    " + Arrays.toString(jvmtiTable) + "\n"
                        + "VMMethod: " + Arrays.toString(vmMethodTable));
    }

    /**
     * The JVMTI table must be a non-empty sequence of (bci, lineNumber) pairs where BCIs are
     * non-negative and strictly non-decreasing, and line numbers are positive.
     */
    @Test
    public void testJvmtiTableStructure() throws Exception {
        stopProfiler();

        Method method = LineNumberTableTest.class.getDeclaredMethod("multiLineMethod", int.class);
        long[] table = JavaProfiler.getJvmtiLineNumberTable0(method);

        assertNotNull(table, "JVMTI GetLineNumberTable returned null");
        assertTrue(table.length % 2 == 0, "Table length must be even (bci/line pairs)");
        assertTrue(table.length > 0, "Table must have at least one entry");

        long prevBci = -1;
        for (int i = 0; i < table.length; i += 2) {
            long bci = table[i];
            long line = table[i + 1];
            assertTrue(bci >= 0, "BCI must be non-negative at index " + i + ", got " + bci);
            assertTrue(bci > prevBci,
                    "BCIs must be strictly increasing; at index " + i + " bci=" + bci
                            + " <= prevBci=" + prevBci);
            assertTrue(line > 0, "Line number must be positive at index " + i + ", got " + line);
            prevBci = bci;
        }
    }

    /**
     * The first BCI in the table must be 0 (method entry maps to the first source line).
     */
    @Test
    public void testFirstEntryBciIsZero() throws Exception {
        stopProfiler();

        Method method = LineNumberTableTest.class.getDeclaredMethod("multiLineMethod", int.class);
        long[] table = JavaProfiler.getJvmtiLineNumberTable0(method);

        assertNotNull(table);
        assertTrue(table.length >= 2, "Table must have at least one entry");
        assertEquals(0L, table[0], "First BCI in line number table must be 0");
    }

    /**
     * VMMethod path must also produce a well-formed table (non-negative BCIs, positive lines)
     * when it is available (JDK <= 25).
     */
    @Test
    public void testVMMethodTableStructure() throws Exception {
        stopProfiler();

        Method method = LineNumberTableTest.class.getDeclaredMethod("multiLineMethod", int.class);
        long[] table = JavaProfiler.getVMMethodLineNumberTable0(method);

        if (table == null) {
            // JDK > 25: not supported.
            return;
        }

        assertTrue(table.length % 2 == 0, "Table length must be even");
        assertTrue(table.length > 0, "Table must have at least one entry");

        long prevBci = -1;
        for (int i = 0; i < table.length; i += 2) {
            long bci  = table[i];
            long line = table[i + 1];
            assertTrue(bci >= 0,    "BCI must be non-negative");
            assertTrue(bci > prevBci, "BCIs must be strictly increasing");
            assertTrue(line > 0,    "Line number must be positive");
            prevBci = bci;
        }
    }

    /**
     * Both paths must handle a trivial method gracefully. The empty void method still has a
     * line number table with at least the method-entry entry.
     */
    @Test
    public void testTrivialMethodHasLineTable() throws Exception {
        stopProfiler();

        Method method = LineNumberTableTest.class.getDeclaredMethod("emptyVoidMethod");

        long[] jvmtiTable = JavaProfiler.getJvmtiLineNumberTable0(method);
        assertNotNull(jvmtiTable, "JVMTI must return a table even for a trivial method");
        assertTrue(jvmtiTable.length >= 2, "Trivial method must have at least one line entry");

        long[] vmMethodTable = JavaProfiler.getVMMethodLineNumberTable0(method);
        if (vmMethodTable != null) {
            assertArrayEquals(jvmtiTable, vmMethodTable,
                    "VMMethod table must match JVMTI for trivial method");
        }
    }
}
