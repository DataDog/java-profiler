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
//   bit 30       RAW_POINTER_MASK  — value is a raw native PC (HotSpot only)
//   bits 23–21   frame type        — FrameTypeId (0–7)
//   bit 20       ENCODED_MASK      — set to distinguish encoded values from raw ASGCT BCIs
//   bits 15–0    BCI               — bytecode index (0–65534; never 65535, see BCI_MASK)
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
public:
  // Produces an encoded int from a frame type and BCI. Negative BCIs (HotSpot -1 sentinels
  // for method-entry/sync-entry) are mapped to 0 rather than wrapping to 0xffff.
  static inline int encode(int type, int bci, bool rawPointer = false) {
    assert((!rawPointer || VM::isHotspot()) && "Raw pointer is only valid for hotspot");
    assert(type >= FRAME_INTERPRETED && type <= FRAME_TYPE_MAX);
    int bci_bits = (bci < 0) ? 0 : (bci & BCI_MASK);
    return ENCODED_MASK | (type << TYPE_SHIFT) | bci_bits | (rawPointer ? RAW_POINTER_MASK : 0);
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

  static inline bool isRawPointer(int bci) {
    return bci > 0 && (bci & RAW_POINTER_MASK) != 0;
  }
};

#endif // _FRAME_H
