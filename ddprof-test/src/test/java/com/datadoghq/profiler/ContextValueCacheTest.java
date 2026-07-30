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
package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNotSame;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertSame;

/**
 * Unit tests for {@link ContextValueCache}, the process-wide value cache backing the all-native
 * context write path. Package-private, so this test lives in {@code com.datadoghq.profiler}.
 */
public class ContextValueCacheTest {

    private final ContextValueCache cache = new ContextValueCache();

    private static void loadLibrary() throws IOException {
        JavaProfiler.getInstance(); // registerConstant0 is native
    }

    @Test
    public void nullResolvesToNull() throws IOException {
        loadLibrary();
        assertNull(cache.resolve(null));
    }

    @Test
    public void resolveHitsCacheOnSecondLookup() throws IOException {
        loadLibrary();
        ContextValueCache.Entry first = cache.resolve("hello");
        assertNotNull(first);
        ContextValueCache.Entry second = cache.resolve("hello");
        assertSame(first, second, "an unchanged value must hit the cache, not re-register");
    }

    @Test
    public void oversizedValueResolvesToNull() throws IOException {
        loadLibrary();
        char[] chars = new char[ContextValueCache.MAX_VALUE_BYTES + 1];
        Arrays.fill(chars, 'x');
        assertNull(cache.resolve(new String(chars)));
    }

    @Test
    public void maxSizeValueResolves() throws IOException {
        loadLibrary();
        char[] chars = new char[ContextValueCache.MAX_VALUE_BYTES];
        Arrays.fill(chars, 'x');
        String value = new String(chars);
        ContextValueCache.Entry e = cache.resolve(value);
        assertNotNull(e);
        assertEquals(ContextValueCache.MAX_VALUE_BYTES, e.utf8.length);
    }

    @Test
    public void hashCollisionEvictsPreviousEntryButBothRemainResolvable() throws IOException {
        loadLibrary();
        // ContextValueCache is direct-mapped by value.hashCode() & 0xFF (SIZE=256). Find two
        // distinct strings that collide in the same slot to exercise the eviction path.
        String a = "collision-a";
        int slotA = a.hashCode() & 0xFF;
        String b = null;
        for (int i = 0; i < 100_000; i++) {
            String candidate = "collision-b-" + i;
            if ((candidate.hashCode() & 0xFF) == slotA && !candidate.equals(a)) {
                b = candidate;
                break;
            }
        }
        assertNotNull(b, "failed to find a colliding string for the test slot");

        ContextValueCache.Entry entryA = cache.resolve(a);
        assertNotNull(entryA);
        ContextValueCache.Entry entryB = cache.resolve(b);
        assertNotNull(entryB);
        assertNotEquals(entryA.encoding, entryB.encoding);

        // Re-resolving "a" after it was evicted from its slot by "b" must still work — it's a
        // cache miss, so it re-registers and gets a fresh (but valid) entry.
        ContextValueCache.Entry entryAAgain = cache.resolve(a);
        assertNotNull(entryAAgain);
        assertEquals(a, entryAAgain.key);
    }

    @Test
    public void clearDropsCachedEntries() throws IOException {
        loadLibrary();
        ContextValueCache.Entry before = cache.resolve("to-clear");
        assertNotNull(before);
        cache.clear();
        ContextValueCache.Entry after = cache.resolve("to-clear");
        assertNotNull(after);
        assertNotSame(before, after, "resolve after clear() must not return the pre-clear entry");
    }
}
