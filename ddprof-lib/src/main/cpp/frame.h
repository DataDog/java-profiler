/*
 * Copyright 2026 Datadog, Inc
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
#ifndef _FRAME_H
#define _FRAME_H

#include <cassert>
#include <cstdint>
#include "vmEntry.h"

enum FrameTypeId {
  FRAME_INTERPRETED = 0,
  FRAME_JIT_COMPILED = 1,
  FRAME_INLINED = 2,
  FRAME_NATIVE = 3,
  FRAME_CPP = 4,
  FRAME_KERNEL = 5,
  FRAME_C1_COMPILED = 6,
  FRAME_NATIVE_REMOTE = 7,  // Native frame with remote symbolication (build-id + pc-offset)
  FRAME_TYPE_MAX = FRAME_NATIVE_REMOTE,  // Maximum valid frame type
  FRAME_TYPE_MASK = 0x7
};

// Packs frame type and BCI into a single int field stored in CallTrace frames.
//
// Bit layout of an encoded value (ENCODED_MASK set):
//   bit 30       RAW_POINTER_MASK  — method field is a raw Method* (HotSpot only)
//   bits 29–24   raw tag, bits 9–4 — only with RAW_POINTER_MASK, see below
//   bits 23–21   frame type        — FrameTypeId (0–7)
//   bit 20       ENCODED_MASK      — set to distinguish encoded values from raw ASGCT BCIs
//   bits 19–16   raw tag, bits 3–0 — only with RAW_POINTER_MASK, see below
//   bits 15–0    BCI               — bytecode index (0–65534; never 65535, see BCI_MASK)
//
// A raw Method* frame also carries a RAW_TAG_BITS-wide tag: the KlassRegistry
// epoch the frame was sampled under (hotspot/klassRegistry.h). Its low 10 bits
// sit in the otherwise unused BCI bits above; its high 16 bits sit in the top
// 16 bits of the Method* pointer, which user-space addresses below 2^48 leave
// clear. The tag makes frames sampled from different loads of a class at the
// same Klass*/Method* addresses differ, and lets resolution reject frames that
// predate the class currently registered at that address.
//
// When ENCODED_MASK is not set the field is a raw, unencoded BCI from ASGCT (non-VM stack
// walking modes). Raw values may be negative: HotSpot uses -1 as a sentinel for method-entry
// and synchronization-entry samples. Both encode() and bci() clamp negative values to 0 so
// that 65535 (the mask value itself) is never emitted and can be treated as unreachable.
// decode() returns FRAME_JIT_COMPILED for all unencoded or negative values.
class FrameType {
  // JVM spec §4.7.3 caps method bytecode at 65535 bytes, so valid BCIs are 0–65534.
  // The mask value 65535 (0xffff) is therefore never a valid BCI; we keep it unreachable
  // by clamping negative sentinels to 0 in encode() and bci().
  static constexpr int BCI_MASK = 0xffff;
  static constexpr int TYPE_SHIFT = 21;
  static constexpr int ENCODED_MASK = 1 << 20;  // distinguishes encoded values from raw ASGCT BCIs
  static constexpr int RAW_POINTER_MASK = 1 << 30;
  static constexpr int RAW_TAG_LOW_SHIFT = 16;   // tag bits 3–0 -> bits 19–16
  static constexpr int RAW_TAG_MID_SHIFT = 24;   // tag bits 9–4 -> bits 29–24
  static constexpr int RAW_TAG_BCI_BITS = 10;
  static constexpr int POINTER_TAG_SHIFT = 48;   // tag bits 25–10 -> pointer bits 63–48
  static constexpr uintptr_t POINTER_ADDRESS_MASK = ((uintptr_t)1 << POINTER_TAG_SHIFT) - 1;
public:
  static constexpr int RAW_TAG_BITS = 26;
  static constexpr uint32_t RAW_TAG_MASK = (1u << RAW_TAG_BITS) - 1;

  // Produces an encoded int from a frame type and BCI. Negative BCIs (HotSpot -1 sentinels
  // for method-entry/sync-entry) are mapped to 0 rather than wrapping to 0xffff.
  static inline int encode(int type, int bci, bool rawPointer = false) {
    assert((!rawPointer || VM::isHotspot()) && "Raw pointer is only valid for hotspot");
    assert(type >= FRAME_INTERPRETED && type <= FRAME_TYPE_MAX);
    int bci_bits = (bci < 0) ? 0 : (bci & BCI_MASK);
    return ENCODED_MASK | (type << TYPE_SHIFT) | bci_bits | (rawPointer ? RAW_POINTER_MASK : 0);
  }

  // Encodes a raw Method* frame carrying `tag` (see the layout above). The
  // matching method field is tagPointer(method, tag).
  static inline int encodeRaw(int type, int bci, uint32_t tag) {
    return encode(type, bci, true) | (int)((tag & 0xf) << RAW_TAG_LOW_SHIFT) |
           (int)(((tag >> 4) & 0x3f) << RAW_TAG_MID_SHIFT);
  }

  // True if `ptr` leaves the pointer tag bits clear, i.e. tagPointer() is reversible.
  static inline bool canTagPointer(const void* ptr) {
    return ((uintptr_t)ptr & ~POINTER_ADDRESS_MASK) == 0;
  }

  static inline const void* tagPointer(const void* ptr, uint32_t tag) {
    assert(canTagPointer(ptr));
    uintptr_t high = (uintptr_t)((tag & RAW_TAG_MASK) >> RAW_TAG_BCI_BITS);
    return (const void*)((uintptr_t)ptr | (high << POINTER_TAG_SHIFT));
  }

  static inline const void* untagPointer(const void* ptr) {
    return (const void*)((uintptr_t)ptr & POINTER_ADDRESS_MASK);
  }

  // Reassembles the tag of a raw Method* frame from its encoded BCI and method field.
  static inline uint32_t rawTag(int bci, const void* ptr) {
    uint32_t low = ((uint32_t)bci >> RAW_TAG_LOW_SHIFT) & 0xf;
    uint32_t mid = ((uint32_t)bci >> RAW_TAG_MID_SHIFT) & 0x3f;
    uint32_t high = (uint32_t)((uintptr_t)ptr >> POINTER_TAG_SHIFT);
    return (low | (mid << 4) | (high << RAW_TAG_BCI_BITS)) & RAW_TAG_MASK;
  }

  // Extracts the BCI from either an encoded value or a raw ASGCT BCI.
  // Negative values (HotSpot -1 sentinels) are clamped to 0, matching encode().
  static inline int bci(int bci) {
    return (bci < 0) ? 0 : (bci & BCI_MASK);
  }

  // Extracts the FrameTypeId from an encoded value.
  // Returns FRAME_JIT_COMPILED for unencoded raw ASGCT BCIs and for negative sentinels,
  // since no type information is available in those cases.
  static inline FrameTypeId decode(int bci) {
    if ((bci & ENCODED_MASK) == 0 || bci < 0) {
      return FRAME_JIT_COMPILED;
    }
    return (FrameTypeId)((bci >> TYPE_SHIFT) & FRAME_TYPE_MASK);
  }

  // Raw pointers only exist on HotSpot (see hotspotSupport.cpp fillFrameRaw),
  // and RAW_POINTER_MASK is only ever set by encode(..., rawPointer=true),
  // which unconditionally also sets ENCODED_MASK. Requiring both HotSpot and
  // ENCODED_MASK prevents a raw, VM-supplied ASGCT BCI from false-positiving
  // just because it happens to have bit 30 set.
  static inline bool isRawPointer(int bci) {
    return VM::isHotspot() && (bci > 0 && (bci & ENCODED_MASK) != 0 && (bci & RAW_POINTER_MASK) != 0);
  }
};

#endif // _FRAME_H
