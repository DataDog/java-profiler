/* Copyright 2026, Datadog, Inc. */
#include "taskBlockDiagnostics.h"
#if defined(DEBUG) || defined(UNIT_TEST)
#include "profiler.h"
#include "os.h"
#include "tsc.h"

TaskBlockDiagnostics& TaskBlockDiagnostics::instance() {
  return Profiler::instance()->taskBlockDiagnostics();
}

const char* TaskBlockDiagnostics::stageName(size_t stage) {
  static constexpr const char* names[] = {
#define TASK_BLOCK_STAGE_NAME(name) #name,
    DD_TASK_BLOCK_STAGE_TABLE(TASK_BLOCK_STAGE_NAME)
#undef TASK_BLOCK_STAGE_NAME
  };
  return stage < STAGES ? names[stage] : nullptr;
}

u64 TaskBlockDiagnostics::append(TaskBlockStage stage, const TaskBlockDiagnosticRecord& record) {
  // Totals and losses are observations only; no payload is published through them.
  _totals[static_cast<size_t>(stage)].fetch_add(1, std::memory_order_relaxed);
  u64 ticket = _next.load(std::memory_order_acquire);
  bool reserved = false;
  for (int attempt = 0; attempt < 8; ++attempt) {
    if (ticket > MAX_TICKET) return 0;
#ifdef UNIT_TEST
    if (_reservation_hook != nullptr) _reservation_hook(*this, ReservationStage::BEFORE_CAS, ticket);
#endif
    if (_next.compare_exchange_weak(ticket, ticket + 1, std::memory_order_acq_rel,
                                    std::memory_order_acquire)) {
      reserved = true;
      break;
    }
  }
  if (!reserved) {
    _reservation_losses.fetch_add(1, std::memory_order_relaxed);
    return 0;
  }
#ifdef UNIT_TEST
  if (_reservation_hook != nullptr) _reservation_hook(*this, ReservationStage::AFTER_RESERVATION, ticket);
#endif
  Cell& cell = _cells[(ticket - 1) & (CAPACITY - 1)];
  u64 old = cell.publication.load(std::memory_order_acquire);
  if ((old & 1) || (old >> 1) >= ticket ||
      !cell.publication.compare_exchange_strong(old, (ticket << 1) | 1,
                                                std::memory_order_acq_rel,
                                                std::memory_order_acquire)) {
    _cell_losses.fetch_add(1, std::memory_order_relaxed);
    return 0;
  }
  // No callbacks or fallible reads occur while this single-writer claim is held.
  // Atomic payload also prevents C++ data races with readers of overwritten cells.
  for (size_t i = 0; i < record.words.size(); ++i) {
    cell.words[i].store(record.words[i], std::memory_order_release);
  }
  cell.publication.store(ticket << 1, std::memory_order_release);
  return ticket;
}

bool TaskBlockDiagnostics::read(u64 ticket, TaskBlockDiagnosticRecord& record) const {
  if (ticket == 0 || ticket > MAX_TICKET) return false;
  const Cell& cell = _cells[(ticket - 1) & (CAPACITY - 1)];
  if (cell.publication.load(std::memory_order_acquire) != (ticket << 1)) return false;
  for (size_t i = 0; i < record.words.size(); ++i) {
    record.words[i] = cell.words[i].load(std::memory_order_acquire);
  }
  return cell.publication.load(std::memory_order_acquire) == (ticket << 1);
}

void TaskBlockDiagnostics::observe(TaskBlockStage stage,
                                    const TaskBlockDiagnosticRecord* identity, u64 detail) {
  ErrnoPreserver errno_preserver;
  TaskBlockDiagnosticRecord record = identity == nullptr ? TaskBlockDiagnosticRecord{} : *identity;
  record.words[TaskBlockDiagnosticRecord::TIMESTAMP] = TSC::ticks();
  record.words[TaskBlockDiagnosticRecord::ACTOR_TID] = OS::threadId();
  record.words[TaskBlockDiagnosticRecord::STAGE] = static_cast<u64>(stage);
  record.words[TaskBlockDiagnosticRecord::DETAIL] = detail;
  instance().append(stage, record);
}

TaskBlockDiagnosticRecord TaskBlockDiagnostics::identity(ThreadFilter* registry, int slot_id, u64 token) {
  TaskBlockDiagnosticRecord record{};
  record.words[TaskBlockDiagnosticRecord::CURRENT_SLOT] = static_cast<u64>(slot_id);
  record.words[TaskBlockDiagnosticRecord::TOKEN] = token;
  record.words[TaskBlockDiagnosticRecord::CURRENT_EPOCH] = registry->recordingEpoch();
  auto* identity = registry->slotForId(slot_id);
  if (identity != nullptr) {
    record.words[TaskBlockDiagnosticRecord::TID] = identity->nativeTid();
    record.words[TaskBlockDiagnosticRecord::LIFECYCLE] = identity->lifecycleGeneration();
    record.words[TaskBlockDiagnosticRecord::SLOT_EPOCH] = identity->recordingEpoch();
    record.words[TaskBlockDiagnosticRecord::OBSERVED_LIFECYCLE] = identity->lifecycleGeneration();
    record.words[TaskBlockDiagnosticRecord::VALID] = TaskBlockDiagnosticRecord::HAS_IDENTITY | TaskBlockDiagnosticRecord::HAS_SLOT;
  }
  return record;
}
#endif
