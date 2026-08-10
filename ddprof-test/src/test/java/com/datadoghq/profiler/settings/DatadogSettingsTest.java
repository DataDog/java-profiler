/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.settings;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class DatadogSettingsTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }

    @RetryingTest(5)
    public void testRecordDatadogSetting() {
        profiler.recordSetting("dimensionless", "value");
        profiler.recordSetting("withUnit", "60", "seconds");
        byte[] longValueBytes = new byte[8191];
        Arrays.fill(longValueBytes, (byte) 'a');
        for (int i = 0; i < 10000; i++) {
            profiler.recordSetting("long value " + i, new String(longValueBytes));
        }
        stopProfiler();
        JfrEvents events = verifyEvents("datadog.ProfilerSetting");
        boolean dimensionlessChecked = false;
        boolean withUnitChecked = false;
        int longValuesChecked = 0;
        for (JfrEvent setting : events) {
            String name = setting.getString("name");
            String value = setting.getString("value");
            String unit = setting.getString("unit");
            if (!dimensionlessChecked && name.equals("dimensionless")) {
                assertEquals("value", value);
                assertEquals("", unit);
                dimensionlessChecked = true;
            } else if (!withUnitChecked && "withUnit".equals(name)) {
                assertEquals("60", value);
                assertEquals("seconds", unit);
                withUnitChecked = true;
            } else {
                assertTrue(name.startsWith("long value"));
                assertEquals(longValueBytes.length, value.length());
                assertEquals("", unit);
                longValuesChecked++;
            }
        }
        assertTrue(dimensionlessChecked);
        assertTrue(withUnitChecked);
        assertEquals(10000, longValuesChecked);
    }
}
