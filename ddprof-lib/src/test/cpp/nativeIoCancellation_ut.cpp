/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#if defined(__linux__)

#include "nativeSocketInterposer.h"
#include "profiler.h"
#include "threadLocalData.inline.h"

#include <atomic>
#include <poll.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

extern void run_with_cleanup(void* (*)(void*), void*, void (*)(void*), void*);

namespace {

std::atomic<bool> entered{false};
std::atomic<bool> owned{false};
std::atomic<bool> cleaned{false};
std::atomic<bool> released{false};
std::atomic<bool> disabled_preserved{false};
std::atomic<bool> returned_normally{false};
int operation;
int descriptors[2];
bool pending_cancel;
bool disabled_cancel;

void observeBlockingCall() {
  ProfiledThread* current = ProfiledThread::current();
  auto* slot = Profiler::instance()->blockTracker()->slotForId(current->filterSlotId());
  owned.store(slot != nullptr && slot->activeBlockOwner() == BlockRunOwner::NATIVE,
              std::memory_order_release);
  entered.store(true, std::memory_order_release);
}

ssize_t blockingRead(int fd, void* data, size_t size) {
  observeBlockingCall();
  return ::read(fd, data, size);
}

ssize_t blockingRecv(int fd, void* data, size_t size, int flags) {
  observeBlockingCall();
  return ::recv(fd, data, size, flags);
}

int blockingPoll(struct pollfd* fds, nfds_t count, int timeout) {
  observeBlockingCall();
  return ::poll(fds, count, timeout);
}

int blockingAccept(int fd, struct sockaddr* address, socklen_t* size) {
  observeBlockingCall();
  return ::accept(fd, address, size);
}

Profiler::TaskBlockRecordResult recordCompletedBlock(int, jthread, int, TaskBlockEvent*) {
  return Profiler::TaskBlockRecordResult::RECORDED;
}

void cleanupThread(void*) {
  ProfiledThread* current = ProfiledThread::current();
  auto* slot = Profiler::instance()->blockTracker()->slotForId(current->filterSlotId());
  cleaned.store(slot != nullptr && slot->activeBlockState() == OSThreadState::UNKNOWN,
                std::memory_order_release);
  Profiler::instance()->threadFilter()->unregisterThreadByTid(current->tid());
  ProfiledThread::release();
  released.store(ProfiledThread::current() == nullptr, std::memory_order_release);
}

void* callHook(void*) {
  if (pending_cancel) pthread_cancel(pthread_self());
  char byte;
  struct pollfd fds = {descriptors[0], POLLIN, 0};
  switch (operation) {
    case 0: NativeSocketInterposer::read_hook(descriptors[0], &byte, 1); break;
    case 1: NativeSocketInterposer::recv_hook(descriptors[0], &byte, 1, 0); break;
    case 2: NativeSocketInterposer::poll_hook(&fds, 1, -1); break;
    case 3: NativeSocketInterposer::accept_hook(descriptors[0], nullptr, nullptr); break;
  }
  return nullptr;
}

void* cancellationThread(void*) {
  ProfiledThread::initCurrentThread();
  ProfiledThread* current = ProfiledThread::current();
  current->setJavaThread(true);
  current->setJvmInternalThread(false);
  current->clearContextForTest();
  // Match the production thread wrapper without an automatic destructor across the hook.
  if (disabled_cancel) pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
  run_with_cleanup(callHook, nullptr, cleanupThread, nullptr);
  if (disabled_cancel) {
    int previous;
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &previous);
    disabled_preserved.store(previous == PTHREAD_CANCEL_DISABLE, std::memory_order_release);
    returned_normally.store(true, std::memory_order_release);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    pthread_testcancel();
  }
  return nullptr;
}

} // namespace

class NativeIoCancellationTest : public ::testing::TestWithParam<int> {};

TEST_P(NativeIoCancellationTest, DeferredCancellationJoinsAndClearsNativeOwner) {
  ASSERT_EXIT({
    alarm(10);
    operation = GetParam();
    pending_cancel = false;
    disabled_cancel = false;
    auto* profiler = Profiler::instance();
    profiler->threadFilter()->init("", true);
    profiler->setTaskBlockEnabledForTest(true);
    Profiler::setTaskBlockRecordOverrideForTest(recordCompletedBlock);
    NativeSocketInterposer::instance()->setActiveForTest(true);
    NativeSocketInterposer::setOriginalFunction(NativeSocketInterposer::HOOK_READ,
                                                reinterpret_cast<void*>(blockingRead));
    NativeSocketInterposer::setOriginalFunction(NativeSocketInterposer::HOOK_RECV,
                                                reinterpret_cast<void*>(blockingRecv));
    NativeSocketInterposer::setOriginalFunction(NativeSocketInterposer::HOOK_POLL,
                                                reinterpret_cast<void*>(blockingPoll));
    NativeSocketInterposer::setOriginalFunction(NativeSocketInterposer::HOOK_ACCEPT,
                                                reinterpret_cast<void*>(blockingAccept));
    if (operation == 3) {
      descriptors[0] = socket(AF_INET, SOCK_STREAM, 0);
      ASSERT_GE(descriptors[0], 0);
      struct sockaddr address = {};
      address.sa_family = AF_INET;
      ASSERT_EQ(0, bind(descriptors[0], &address, sizeof(address)));
      ASSERT_EQ(0, listen(descriptors[0], 1));
      descriptors[1] = -1;
    } else {
      ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, descriptors));
    }
    // Repeat with a cancellation already pending when admission begins.
    for (int iteration = 0; iteration < 2; iteration++) {
      entered = false;
      owned = false;
      cleaned = false;
      released = false;
      pending_cancel = iteration != 0;
      pthread_t thread;
      ASSERT_EQ(0, pthread_create(&thread, nullptr, cancellationThread, nullptr));
      if (!pending_cancel) {
        while (!entered.load(std::memory_order_acquire)) usleep(100);
        ASSERT_TRUE(owned.load(std::memory_order_acquire));
        ASSERT_EQ(0, pthread_cancel(thread));
      }
      void* result = nullptr;
      ASSERT_EQ(0, pthread_join(thread, &result));
      EXPECT_EQ(PTHREAD_CANCELED, result);
      EXPECT_TRUE(cleaned.load(std::memory_order_acquire));
      EXPECT_TRUE(released.load(std::memory_order_acquire));
    }
    close(descriptors[0]);
    if (descriptors[1] >= 0) close(descriptors[1]);
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

TEST(NativeIoCancellationStateTest, DisabledCancellationSurvivesTheCallAndRetainsPendingRequest) {
  ASSERT_EXIT({
    alarm(10);
    operation = 0;
    pending_cancel = disabled_cancel = true;
    auto* profiler = Profiler::instance();
    profiler->threadFilter()->init("", true);
    profiler->setTaskBlockEnabledForTest(true);
    Profiler::setTaskBlockRecordOverrideForTest(recordCompletedBlock);
    NativeSocketInterposer::instance()->setActiveForTest(true);
    NativeSocketInterposer::setOriginalFunction(NativeSocketInterposer::HOOK_READ,
                                                reinterpret_cast<void*>(blockingRead));
    ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, descriptors));
    pthread_t thread;
    ASSERT_EQ(0, pthread_create(&thread, nullptr, cancellationThread, nullptr));
    while (!entered.load(std::memory_order_acquire)) usleep(100);
    ASSERT_TRUE(owned.load(std::memory_order_acquire));
    char byte = 1;
    ASSERT_EQ(1, write(descriptors[1], &byte, 1));
    void* result = nullptr;
    ASSERT_EQ(0, pthread_join(thread, &result));
    EXPECT_EQ(PTHREAD_CANCELED, result);
    EXPECT_TRUE(returned_normally.load(std::memory_order_acquire));
    EXPECT_TRUE(disabled_preserved.load(std::memory_order_acquire));
    EXPECT_TRUE(cleaned.load(std::memory_order_acquire));
    EXPECT_TRUE(released.load(std::memory_order_acquire));
    close(descriptors[0]);
    close(descriptors[1]);
    _exit(HasFailure() ? 1 : 0);
  }, ::testing::ExitedWithCode(0), "");
}

INSTANTIATE_TEST_SUITE_P(LibcCancellationPoints, NativeIoCancellationTest,
                        ::testing::Values(0, 1, 2, 3));

#endif // __linux__
