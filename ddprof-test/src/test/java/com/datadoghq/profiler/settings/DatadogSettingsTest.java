package com.datadoghq.profiler.settings;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

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
        IItemCollection events = verifyEvents("datadog.ProfilerSetting");
        final IAttribute<String> nameAttr =
                attr("name", "", "", PLAIN_TEXT);
        final IAttribute<String> valueAttr =
                attr("value", "", "", PLAIN_TEXT);
        final IAttribute<String> unitAttr =
                attr("unit", "", "", PLAIN_TEXT);
        boolean dimensionlessChecked = false;
        boolean withUnitChecked = false;
        int longValuesChecked = 0;
        for (IItemIterable settings : events) {
            IMemberAccessor<String, IItem> nameAccessor = nameAttr.getAccessor(settings.getType());
            IMemberAccessor<String, IItem> valueAccessor = valueAttr.getAccessor(settings.getType());
            IMemberAccessor<String, IItem> unitAccessor = unitAttr.getAccessor(settings.getType());
            for (IItem setting : settings) {
                String name = nameAccessor.getMember(setting);
                String value = valueAccessor.getMember(setting);
                String unit = unitAccessor.getMember(setting);
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
        }
        assertTrue(dimensionlessChecked);
        assertTrue(withUnitChecked);
        assertEquals(10000, longValuesChecked);
    }
}
