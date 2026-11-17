/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFERENCECHAINOBSERVATION_H
#define _REFERENCECHAINOBSERVATION_H

#include "arch.h"
#include "spinLock.h"
#include <jni.h>

// One callback report's anchor effects for one frontier tag. Callbacks only record these; the
// caller replays them in arrival order after the synchronous JVMTI traversal returns.
struct AnchorObservation {
  static constexpr u8 LOCAL = 1;             // noteLocalRootHolder(tag, own_class_tag)
  static constexpr u8 DURABLE_ADD = 2;       // addToStaticAnchorIndex(tag, durable_root_kind, own_class_tag)
  static constexpr u8 REENLIST_ELIGIBLE = 4; // indexAnchorForRotation() if not indexed
  static constexpr u8 AT_RISK = 8;           // pushAtRiskStaticAnchor(tag, at_risk_klass_id)

  jlong tag;
  jlong own_class_tag;
  u32 at_risk_klass_id;
  u8 actions;
  u8 durable_root_kind;
};
static_assert(sizeof(AnchorObservation) <= 24, "AnchorObservation payload must stay <= 24 bytes");

// Ownership token of one scope: valid only while its id is the buffer's current lease and its
// epoch is unchanged. Default-constructed (id 0) is never valid.
struct AnchorObservationLease {
  u64 epoch = 0;
  u64 id = 0;
};

// Fixed-capacity, tracker-owned journal. All metadata is read and written under _lock (a full
// barrier, so arm64 publication between the callback and caller threads is ordered); the lock is
// never held across JVMTI, frontier or index work. The records array is written only by the single
// serialized heap callback between begin and flush, and read by the caller after the traversal
// returned, so it needs no lock of its own.
class AnchorObservationBuffer {
public:
  static constexpr u32 CAPACITY = 16384;

  AnchorObservationBuffer() = default;
  AnchorObservationBuffer(const AnchorObservationBuffer &) = delete;
  AnchorObservationBuffer &operator=(const AnchorObservationBuffer &) = delete;

  // Takes the sole caller lease; an invalid token (id 0) if a scope already holds it.
  AnchorObservationLease tryLease() {
    ExclusiveLockGuard guard(&_lock);
    if (_lease_id != 0) {
      return AnchorObservationLease{};
    }
    _lease_id = ++_next_lease_id;
    return AnchorObservationLease{_epoch, _lease_id};
  }

  // Releases only the lease the token names; a stale or non-owning token changes nothing.
  void releaseLease(const AnchorObservationLease &lease) {
    ExclusiveLockGuard guard(&_lock);
    if (owns(lease)) {
      _lease_id = 0;
    }
  }

  // Checks room for one record without publishing it; at most one reservation is outstanding.
  // A non-owning token, a prior overflow or a nested reservation fails without changing state;
  // a full journal also latches the overflow flag.
  bool reserve(const AnchorObservationLease &lease) {
    ExclusiveLockGuard guard(&_lock);
    if (!owns(lease) || _overflow || _reserved) {
      return false;
    }
    if (_count >= CAPACITY) {
      _overflow = true;
      return false;
    }
    _reserved = true;
    return true;
  }

  void commit(const AnchorObservationLease &lease, const AnchorObservation &record) {
    ExclusiveLockGuard guard(&_lock);
    if (!owns(lease) || !_reserved) {
      return;
    }
    _records[_count] = record;
    _count++;
    _reserved = false;
  }

  void cancel(const AnchorObservationLease &lease) {
    ExclusiveLockGuard guard(&_lock);
    if (owns(lease)) {
      _reserved = false;
    }
  }

  // Latches the overflow outcome; static_attachment also requests one static-scan retry.
  // A non-owning token is ignored.
  void markOverflow(const AnchorObservationLease &lease, bool static_attachment) {
    ExclusiveLockGuard guard(&_lock);
    if (!owns(lease)) {
      return;
    }
    _overflow = true;
    _static_retry = _static_retry || static_attachment;
  }

  // Caller-side publication barrier after a synchronous traversal returned. A non-owning token
  // has no journal, so it reports overflow and the caller aborts rather than losing observations.
  bool observeOverflow(const AnchorObservationLease &lease) {
    ExclusiveLockGuard guard(&_lock);
    return !owns(lease) || _overflow;
  }

  // Reads the accepted prefix metadata; false unless the token still owns the journal.
  bool snapshot(const AnchorObservationLease &lease, u32 *count, bool *static_retry) {
    ExclusiveLockGuard guard(&_lock);
    if (!owns(lease)) {
      return false;
    }
    *count = _count;
    *static_retry = _static_retry;
    return true;
  }

  // Clears the replayed prefix; a no-op for a stale or non-owning token.
  void clearPrefix(const AnchorObservationLease &lease) {
    ExclusiveLockGuard guard(&_lock);
    if (!owns(lease)) {
      return;
    }
    // A reservation is RAII-cancelled at callback return, so none can be outstanding here; a
    // commit after this clear would be silently dropped by the !_reserved check. Keeping the
    // assignment is the defensive fallback if that discipline is ever broken in a release build.
    assert(_reserved == false);
    _count = 0;
    _static_retry = false;
    _overflow = false;
    _reserved = false;
  }

  // Lifecycle disposal; callers guarantee no scope is mid-traversal (engine serialization or a
  // joined thread). Invalidates every outstanding lease token.
  void reset() {
    ExclusiveLockGuard guard(&_lock);
    _count = 0;
    _static_retry = false;
    _overflow = false;
    _reserved = false;
    _lease_id = 0;
    _epoch++;
  }

  u32 count() {
    ExclusiveLockGuard guard(&_lock);
    return _count;
  }

  u64 epoch() {
    ExclusiveLockGuard guard(&_lock);
    return _epoch;
  }

  const AnchorObservation *records() const { return _records; }

private:
  // Caller holds _lock. A token owns the journal only for its own lease within its own epoch.
  bool owns(const AnchorObservationLease &lease) const {
    return lease.id != 0 && lease.id == _lease_id && lease.epoch == _epoch;
  }

  SpinLock _lock;
  u32 _count = 0;
  u64 _epoch = 0;
  bool _static_retry = false;
  bool _overflow = false;
  bool _reserved = false;
  u64 _lease_id = 0;      // 0 = no lease held
  u64 _next_lease_id = 0; // never reused, so a stale token cannot match a newer lease
  AnchorObservation _records[CAPACITY];
};
static_assert(sizeof(AnchorObservation) * AnchorObservationBuffer::CAPACITY <= 393216,
              "journal storage must stay <= 384 KiB");

// RAII token for one outstanding reservation: commit() publishes, destruction without commit
// abandons it.
class AnchorObservationReservation {
public:
  AnchorObservationReservation(AnchorObservationBuffer &buffer, const AnchorObservationLease &lease)
      : _buffer(buffer), _lease(lease), _held(buffer.reserve(lease)) {}
  ~AnchorObservationReservation() {
    if (_held) {
      _buffer.cancel(_lease);
    }
  }
  AnchorObservationReservation(const AnchorObservationReservation &) = delete;
  AnchorObservationReservation &operator=(const AnchorObservationReservation &) = delete;

  bool held() const { return _held; }

  void commit(const AnchorObservation &record) {
    if (_held) {
      _buffer.commit(_lease, record);
      _held = false;
    }
  }

private:
  AnchorObservationBuffer &_buffer;
  AnchorObservationLease _lease;
  bool _held;
};

#endif // _REFERENCECHAINOBSERVATION_H
