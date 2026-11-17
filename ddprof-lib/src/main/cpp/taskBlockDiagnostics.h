/* Copyright 2026, Datadog, Inc. */
#ifndef _TASK_BLOCK_DIAGNOSTICS_H
#define _TASK_BLOCK_DIAGNOSTICS_H

#include "arch.h"
#if defined(DEBUG) || defined(UNIT_TEST)
#include <array>
#include <atomic>
#include <cstddef>
#include <limits>

class ThreadFilter;

#define DD_TASK_BLOCK_STAGE_TABLE(X) \
  X(ACTIVITY_ADMITTED) \
  X(ACTIVITY_REUSED) \
  X(ACTIVITY_CLOSED_INITIAL) \
  X(ACTIVITY_CLOSED_DURING_CAS) \
  X(ACTIVITY_CAS_BUDGET_EXHAUSTED) \
  X(ENTER_UNKNOWN_STATE) \
  X(ENTER_NO_IDENTITY_SLOT) \
  X(ENTER_NO_BLOCK_SLOT) \
  X(ENTER_INSIDE_CONTEXT_WINDOW) \
  X(ENTER_OWNER_ALREADY_HELD) \
  X(ENTER_CONTEXT_CHANGED_AFTER_OWNER_CAS) \
  X(ENTER_GENERATION_SATURATED) \
  X(ENTER_TOKEN_PUBLISHED) \
  X(TLS_ARMED) \
  X(EXIT_CALLED) \
  X(EXIT_ZERO_TOKEN) \
  X(EXIT_TLS_TOKEN_MISMATCH) \
  X(EXIT_TLS_EXTRACTED) \
  X(EXIT_VALIDATION_BEGIN) \
  X(OWNER_SLOT_UNAVAILABLE) \
  X(OWNER_SLOT_MISMATCH) \
  X(EXIT_CACHED_SLOT_FALLBACK) \
  X(EXIT_NO_IDENTITY_SLOT) \
  X(EXIT_NO_BLOCK_SLOT) \
  X(EXIT_ZERO_GENERATION) \
  X(EXIT_STATE_UNKNOWN) \
  X(EXIT_OWNER_NONE) \
  X(EXIT_GENERATION_MISMATCH) \
  X(EXIT_MATCHED_AND_CLEARED) \
  X(EXIT_ACTIVITY_REJECTED) \
  X(EXIT_RECORDING_DISABLED) \
  X(EXIT_VALIDATION_REJECTED) \
  X(EXIT_CONTEXT_WINDOW_INELIGIBLE) \
  X(EXIT_ELIGIBLE) \
  X(INVALIDATE_RESET) \
  X(INVALIDATE_REUSE) \
  X(INVALIDATE_ALL) \
  X(INVALIDATE_CONTEXT) \
  X(INVALIDATE_RETIRE) \
  X(REJECT_TRACE_CONTEXT) \
  X(REJECT_DURATION_NOT_POSITIVE) \
  X(REJECT_DURATION_BELOW_MINIMUM) \
  X(BASIC_ELIGIBLE) \
  X(RECORD_REQUEST) \
  X(REJECT_STRIPE_BUSY) \
  X(REJECT_STACK_DEPTH_NONPOSITIVE) \
  X(REJECT_CALLTRACE_BUFFER_MISSING) \
  X(REJECT_STACK_CAPTURE_EMPTY_OR_ERROR) \
  X(REJECT_CALLTRACE_STORAGE_ZERO) \
  X(STACK_READY) \
  X(STACK_OMITTED_INTENTIONALLY) \
  X(REJECT_RECORDER_SHARED_LOCK) \
  X(REJECT_NO_RECORDING) \
  X(REJECT_EVENT_THREAD_ADMISSION) \
  X(BUFFER_SERIALIZATION_BEGIN) \
  X(BUFFER_ACCEPTED) \
  X(TERMINAL_BUFFER_ACCEPTED) \
  X(TERMINAL_STACK_CAPTURE_FAILED) \
  X(TERMINAL_RECORD_FAILED)

enum class TaskBlockStage : u64 {
#define TASK_BLOCK_STAGE_ENUM(name) name,
  DD_TASK_BLOCK_STAGE_TABLE(TASK_BLOCK_STAGE_ENUM)
#undef TASK_BLOCK_STAGE_ENUM
  COUNT
};

struct TaskBlockDiagnosticRecord {
  enum Field : size_t {
    TIMESTAMP, ACTOR_TID, STAGE, TID, LIFECYCLE, TOKEN, ORIGIN_EPOCH,
    CURRENT_EPOCH, SLOT_EPOCH, START, END, BLOCKER, OWNER, STATE,
    CURRENT_SLOT, OBSERVED_GENERATION, OBSERVED_OWNER, OBSERVED_STATE,
    OBSERVED_LIFECYCLE, VALID, OPERATION, DETAIL, WIDTH
  };
  enum Valid : u64 {
    HAS_IDENTITY = 1, HAS_ORIGIN = 2, HAS_INTERVAL = 4, HAS_SLOT = 8,
    HAS_OBSERVED_STATE = 16, HAS_OBSERVED_OWNER = 32, HAS_OBSERVED_GENERATION = 64
  };
  std::array<u64, WIDTH> words{};
};

class TaskBlockDiagnostics {
 public:
  static constexpr u64 CAPACITY = 4096;
  static constexpr u64 MAX_TICKET = (std::numeric_limits<u64>::max() >> 1) - 1;
  static constexpr size_t STAGES = static_cast<size_t>(TaskBlockStage::COUNT);
#ifdef UNIT_TEST
  enum class ReservationStage { BEFORE_CAS, AFTER_RESERVATION };
  using ReservationHook = void (*)(TaskBlockDiagnostics&, ReservationStage, u64);
#endif
 private:
  struct Cell {
    std::atomic<u64> publication{0};
    std::atomic<u64> words[TaskBlockDiagnosticRecord::WIDTH]{};
  };
  static_assert(sizeof(Cell) <= 192, "diagnostic cells must stay bounded");
  std::array<Cell, CAPACITY> _cells{};
  std::atomic<u64> _next{1};
  std::array<std::atomic<u64>, STAGES> _totals{};
  std::atomic<u64> _reservation_losses{0};
  std::atomic<u64> _cell_losses{0};
#ifdef UNIT_TEST
  ReservationHook _reservation_hook = nullptr;
#endif
 public:
  static TaskBlockDiagnostics& instance();
  static const char* stageName(size_t stage);
  u64 append(TaskBlockStage stage, const TaskBlockDiagnosticRecord& record);
  bool read(u64 ticket, TaskBlockDiagnosticRecord& record) const;
  u64 cursor() const { return _next.load(std::memory_order_acquire) - 1; }
  static u64 oldestRetained(u64 high) { return high >= CAPACITY ? high - CAPACITY + 1 : 1; }
  bool exhausted() const { return cursor() == MAX_TICKET; }
  u64 stageTotal(TaskBlockStage stage) const { return _totals[static_cast<size_t>(stage)].load(std::memory_order_acquire); }
  u64 reservationLosses() const { return _reservation_losses.load(std::memory_order_acquire); }
  u64 cellLosses() const { return _cell_losses.load(std::memory_order_acquire); }
  static void observe(TaskBlockStage stage, const TaskBlockDiagnosticRecord* identity = nullptr, u64 detail = 0);
  static TaskBlockDiagnosticRecord identity(ThreadFilter* registry, int slot_id, u64 token = 0);
  static void reject(TaskBlockStage stage, const TaskBlockDiagnosticRecord* identity,
                     u64 detail, TaskBlockStage* rejection) {
    if (rejection != nullptr) *rejection = stage;
    observe(stage, identity, detail);
  }
#ifdef UNIT_TEST
  void setReservationHookForTest(ReservationHook hook) { _reservation_hook = hook; }
  void setPublicationForTest(u64 ticket, u64 value) { _cells[(ticket - 1) & (CAPACITY - 1)].publication.store(value, std::memory_order_release); }
  void setNextForTest(u64 next) { _next.store(next, std::memory_order_release); }
#endif
};
static_assert(std::atomic<u64>::is_always_lock_free, "diagnostics must be signal safe");
// Diagnostic parameters and argument expressions do not exist in release builds.
#define TASK_BLOCK_DIAGNOSTIC_ONLY(...) __VA_ARGS__
#define TASK_BLOCK_DIAGNOSTIC(stage, identity, detail) \
  TaskBlockDiagnostics::observe(TaskBlockStage::stage, identity, detail)
#define TASK_BLOCK_REJECTION(stage, identity, detail, rejection) \
  TaskBlockDiagnostics::reject(TaskBlockStage::stage, identity, detail, rejection)
#else
#define TASK_BLOCK_DIAGNOSTIC_ONLY(...)
#define TASK_BLOCK_REJECTION(stage, identity, detail, rejection) do {} while (0)
#define TASK_BLOCK_DIAGNOSTIC(stage, identity, detail) do {} while (0)
#endif

#endif
