/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * libFuzzer fuzz target for the triple-buffered StringDictionary.
 *
 * The fuzzer interprets each input as a sequence of dictionary operations and
 * verifies the documented sequential invariants of StringDictionary:
 *
 *   I1. Once a key has an id, every subsequent successful lookup of that key
 *       returns the same id — across any number of rotate()/clearStandby() cycles.
 *
 *   I2. The signal-safe read-only bounded_lookup(key, len) never returns an id
 *       for a key that was never inserted into the active buffer.
 *
 *   I3. lookupDuringDump(key) either returns 0 or returns an id that is also
 *       resolvable from standby()->collect().
 *
 *   I4. clearAll() resets state — after clearAll(), no previously recorded id
 *       must be observable via any read path.
 *
 * Address/UB sanitizer is expected to be enabled by the fuzz build; UAFs and
 * heap corruption from the malloc'd key storage will be caught automatically.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <map>
#include <string>
#include <unordered_map>

#include "stringDictionary.h"

namespace {

// Bound the working set so a pathological corpus does not OOM the fuzzer.
constexpr int kMaxUniqueKeys     = 4096;
constexpr int kBoundedSizeLimit  = 8192;
constexpr size_t kMaxKeyLen      = 31;  // mask of the length byte

// Read a length-prefixed key from the input.  '\0' bytes are mapped to '_' so
// the key is a valid C string (StringDictionary uses NUL-terminated comparison).
// Advances pos.  Returns an empty key when the input is exhausted.
std::string readKey(const uint8_t *data, size_t size, size_t &pos) {
    if (pos >= size) return {};
    size_t len = data[pos++] & kMaxKeyLen;
    if (pos + len > size) len = size - pos;
    std::string out;
    out.reserve(len);
    for (size_t i = 0; i < len; i++) {
        char c = (char)data[pos + i];
        out.push_back(c == '\0' ? '_' : c);
    }
    pos += len;
    return out;
}

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    StringDictionary dict;
    std::unordered_map<std::string, u32> shadow;  // key -> expected id
    bool has_dump_buffer = false;                 // true after first rotate()

    size_t pos = 0;
    while (pos < size) {
        uint8_t op = data[pos++];

        if (op < 0x40) {
            // lookup (insert into active)
            std::string k = readKey(data, size, pos);
            if (shadow.size() >= kMaxUniqueKeys && shadow.find(k) == shadow.end()) {
                continue;
            }
            u32 id = dict.lookup(k.c_str(), k.size());
            if (id == 0) continue;
            auto it = shadow.find(k);
            if (it == shadow.end()) {
                shadow.emplace(k, id);
            } else if (it->second != id) {
                __builtin_trap();  // I1: id changed for known key
            }
        } else if (op < 0x60) {
            // bounded_lookup with insert (high cap)
            std::string k = readKey(data, size, pos);
            if (shadow.size() >= kMaxUniqueKeys && shadow.find(k) == shadow.end()) {
                continue;
            }
            u32 id = dict.bounded_lookup(k.c_str(), k.size(), kBoundedSizeLimit);
            if (id == 0) continue;  // at cap is legitimate
            auto it = shadow.find(k);
            if (it == shadow.end()) {
                shadow.emplace(k, id);
            } else if (it->second != id) {
                __builtin_trap();  // I1
            }
        } else if (op < 0x70) {
            // bounded_lookup signal-safe (read-only)
            std::string k = readKey(data, size, pos);
            u32 id = dict.bounded_lookup(k.c_str(), k.size());
            auto it = shadow.find(k);
            if (it == shadow.end()) {
                if (id != 0) __builtin_trap();  // I2: phantom id
            } else if (id != 0 && id != it->second) {
                __builtin_trap();  // I1: id changed
            }
            // Note: id may legitimately be 0 if the key only ever existed in
            // standby/dump (e.g. inserted, then clearAll, then nothing); we
            // already cleared the shadow in that case, so shadow.find would miss.
        } else if (op < 0x80) {
            // lookupDuringDump — only legal once we have a dump buffer.
            std::string k = readKey(data, size, pos);
            if (!has_dump_buffer) continue;
            if (shadow.size() >= kMaxUniqueKeys && shadow.find(k) == shadow.end()) {
                continue;
            }
            u32 id = dict.lookupDuringDump(k.c_str(), k.size());
            if (id == 0) continue;
            auto it = shadow.find(k);
            if (it == shadow.end()) {
                shadow.emplace(k, id);
            } else if (it->second != id) {
                __builtin_trap();  // I1
            }
            // I3: lookupDuringDump must leave the key resolvable from standby().
            std::map<u32, const char*> snap;
            dict.standby()->collect(snap);
            auto found = snap.find(id);
            if (found == snap.end() || k != found->second) {
                __builtin_trap();
            }
        } else if (op < 0x90) {
            // rotate
            dict.rotate();
            has_dump_buffer = true;
        } else if (op < 0xA0) {
            // clearStandby (clears scratch; does not affect active)
            dict.clearStandby();
        } else if (op < 0xA8) {
            // clearAll — sequential fuzz only; not exercising signal-time semantics.
            dict.clearAll();
            shadow.clear();
            has_dump_buffer = false;
        }
        // 0xA8-0xFF: noop / spacer — keeps the corpus density adjustable.
    }

    return 0;
}
