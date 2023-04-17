package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.util.BitSet;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class DictionaryTest {

    @Test
    public void  testIdempotent() {
        Dictionary dictionary = new Dictionary((String key, int encoding) -> {});
        String key = "key";

        int expected = dictionary.encode(key);
        assertEquals(expected, dictionary.encode(key));
        for (int i = 0; i < 10000; i++) {
            dictionary.encode(key + i);
        }
        assertEquals(expected, dictionary.encode(key));
    }

    @Test
    public void testHashCollision() {
        Map<Integer, CharSequence> encoded = new HashMap<>();
        BitSet bitset = new BitSet();
        Dictionary dictionary = new Dictionary((String key, int encoding) -> {
            CharSequence old = encoded.put(encoding, key);
            assertNull(old,  old + " replaced by " + key);
        });
        String key1 = "Aa";
        String key2 = "BB";
        assertEquals(key1.hashCode(), key2.hashCode(), "precondition: seed strings must collide");

        int key1Encoding = dictionary.encode(key1);
        int key2Encoding = dictionary.encode(key2);
        bitset.set(key1Encoding);
        bitset.set(key2Encoding);
        assertNotEquals(key1Encoding, key2Encoding);
        int numCollisionsAdded = 10000;
        for (int i = 0; i < numCollisionsAdded; i++) {
            // hash codes also collide with each other
            int e1 = dictionary.encode(key1 + i);
            int e2 = dictionary.encode(key2 + i);
            bitset.set(e1);
            bitset.set(e2);
        }
        assertEquals(key1Encoding, dictionary.encode(key1));
        assertEquals(key2Encoding, dictionary.encode(key2));
        assertEquals(2 * (numCollisionsAdded + 1), bitset.cardinality());
    }

    @Test
    public void testDump() {
        Map<CharSequence, Integer> target = new HashMap<>();
        Dictionary dictionary = new Dictionary(target::put);
        Map<CharSequence, Integer> reference = new HashMap<>();
        for (int i = 0; i < 10000; i++) {
            String key = UUID.randomUUID().toString();
            reference.put(key, dictionary.encode(key));
        }
        assertEquals(reference, target);
    }
}
