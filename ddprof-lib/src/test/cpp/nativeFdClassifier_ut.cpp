/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include <gtest/gtest.h>

#if defined(__linux__)

#include "nativeFdClassifier.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

namespace {

class NativeFdClassifierExhaustionTest : public ::testing::Test {
protected:
  void SetUp() override {
    current = this;
    NativeFdClassifier::setProbeOverrideForTest(probe);
  }

  void TearDown() override {
    NativeFdClassifier::setProbeOverrideForTest(nullptr);
    current = nullptr;
  }

  static int probe(int fd, int* type, int* failure) {
    current->calls++;
    *type = current->socket_type;
    *failure = 0;
    if (current->publishing_successor != nullptr) {
      NativeFdClassifier* classifier = current->publishing_successor;
      current->publishing_successor = nullptr;
      current->successor_published = classifier->revalidateStreamSocket(fd);
      *failure = ENOTSOCK;
      return -1;
    }
    if (current->invalidating != nullptr) {
      for (uint32_t i = 0; i < current->invalidations; i++) {
        current->invalidating->clearFdType(fd);
        current->completed_invalidations++;
      }
      *failure = ENOTSOCK;
      return -1;
    }
    return 0;
  }

  int calls = 0;
  int socket_type = SOCK_STREAM;
  NativeFdClassifier* invalidating = nullptr;
  NativeFdClassifier* publishing_successor = nullptr;
  bool successor_published = false;
  uint32_t invalidations = 0;
  uint32_t completed_invalidations = 0;
  static NativeFdClassifierExhaustionTest* current;
};

NativeFdClassifierExhaustionTest* NativeFdClassifierExhaustionTest::current = nullptr;

TEST_F(NativeFdClassifierExhaustionTest,
       SameTypePublicationRejectsStaleNegativeWithoutLifecycleInvalidation) {
  for (int fd : {7, 65536 + 7}) {
    SCOPED_TRACE(fd);
    NativeFdClassifier classifier;
    calls = 0;
    ASSERT_TRUE(classifier.isStreamSocket(fd));
    ASSERT_EQ(1, calls);
    publishing_successor = &classifier;
    successor_published = false;
    // The nested successful probe returns the same type as the ready entry.
    // It must still change the publication identity before this ENOTSOCK CAS.
    EXPECT_TRUE(classifier.revalidateStreamSocket(fd));
    EXPECT_TRUE(successor_published);
    EXPECT_EQ(3, calls);
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_EQ(3, calls) << "a fresh positive successor must remain ready";
  }
}

TEST_F(NativeFdClassifierExhaustionTest,
       ConcurrentFirstClassificationPublishesOneInitializedCachePair) {
  NativeFdClassifier classifier;
  NativeFdClassifier::setProbeOverrideForTest(nullptr);
  uint64_t allocations = NativeFdClassifier::cacheAllocationCountForTest();
  int sockets[2], pipes[2];
  ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));
  struct ClosePair {
    int* fds;
    ~ClosePair() { close(fds[0]); close(fds[1]); }
  } close_sockets{sockets};
  ASSERT_EQ(0, pipe(pipes));
  ClosePair close_pipes{pipes};
  std::atomic<int> waiting{0}, failures{0};
  std::atomic<bool> start{false};
  std::thread workers[8];
  for (auto& worker : workers) {
    worker = std::thread([&]() {
      waiting.fetch_add(1, std::memory_order_acq_rel);
      while (!start.load(std::memory_order_acquire)) std::this_thread::yield();
      for (int i = 0; i < 1000; i++) {
        if (!classifier.isStreamSocket(sockets[0]) || classifier.isStreamSocket(pipes[0])) {
          failures.fetch_add(1, std::memory_order_acq_rel);
        }
      }
    });
  }
  while (waiting.load(std::memory_order_acquire) != 8) std::this_thread::yield();
  start.store(true, std::memory_order_release);
  for (auto& worker : workers) worker.join();
  EXPECT_EQ(0, failures.load(std::memory_order_acquire));
  EXPECT_EQ(allocations + 1, NativeFdClassifier::cacheAllocationCountForTest());
}

TEST_F(NativeFdClassifierExhaustionTest,
       RealLowAndHighFdReuseRepairsStableNegativesWithoutRetainingTransientErrors) {
  NativeFdClassifier::setProbeOverrideForTest(nullptr);
  struct rlimit limit;
  ASSERT_EQ(0, getrlimit(RLIMIT_NOFILE, &limit));
  ASSERT_GT(limit.rlim_cur, 65536u);
  for (int minimum : {0, 65536}) {
    SCOPED_TRACE(minimum);
    NativeFdClassifier classifier;
    int sockets[2], pipes[2];
    ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));
    struct ClosePair {
      int* fds;
      ~ClosePair() { close(fds[0]); close(fds[1]); }
    } close_sockets{sockets};
    ASSERT_EQ(0, pipe(pipes));
    ClosePair close_pipes{pipes};
    int fd = fcntl(sockets[0], F_DUPFD_CLOEXEC, minimum);
    ASSERT_GE(fd, minimum);
    struct CloseFd {
      int fd;
      ~CloseFd() { if (fd >= 0) close(fd); }
    } target{fd};
    if (minimum == 0) ASSERT_LT(fd, 65536);
    uint64_t probes = NativeFdClassifier::probeCountForTest();
    ASSERT_TRUE(classifier.isStreamSocket(fd));
    ASSERT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_EQ(probes + 1, NativeFdClassifier::probeCountForTest());
    ASSERT_EQ(fd, ::dup2(pipes[1], fd));
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_FALSE(classifier.revalidateStreamSocket(fd));
    EXPECT_EQ(ENOTSOCK, errno);
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_EQ(probes + 2, NativeFdClassifier::probeCountForTest());
    ASSERT_EQ(fd, ::dup2(sockets[0], fd));
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_TRUE(classifier.revalidateStreamSocket(fd));
    EXPECT_EQ(probes + 3, NativeFdClassifier::probeCountForTest());
    target.fd = -1;
    ASSERT_EQ(0, ::close(fd));
    classifier.clearFdType(fd);
    EXPECT_FALSE(classifier.revalidateStreamSocket(fd));
    EXPECT_EQ(EBADF, errno);
    EXPECT_EQ(probes + 4, NativeFdClassifier::probeCountForTest());
    int replacement = ::dup2(sockets[0], fd);
    target.fd = replacement;
    ASSERT_EQ(fd, replacement);
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_EQ(probes + 5, NativeFdClassifier::probeCountForTest());
  }
}

TEST_F(NativeFdClassifierExhaustionTest,
       LifecycleInvalidationBeforeAdmissionDoesNotAllocateRetiredBanks) {
  NativeFdClassifier classifier;
  uint64_t allocations = NativeFdClassifier::cacheAllocationCountForTest();
  // Invalidations must not allocate storage that this classifier can no longer
  // safely publish into, including before its first classification.
  for (uint32_t epoch = 0; epoch < (1u << 18); epoch++) {
    classifier.clearFdType(65536 + 7);
  }
  EXPECT_EQ(allocations, NativeFdClassifier::cacheAllocationCountForTest());
  for (int fd : {7, 65536 + 7}) {
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_TRUE(classifier.isStreamSocket(fd));
  }
  EXPECT_EQ(4, calls);
  EXPECT_EQ(allocations, NativeFdClassifier::cacheAllocationCountForTest());
}

TEST_F(NativeFdClassifierExhaustionTest,
       SecondBankRetirementRejectsUntouchedHitsAndRepairsNegativeObservations) {
  NativeFdClassifier classifier;
  for (uint32_t epoch = 0; epoch < (1u << 17); epoch++) {
    classifier.clearFdTypeCache();
  }
  for (int fd : {7, 65536 + 7}) {
    ASSERT_TRUE(classifier.isStreamSocket(fd));
    ASSERT_TRUE(classifier.isStreamSocket(fd));
  }
  ASSERT_EQ(2, calls) << "the second bank must still cache ready hits";
  for (uint32_t epoch = 0; epoch < (1u << 17); epoch++) {
    classifier.clearFdTypeCache();
  }
  socket_type = SOCK_DGRAM;
  for (int fd : {7, 65536 + 7}) {
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_TRUE(classifier.isDatagramSocket(fd));
  }
  EXPECT_EQ(6, calls) << "retired ready entries must never resurrect";
  int pipes[2];
  ASSERT_EQ(0, pipe(pipes));
  struct ClosePipe {
    int* fds;
    ~ClosePipe() { close(fds[0]); close(fds[1]); }
  } close_pipe{pipes};
  NativeFdClassifier::setProbeOverrideForTest(nullptr);
  EXPECT_FALSE(classifier.isStreamSocket(pipes[0]));
  EXPECT_EQ(ENOTSOCK, errno);
  NativeFdClassifier::setProbeOverrideForTest(probe);
  socket_type = SOCK_STREAM;
  EXPECT_TRUE(classifier.isStreamSocket(pipes[0]));
  EXPECT_EQ(7, calls) << "uncached ENOTSOCK must not become sticky";
}

TEST_F(NativeFdClassifierExhaustionTest,
       IncarnationExhaustionRetiresBankBeforeAnyIdentityRepeats) {
  for (int fd : {7, 65536 + 7}) {
    SCOPED_TRACE(fd);
    NativeFdClassifier classifier;
    calls = 0;
    ASSERT_TRUE(classifier.isStreamSocket(fd));
    classifier.clearFdType(fd);
    invalidating = &classifier;
    invalidations = fd < 65536 ? 1u << 28 : 1u << 24;
    completed_invalidations = 0;
    // Warm the epoch before capture; an initially zero word changing epoch is
    // not an ABA. Exercise the actual packed bound without counter injection.
    EXPECT_FALSE(classifier.isStreamSocket(fd));
    EXPECT_EQ(invalidations, completed_invalidations);
    EXPECT_EQ(2, calls);
    invalidating = nullptr;
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_TRUE(classifier.isStreamSocket(fd));
    EXPECT_EQ(3, calls) << "retirement must leave the next bank cacheable";
  }
}

} // namespace

#endif // __linux__
