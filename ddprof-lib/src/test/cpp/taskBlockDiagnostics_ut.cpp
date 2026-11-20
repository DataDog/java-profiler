/* Copyright 2026, Datadog, Inc. */
#include <gtest/gtest.h>
#include "taskBlockDiagnostics.h"
#include <cerrno>
#include <csignal>
#include <memory>
#include <thread>
#include <vector>

TEST(TaskBlockDiagnostics, EmptyAndEveryIdentityFieldRoundTrip) {
  auto diagnostics = std::make_unique<TaskBlockDiagnostics>();
  EXPECT_EQ(0, diagnostics->cursor());
  TaskBlockDiagnosticRecord record{};
  for (size_t i = 0; i < record.words.size(); ++i) record.words[i] = i + 100;
  errno = EDOM;
  const u64 ticket = diagnostics->append(TaskBlockStage::EXIT_GENERATION_MISMATCH, record);
  EXPECT_EQ(EDOM, errno);
  ASSERT_EQ(1, ticket);
  TaskBlockDiagnosticRecord copy{};
  ASSERT_TRUE(diagnostics->read(ticket, copy));
  EXPECT_EQ(record.words, copy.words);
  EXPECT_EQ(1, diagnostics->stageTotal(TaskBlockStage::EXIT_GENERATION_MISMATCH));
  EXPECT_FALSE(diagnostics->read(0, copy));
  EXPECT_FALSE(diagnostics->read(2, copy));
}

TEST(TaskBlockDiagnostics, ExactCapacityAndFirstOverwriteAreVisible) {
  auto diagnostics = std::make_unique<TaskBlockDiagnostics>();
  TaskBlockDiagnosticRecord record{};
  for (u64 i = 1; i <= TaskBlockDiagnostics::CAPACITY; ++i) {
    record.words[TaskBlockDiagnosticRecord::TOKEN] = i;
    ASSERT_EQ(i, diagnostics->append(TaskBlockStage::ENTER_TOKEN_PUBLISHED, record));
  }
  TaskBlockDiagnosticRecord copy{};
  EXPECT_TRUE(diagnostics->read(1, copy));
  EXPECT_EQ(1, copy.words[TaskBlockDiagnosticRecord::TOKEN]);
  EXPECT_EQ(TaskBlockDiagnostics::CAPACITY + 1,
            diagnostics->append(TaskBlockStage::ENTER_TOKEN_PUBLISHED, record));
  EXPECT_FALSE(diagnostics->read(1, copy));
  EXPECT_TRUE(diagnostics->read(2, copy));
  EXPECT_EQ(2, TaskBlockDiagnostics::oldestRetained(diagnostics->cursor()));
}

TEST(TaskBlockDiagnostics, BusySupersededAndSequenceExhaustionAreReported) {
  auto diagnostics = std::make_unique<TaskBlockDiagnostics>();
  diagnostics->setPublicationForTest(1, 3);
  TaskBlockDiagnosticRecord record{};
  EXPECT_EQ(0, diagnostics->append(TaskBlockStage::RECORD_REQUEST, record));
  EXPECT_EQ(1, diagnostics->cellLosses());
  diagnostics->setPublicationForTest(2, 200);
  EXPECT_EQ(0, diagnostics->append(TaskBlockStage::RECORD_REQUEST, record));
  EXPECT_EQ(2, diagnostics->cellLosses());
  diagnostics->setNextForTest(TaskBlockDiagnostics::MAX_TICKET);
  EXPECT_EQ(TaskBlockDiagnostics::MAX_TICKET,
            diagnostics->append(TaskBlockStage::RECORD_REQUEST, record));
  EXPECT_EQ(0, diagnostics->append(TaskBlockStage::RECORD_REQUEST, record));
  EXPECT_TRUE(diagnostics->exhausted());
  EXPECT_EQ(4, diagnostics->stageTotal(TaskBlockStage::RECORD_REQUEST));
}

TEST(TaskBlockDiagnostics, ConcurrentWritersAndReaderNeverAcceptTornIdentities) {
  auto diagnostics = std::make_unique<TaskBlockDiagnostics>();
  std::atomic<int> remaining{4};
  std::vector<std::thread> writers;
  for (u64 tid = 1; tid <= 4; ++tid) {
    writers.emplace_back([&, tid] {
      TaskBlockDiagnosticRecord record{};
      for (u64 token = 1; token <= 10000; ++token) {
        record.words.fill((tid << 32) | token);
        diagnostics->append(TaskBlockStage::ENTER_TOKEN_PUBLISHED, record);
      }
      remaining.fetch_sub(1, std::memory_order_release);
    });
  }
  u64 accepted = 0;
  do {
    const u64 high = diagnostics->cursor();
    const u64 low = high >= TaskBlockDiagnostics::CAPACITY
                        ? high - TaskBlockDiagnostics::CAPACITY + 1 : 1;
    for (u64 ticket = low; ticket <= high; ++ticket) {
      TaskBlockDiagnosticRecord record{};
      if (!diagnostics->read(ticket, record)) continue;
      ++accepted;
      for (u64 value : record.words) EXPECT_EQ(record.words[0], value);
    }
  } while (remaining.load(std::memory_order_acquire) != 0);
  for (auto& writer : writers) writer.join();
  EXPECT_GT(accepted, 0);
  EXPECT_EQ(40000, diagnostics->stageTotal(TaskBlockStage::ENTER_TOKEN_PUBLISHED));
  EXPECT_LE(diagnostics->cursor(), 40000);
}

TEST(TaskBlockDiagnostics, StageNamesAndStorageBudgetMatchTheProtocol) {
  EXPECT_LE(sizeof(TaskBlockDiagnostics), 768 * 1024 + 1024);
  EXPECT_EQ(nullptr, TaskBlockDiagnostics::stageName(TaskBlockDiagnostics::STAGES));
  for (size_t stage = 0; stage < TaskBlockDiagnostics::STAGES; ++stage) {
    ASSERT_NE(nullptr, TaskBlockDiagnostics::stageName(stage));
    EXPECT_NE('\0', TaskBlockDiagnostics::stageName(stage)[0]);
    for (size_t other = 0; other < stage; ++other) {
      EXPECT_STRNE(TaskBlockDiagnostics::stageName(stage), TaskBlockDiagnostics::stageName(other));
    }
  }
}

namespace {
bool diagnostic_reentry = false;
bool diagnostic_delay = false;
struct DiagnosticReentryGuard {
  DiagnosticReentryGuard() { diagnostic_reentry = true; }
  ~DiagnosticReentryGuard() { diagnostic_reentry = false; }
  DiagnosticReentryGuard(const DiagnosticReentryGuard&) = delete;
  DiagnosticReentryGuard& operator=(const DiagnosticReentryGuard&) = delete;
};
void contendDiagnosticReservation(TaskBlockDiagnostics& diagnostics,
    TaskBlockDiagnostics::ReservationStage stage, u64 ticket) {
  if (diagnostic_reentry) return;
  DiagnosticReentryGuard guard;
  TaskBlockDiagnosticRecord record{};
  if (!diagnostic_delay && stage == TaskBlockDiagnostics::ReservationStage::BEFORE_CAS) {
    diagnostics.append(TaskBlockStage::ENTER_TOKEN_PUBLISHED, record);
  } else if (diagnostic_delay && stage == TaskBlockDiagnostics::ReservationStage::AFTER_RESERVATION && ticket == 1) {
    for (u64 i = 0; i < TaskBlockDiagnostics::CAPACITY; ++i) {
      diagnostics.append(TaskBlockStage::ENTER_TOKEN_PUBLISHED, record);
    }
  }
}
}

TEST(TaskBlockDiagnostics, RealNestedReservationsExhaustBudgetWithoutWaiting) {
  auto diagnostics = std::make_unique<TaskBlockDiagnostics>();
  diagnostic_delay = false;
  diagnostics->setReservationHookForTest(contendDiagnosticReservation);
  TaskBlockDiagnosticRecord record{};
  EXPECT_EQ(0, diagnostics->append(TaskBlockStage::RECORD_REQUEST, record));
  EXPECT_EQ(8, diagnostics->cursor());
  EXPECT_EQ(1, diagnostics->reservationLosses());
  EXPECT_EQ(8, diagnostics->stageTotal(TaskBlockStage::ENTER_TOKEN_PUBLISHED));
  EXPECT_EQ(1, diagnostics->stageTotal(TaskBlockStage::RECORD_REQUEST));
}

TEST(TaskBlockDiagnostics, SupersededRealReservationCannotOverwriteNewerCommittedTicket) {
  auto diagnostics = std::make_unique<TaskBlockDiagnostics>();
  diagnostic_delay = true;
  diagnostics->setReservationHookForTest(contendDiagnosticReservation);
  TaskBlockDiagnosticRecord record{};
  EXPECT_EQ(0, diagnostics->append(TaskBlockStage::RECORD_REQUEST, record));
  EXPECT_EQ(TaskBlockDiagnostics::CAPACITY + 1, diagnostics->cursor());
  EXPECT_EQ(1, diagnostics->cellLosses());
  EXPECT_FALSE(diagnostics->read(1, record));
  EXPECT_TRUE(diagnostics->read(TaskBlockDiagnostics::CAPACITY + 1, record));
  EXPECT_EQ(0, diagnostics->reservationLosses());
}

namespace {
volatile sig_atomic_t diagnostic_signal_observed = 0;
volatile sig_atomic_t diagnostic_errno_preserved = 0;
void diagnosticSignalHandler(int) {
  int saved_errno = errno;
  TaskBlockDiagnostics::observe(TaskBlockStage::INVALIDATE_CONTEXT);
  diagnostic_errno_preserved = errno == saved_errno;
  diagnostic_signal_observed = 1;
}
class DiagnosticSignalAction {
  struct sigaction previous{};
  int installed;
public:
  DiagnosticSignalAction() {
    struct sigaction action{};
    action.sa_handler = diagnosticSignalHandler;
    sigemptyset(&action.sa_mask);
    installed = sigaction(SIGUSR1, &action, &previous);
  }
  ~DiagnosticSignalAction() { if (installed == 0) sigaction(SIGUSR1, &previous, nullptr); }
  DiagnosticSignalAction(const DiagnosticSignalAction&) = delete;
  DiagnosticSignalAction& operator=(const DiagnosticSignalAction&) = delete;
  bool active() const { return installed == 0; }
};
}

TEST(TaskBlockDiagnostics, SignalWriterPublishesReceiptAndPreservesErrno) {
  DiagnosticSignalAction action;
  ASSERT_TRUE(action.active());
  diagnostic_signal_observed = 0;
  diagnostic_errno_preserved = 0;
  u64 cursor = TaskBlockDiagnostics::instance().cursor();
  errno = ERANGE;
  ASSERT_EQ(0, raise(SIGUSR1));
  ASSERT_EQ(1, diagnostic_signal_observed);
  EXPECT_EQ(1, diagnostic_errno_preserved);
  TaskBlockDiagnosticRecord record{};
  ASSERT_TRUE(TaskBlockDiagnostics::instance().read(cursor + 1, record));
  EXPECT_EQ(static_cast<u64>(TaskBlockStage::INVALIDATE_CONTEXT), record.words[TaskBlockDiagnosticRecord::STAGE]);
  EXPECT_GT(record.words[TaskBlockDiagnosticRecord::TIMESTAMP], 0);
  EXPECT_GT(record.words[TaskBlockDiagnosticRecord::ACTOR_TID], 0);
}
