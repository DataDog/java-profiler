/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#if defined(__linux__)

#include "libraries.h"
#include "libraryPatcher.h"
#include "nativeBlock.h"
#include "nativeFdClassifier.h"
#include "nativeSocketInterposer.h"
#include "nativeSocketSampler.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <dlfcn.h>
#include <fcntl.h>
#include <limits.h>
#include <initializer_list>
#include <sys/socket.h>
#include <unistd.h>

namespace {

const int kHighFd = 65536 + 73;

class ScopedQualificationFd {
public:
  explicit ScopedQualificationFd(int fd) : _fd(fd) {}
  ~ScopedQualificationFd() {
    if (_fd >= 0) ::close(_fd);
  }
  int release() {
    int fd = _fd;
    _fd = -1;
    return fd;
  }
  void reset(int fd) {
    if (_fd >= 0) ::close(_fd);
    _fd = fd;
  }
  ScopedQualificationFd(const ScopedQualificationFd&) = delete;
  ScopedQualificationFd& operator=(const ScopedQualificationFd&) = delete;

private:
  int _fd;
};

class NativeFdQualificationTest : public ::testing::Test {
protected:
  void SetUp() override {
    current = this;
    NativeFdClassifier::setProbeOverrideForTest(probe);
  }

  void TearDown() override {
    NativeFdClassifier::setProbeOverrideForTest(nullptr);
    NativeSocketSampler::instance()->clearFdCache();
    current = nullptr;
  }

  // The callback runs between the production captured-word load and its CAS.
  static int probe(int fd, int* type, int* failure) {
    NativeFdQualificationTest& state = *current;
    state.calls++;
    if (state.nested) {
      *type = state.successor_type;
      *failure = 0;
      return 0;
    }
    if (state.calls == 1) {
      for (uint32_t index = 0; index < state.epoch_clears; index++) {
        state.sampler->clearFdCache();
        state.completed_clears++;
      }
      if (state.invalidate) {
        state.classifier->clearFdType(fd);
        state.completed_invalidations++;
      }
      if (state.publish_successor) {
        state.nested = true;
        int successor_fd = state.collision_fd >= 0 ? state.collision_fd : fd;
        state.successor_published = state.successor_type == SOCK_STREAM
            ? state.classifier->isStreamSocket(successor_fd)
            : state.classifier->isDatagramSocket(successor_fd);
        state.nested = false;
      }
    }
    *type = state.probe_type;
    *failure = state.probe_failure;
    return state.probe_failure == 0 ? 0 : -1;
  }

  void resetProbe() {
    calls = 0;
    completed_clears = 0;
    completed_invalidations = 0;
    successor_published = false;
  }

  NativeFdClassifier* classifier = nullptr;
  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  int calls = 0;
  int probe_type = SOCK_STREAM;
  int probe_failure = 0;
  int successor_type = SOCK_DGRAM;
  int collision_fd = -1;
  bool nested = false;
  bool invalidate = false;
  bool publish_successor = false;
  bool successor_published = false;
  uint32_t epoch_clears = 0;
  uint32_t completed_clears = 0;
  int completed_invalidations = 0;
  static NativeFdQualificationTest* current;
};

NativeFdQualificationTest* NativeFdQualificationTest::current = nullptr;

TEST_F(NativeFdQualificationTest, EpochWrapNeighborControlsReprobeUntouchedEntries) {
  for (uint32_t clears : {(1u << 17) - 1, (1u << 17) + 1}) {
    for (int fd : {73, kHighFd}) {
      SCOPED_TRACE(clears);
      SCOPED_TRACE(fd);
      NativeFdClassifier cache;
      resetProbe();
      probe_type = SOCK_STREAM;
      ASSERT_TRUE(cache.isStreamSocket(fd));
      ASSERT_EQ(1, calls);
      uint32_t completed = 0;
      for (; completed < clears; completed++) cache.clearFdTypeCache();
      ASSERT_EQ(clears, completed);
      probe_type = SOCK_DGRAM;
      EXPECT_FALSE(cache.isStreamSocket(fd));
      EXPECT_TRUE(cache.isDatagramSocket(fd));
      EXPECT_EQ(2, calls);
    }
  }
}

TEST_F(NativeFdQualificationTest, InvalidationRejectsStreamDatagramAndStableNegativePublication) {
  const int results[] = {SOCK_STREAM, SOCK_DGRAM, -ENOTSOCK};
  for (int fd : {73, kHighFd}) {
    for (int result : results) {
      SCOPED_TRACE(fd);
      SCOPED_TRACE(result);
      NativeFdClassifier cache;
      classifier = &cache;
      cache.clearFdType(fd);
      resetProbe();
      invalidate = true;
      probe_type = result < 0 ? 0 : result;
      probe_failure = result < 0 ? -result : 0;
      EXPECT_FALSE(cache.isStreamSocket(fd));
      EXPECT_EQ(1, calls);
      EXPECT_EQ(1, completed_invalidations);
      invalidate = false;
      probe_type = SOCK_STREAM;
      probe_failure = 0;
      EXPECT_TRUE(cache.isStreamSocket(fd));
      EXPECT_TRUE(cache.isStreamSocket(fd));
      EXPECT_EQ(2, calls);
    }
  }
}

TEST_F(NativeFdQualificationTest, StaleNegativeCasCannotReplacePublishedSuccessor) {
  for (int fd : {73, kHighFd}) {
    for (int failure : {ENOTSOCK, EBADF}) {
      SCOPED_TRACE(fd);
      SCOPED_TRACE(failure);
      NativeFdClassifier cache;
      classifier = &cache;
      cache.clearFdType(fd);
      resetProbe();
      invalidate = true;
      publish_successor = true;
      successor_type = SOCK_STREAM;
      probe_failure = failure;
      bool outer_stream = cache.isStreamSocket(fd);
      EXPECT_EQ(failure == ENOTSOCK, outer_stream);
      EXPECT_TRUE(successor_published);
      EXPECT_EQ(1, completed_invalidations);
      EXPECT_EQ(2, calls);
      EXPECT_TRUE(cache.isStreamSocket(fd));
      EXPECT_EQ(2, calls);
    }
  }
}

TEST_F(NativeFdQualificationTest, CompetingPublicationWinsWithoutLifecycleInvalidation) {
  for (int fd : {73, kHighFd}) {
    SCOPED_TRACE(fd);
    NativeFdClassifier cache;
    classifier = &cache;
    resetProbe();
    publish_successor = true;
    successor_type = SOCK_DGRAM;
    probe_type = SOCK_STREAM;
    EXPECT_FALSE(cache.isStreamSocket(fd));
    EXPECT_TRUE(successor_published);
    EXPECT_EQ(0, completed_invalidations);
    EXPECT_TRUE(cache.isDatagramSocket(fd));
    EXPECT_EQ(2, calls);
  }
}

TEST_F(NativeFdQualificationTest, CollidingHighFdSuccessorIsNotReturnedForCapturedDescriptor) {
  NativeFdClassifier cache;
  classifier = &cache;
  collision_fd = kHighFd + 4096;
  publish_successor = true;
  successor_type = SOCK_STREAM;
  EXPECT_FALSE(cache.isStreamSocket(kHighFd));
  EXPECT_TRUE(successor_published);
  EXPECT_EQ(2, calls);
  EXPECT_TRUE(cache.isStreamSocket(collision_fd));
  EXPECT_EQ(2, calls);
  publish_successor = false;
  probe_type = SOCK_DGRAM;
  EXPECT_TRUE(cache.isDatagramSocket(kHighFd));
  EXPECT_EQ(3, calls);
}

TEST_F(NativeFdQualificationTest, ForcedNegativeRepairDistinguishesEnotsockFromTransientErrors) {
  for (int fd : {73, kHighFd}) {
    for (int failure : {ENOTSOCK, EBADF, EINTR, EIO, EAGAIN, ENOBUFS, EINVAL}) {
      SCOPED_TRACE(fd);
      SCOPED_TRACE(failure);
      sampler->clearFdCache();
      resetProbe();
      probe_failure = 0;
      ASSERT_TRUE(sampler->isSocketForTest(fd));
      ASSERT_EQ(1, calls);
      probe_failure = failure;
      EXPECT_FALSE(sampler->revalidateSocketForTest(fd));
      EXPECT_EQ(2, calls);
      probe_failure = 0;
      EXPECT_EQ(failure != ENOTSOCK, sampler->isSocketForTest(fd));
      EXPECT_EQ(2, calls);
      EXPECT_TRUE(sampler->revalidateSocketForTest(fd));
      EXPECT_TRUE(sampler->isSocketForTest(fd));
      EXPECT_EQ(3, calls);
    }
  }
}

TEST_F(NativeFdQualificationTest, PackedEpochCycleCannotPublishStaleEnotsockRepair) {
  for (uint32_t clears : {1u, 1u << 17}) {
    SCOPED_TRACE(clears);
    sampler->clearFdCache();
    sampler->clearFdCacheEntry(kHighFd);
    resetProbe();
    epoch_clears = clears;
    probe_failure = ENOTSOCK;
    EXPECT_FALSE(sampler->revalidateSocketForTest(kHighFd));
    EXPECT_EQ(1, calls);
    EXPECT_EQ(clears, completed_clears);
    epoch_clears = 0;
    probe_failure = 0;
    EXPECT_TRUE(sampler->isSocketForTest(kHighFd));
    EXPECT_EQ(2, calls);
  }
}

TEST_F(NativeFdQualificationTest, IndependentClassifiersDoNotShareInvalidationOrRepair) {
  NativeFdClassifier first;
  NativeFdClassifier second;
  for (int fd : {73, kHighFd}) {
    SCOPED_TRACE(fd);
    resetProbe();
    probe_type = SOCK_STREAM;
    ASSERT_TRUE(first.isStreamSocket(fd));
    ASSERT_TRUE(second.isStreamSocket(fd));
    ASSERT_EQ(2, calls);
    first.clearFdType(fd);
    probe_type = SOCK_DGRAM;
    EXPECT_TRUE(first.isDatagramSocket(fd));
    EXPECT_TRUE(second.isStreamSocket(fd));
    EXPECT_EQ(3, calls);
    second.clearFdType(fd);
    EXPECT_TRUE(second.isDatagramSocket(fd));
    EXPECT_EQ(4, calls);
  }
}

class NativeIoForwardingQualificationTest : public ::testing::Test {
protected:
  void SetUp() override {
    NativeSocketInterposer::getOriginalFunctions(send, recv, write, read);
    NativeSocketSampler::getOriginalFunctions(sampler_send, sampler_recv,
                                               sampler_write, sampler_read);
    saved_interposer = NativeSocketInterposer::instance()->setActiveForTest(false);
    saved_sampler = NativeSocketSampler::setActiveForTest(false);
    saved_installed = LibraryPatcher::_socket_active.exchange(false, std::memory_order_acq_rel);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
    NativeFdClassifier::resetProbeCountForTest();
    original_calls = 0;
    block_calls = 0;
    record_calls = 0;
    NativeBlockScope::setHookObserverForTest(observeBlock);
    NativeSocketSampler::setHookObserverForTest(observeRecord);
  }

  void TearDown() override {
    NativeFdClassifier::setProbeOverrideForTest(nullptr);
    NativeBlockScope::setHookObserverForTest(nullptr);
    NativeSocketSampler::setHookObserverForTest(nullptr);
    NativeSocketInterposer::setOriginalFunctions(send, recv, write, read);
    NativeSocketSampler::setOriginalFunctions(sampler_send, sampler_recv,
                                               sampler_write, sampler_read);
    NativeSocketInterposer::instance()->setActiveForTest(saved_interposer);
    NativeSocketSampler::setActiveForTest(saved_sampler);
    LibraryPatcher::_socket_active.store(saved_installed, std::memory_order_release);
    NativeSocketInterposer::instance()->clearFdTypeCache();
    NativeSocketSampler::instance()->clearFdCache();
  }

  static void observeBlock(const char*, NativeBlockKind, int) { block_calls++; }
  static void observeRecord(const char*, int, u8, ssize_t) { record_calls++; }
  static int failProbe(int, int*, int* failure) { *failure = EBADF; return -1; }

  static ssize_t original(int fd, const void* data, size_t size, int flags) {
    // Capture entry errno before any assertion helper may itself change it.
    int entry_errno = errno;
    original_calls++;
    EXPECT_EQ(kHighFd, fd);
    EXPECT_EQ(static_cast<const void*>(buffer), data);
    EXPECT_EQ(1u, size);
    EXPECT_EQ(expected_flags, flags);
    EXPECT_EQ(E2BIG, entry_errno);
    errno = EPIPE;
    return -1;
  }
  static ssize_t originalSend(int fd, const void* data, size_t size, int flags) {
    return original(fd, data, size, flags);
  }
  static ssize_t originalRecv(int fd, void* data, size_t size, int flags) {
    return original(fd, data, size, flags);
  }
  static ssize_t originalWrite(int fd, const void* data, size_t size) {
    return original(fd, data, size, 0);
  }
  static ssize_t originalRead(int fd, void* data, size_t size) {
    return original(fd, data, size, 0);
  }

  void exerciseFourHooks() {
    expected_flags = MSG_DONTWAIT;
    errno = E2BIG;
    EXPECT_EQ(-1, NativeSocketInterposer::send_hook(kHighFd, buffer, 1, expected_flags));
    EXPECT_EQ(EPIPE, errno);
    expected_flags = MSG_PEEK;
    errno = E2BIG;
    EXPECT_EQ(-1, NativeSocketInterposer::recv_hook(kHighFd, buffer, 1, expected_flags));
    EXPECT_EQ(EPIPE, errno);
    expected_flags = 0;
    errno = E2BIG;
    EXPECT_EQ(-1, NativeSocketInterposer::write_hook(kHighFd, buffer, 1));
    EXPECT_EQ(EPIPE, errno);
    errno = E2BIG;
    EXPECT_EQ(-1, NativeSocketInterposer::read_hook(kHighFd, buffer, 1));
    EXPECT_EQ(EPIPE, errno);
    EXPECT_EQ(4, original_calls);
    EXPECT_EQ(0, block_calls);
    EXPECT_EQ(0, record_calls);
  }

  NativeSocketInterposer::send_fn send;
  NativeSocketInterposer::recv_fn recv;
  NativeSocketInterposer::write_fn write;
  NativeSocketInterposer::read_fn read;
  NativeSocketSampler::send_fn sampler_send;
  NativeSocketSampler::recv_fn sampler_recv;
  NativeSocketSampler::write_fn sampler_write;
  NativeSocketSampler::read_fn sampler_read;
  bool saved_interposer;
  bool saved_sampler;
  bool saved_installed;
  static char buffer[1];
  static int expected_flags;
  static int original_calls;
  static int block_calls;
  static int record_calls;
};

char NativeIoForwardingQualificationTest::buffer[1] = {};
int NativeIoForwardingQualificationTest::expected_flags = 0;
int NativeIoForwardingQualificationTest::original_calls = 0;
int NativeIoForwardingQualificationTest::block_calls = 0;
int NativeIoForwardingQualificationTest::record_calls = 0;

TEST_F(NativeIoForwardingQualificationTest, InactiveOwnersIgnoreInstalledAndProbeFailureState) {
  NativeSocketInterposer::setOriginalFunctions(originalSend, originalRecv, originalWrite, originalRead);
  NativeSocketSampler::setOriginalFunctions(nullptr, nullptr, nullptr, nullptr);
  NativeFdClassifier::setProbeOverrideForTest(failProbe);
  for (bool installed : {false, true}) {
    SCOPED_TRACE(installed);
    LibraryPatcher::_socket_active.store(installed, std::memory_order_release);
    original_calls = 0;
    exerciseFourHooks();
    EXPECT_EQ(0u, NativeFdClassifier::probeCountForTest());
  }
}

TEST_F(NativeIoForwardingQualificationTest, SamplerOnlyTransientClassificationPreservesOriginalEntryAndFailureErrno) {
  NativeSocketSampler::setOriginalFunctions(originalSend, originalRecv, originalWrite, originalRead);
  NativeSocketInterposer::setOriginalFunctions(nullptr, nullptr, nullptr, nullptr);
  NativeSocketSampler::setActiveForTest(true);
  LibraryPatcher::_socket_active.store(true, std::memory_order_release);
  NativeFdClassifier::setProbeOverrideForTest(failProbe);
  exerciseFourHooks();
  EXPECT_EQ(4u, NativeFdClassifier::probeCountForTest());
}

TEST_F(NativeIoForwardingQualificationTest, RawCloseAndReuseLeaveIndependentCachesStaleUntilExplicitRepair) {
  NativeFdClassifier::setProbeOverrideForTest(nullptr);
  NativeSocketInterposer* interposer = NativeSocketInterposer::instance();
  NativeSocketSampler* sampler = NativeSocketSampler::instance();
  for (int minimum : {0, 65536}) {
    SCOPED_TRACE(minimum);
    int sockets[2];
    ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sockets));
    ScopedQualificationFd stream(sockets[0]);
    ScopedQualificationFd peer(sockets[1]);
    int pipes[2];
    ASSERT_EQ(0, pipe2(pipes, O_CLOEXEC | O_NONBLOCK));
    ScopedQualificationFd pipe_read(pipes[0]);
    ScopedQualificationFd pipe_write(pipes[1]);
    int fd = fcntl(sockets[0], F_DUPFD_CLOEXEC, minimum);
    ASSERT_GE(fd, minimum);
    ScopedQualificationFd target(fd);
    if (minimum == 0) ASSERT_LT(fd, 65536);
    ASSERT_TRUE(interposer->isStreamSocket(fd));
    ASSERT_TRUE(sampler->isSocketForTest(fd));
    // Raw close is deliberately unobserved, unlike close_hook invalidation.
    int close_result = ::close(target.release());
    if (close_result != 0) {
      ADD_FAILURE() << "raw close failed errno=" << errno;
      return;
    }
    int replacement = ::dup2(pipes[1], fd);
    target.reset(replacement);
    ASSERT_EQ(fd, replacement);
    int type = 0;
    socklen_t size = sizeof(type);
    errno = 0;
    ASSERT_EQ(-1, getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &size));
    ASSERT_EQ(ENOTSOCK, errno);
    EXPECT_TRUE(interposer->isStreamSocket(fd));
    EXPECT_TRUE(sampler->isSocketForTest(fd));
    EXPECT_FALSE(sampler->revalidateSocketForTest(fd));
    EXPECT_FALSE(sampler->isSocketForTest(fd));
    EXPECT_TRUE(interposer->isStreamSocket(fd));
    interposer->clearFdType(fd);
    EXPECT_FALSE(interposer->isStreamSocket(fd));
  }
}

class NativeIoRollbackQualificationTest : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    ASSERT_EQ(0, LibraryPatcher::socket_library_count_for_test());
    ASSERT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    NativeSocketInterposer::getOriginalFunctions(send, recv, write, read);
    NativeSocketSampler::getOriginalFunctions(sampler_send, sampler_recv,
                                               sampler_write, sampler_read);
    saved_interposer = NativeSocketInterposer::instance()->setActiveForTest(false);
    saved_sampler = NativeSocketSampler::setActiveForTest(false);
    saved_owner = NativeSocketInterposer::setHookOwnerPidForTest(getpid());
    saved = true;
    const char* roots[] = {"build/test/resources/native-libs/socket-patch-transaction-lib",
                          "../build/test/resources/native-libs/socket-patch-transaction-lib"};
    for (const char* root : roots) {
      snprintf(directory, sizeof(directory), "%s", root);
      anchor = openLibrary("libjava.so");
      if (anchor != nullptr) break;
    }
    ASSERT_NE(nullptr, anchor) << dlerror();
    network = openLibrary("libnet.so");
    ASSERT_NE(nullptr, network) << dlerror();
    void* symbol = dlsym(network, "socket_patch_read");
    ASSERT_NE(nullptr, symbol) << dlerror();
    Libraries::instance()->updateSymbols(false);
    library = Libraries::instance()->findLibraryByAddress(symbol);
    ASSERT_NE(nullptr, library);
    ASSERT_EQ(1u, library->importCount(im_write));
    ASSERT_EQ(1u, library->importCount(im_read));
    slots[0] = library->findImport(im_write);
    slots[1] = library->findImport(im_read);
    for (int index = 0; index < 2; index++) {
      ASSERT_NE(nullptr, slots[index]);
      originals[index] = __atomic_load_n(slots[index], __ATOMIC_ACQUIRE);
      ASSERT_NE(nullptr, originals[index]);
    }
    current = this;
  }

  void TearDown() override {
    if (!saved) return;
    if (failure_installed) LibraryPatcher::exchangeSocketImportFailureForTest(previous_failure);
    LibraryPatcher::unpatch_socket_functions();
    current = nullptr;
    if (network != nullptr) EXPECT_EQ(0, dlclose(network));
    if (anchor != nullptr) EXPECT_EQ(0, dlclose(anchor));
    if (saved) {
      NativeSocketInterposer::setOriginalFunctions(send, recv, write, read);
      NativeSocketSampler::setOriginalFunctions(sampler_send, sampler_recv,
                                                 sampler_write, sampler_read);
      NativeSocketInterposer::instance()->setActiveForTest(saved_interposer);
      NativeSocketSampler::setActiveForTest(saved_sampler);
      NativeSocketInterposer::setHookOwnerPidForTest(saved_owner);
    }
  }

  static bool failRead(CodeCache* target, ImportId id, size_t index) {
    if (target != current->library || id != im_read || index != 0) return false;
    current->failure_calls++;
    current->partial_write_seen = __atomic_load_n(current->slots[0], __ATOMIC_ACQUIRE)
        == reinterpret_cast<void*>(NativeSocketInterposer::write_hook);
    return true;
  }

  void* openLibrary(const char* name) {
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", directory, name);
    return dlopen(path, RTLD_NOW | RTLD_LOCAL);
  }

  void expectSlots(bool patched) {
    void* hooks[] = {reinterpret_cast<void*>(NativeSocketInterposer::write_hook),
                     reinterpret_cast<void*>(NativeSocketInterposer::read_hook)};
    for (int index = 0; index < 2; index++) {
      EXPECT_EQ(patched ? hooks[index] : originals[index],
                __atomic_load_n(slots[index], __ATOMIC_ACQUIRE));
    }
  }

  void expectPipeForwarding(NativeSocketInterposer::write_fn writer,
                            NativeSocketInterposer::read_fn reader) {
    int descriptors[2];
    ASSERT_EQ(0, pipe(descriptors));
    ScopedQualificationFd read_end(descriptors[0]);
    ScopedQualificationFd write_end(descriptors[1]);
    int flags = fcntl(descriptors[0], F_GETFL);
    ASSERT_GE(flags, 0);
    // A broken writer must fail the payload check rather than block the reader.
    ASSERT_EQ(0, fcntl(descriptors[0], F_SETFL, flags | O_NONBLOCK));
    const char payload[] = "rollback forwarding";
    char received[sizeof(payload)] = {};
    errno = E2BIG;
    ssize_t written = writer(descriptors[1], payload, sizeof(payload));
    int write_errno = errno;
    EXPECT_EQ(static_cast<ssize_t>(sizeof(payload)), written);
    EXPECT_EQ(E2BIG, write_errno);
    errno = EINPROGRESS;
    ssize_t read_bytes = reader(descriptors[0], received, sizeof(received));
    int read_errno = errno;
    EXPECT_EQ(static_cast<ssize_t>(sizeof(received)), read_bytes);
    EXPECT_EQ(EINPROGRESS, read_errno);
    EXPECT_EQ(0, std::memcmp(payload, received, sizeof(payload)));
  }

  void expectPublishedForwarders() {
    NativeSocketInterposer::send_fn current_send;
    NativeSocketInterposer::recv_fn current_recv;
    NativeSocketInterposer::write_fn interposer_write;
    NativeSocketInterposer::read_fn interposer_read;
    NativeSocketInterposer::write_fn sampler_current_write;
    NativeSocketInterposer::read_fn sampler_current_read;
    NativeSocketInterposer::getOriginalFunctions(current_send, current_recv,
                                                 interposer_write, interposer_read);
    NativeSocketSampler::getOriginalFunctions(current_send, current_recv,
                                               sampler_current_write, sampler_current_read);
    // GOT slots may bind executable sanitizer interceptors; forwarding targets
    // come from the profiler DSO's RTLD_NEXT lookup, not those slot originals.
    void* interposer_targets[] = {reinterpret_cast<void*>(interposer_write),
                                 reinterpret_cast<void*>(interposer_read)};
    void* sampler_targets[] = {reinterpret_cast<void*>(sampler_current_write),
                              reinterpret_cast<void*>(sampler_current_read)};
    void* sampler_hooks[] = {reinterpret_cast<void*>(NativeSocketSampler::write_hook),
                            reinterpret_cast<void*>(NativeSocketSampler::read_hook)};
    int hook_indices[] = {NativeSocketInterposer::HOOK_WRITE, NativeSocketInterposer::HOOK_READ};
    const NativeSocketInterposer::NativeIoHookSpec* hooks = NativeSocketInterposer::hookSpecs();
    for (int index = 0; index < 2; index++) {
      ASSERT_NE(nullptr, interposer_targets[index]);
      ASSERT_EQ(interposer_targets[index], sampler_targets[index]);
      ASSERT_NE(hooks[hook_indices[index]].hook, interposer_targets[index]);
      ASSERT_NE(hooks[hook_indices[index]].fork_safe_hook, interposer_targets[index]);
      ASSERT_NE(sampler_hooks[index], interposer_targets[index]);
    }
    expectPipeForwarding(NativeSocketInterposer::write_hook, NativeSocketInterposer::read_hook);
    expectPipeForwarding(NativeSocketSampler::write_hook, NativeSocketSampler::read_hook);
  }

  char directory[PATH_MAX] = {};
  void* anchor = nullptr;
  void* network = nullptr;
  CodeCache* library = nullptr;
  void** slots[2] = {};
  void* originals[2] = {};
  int failure_calls = 0;
  bool partial_write_seen = false;
  bool failure_installed = false;
  bool saved = false;
  bool saved_interposer = false;
  bool saved_sampler = false;
  pid_t saved_owner = 0;
  LibraryPatcher::SocketImportFailureForTest previous_failure = nullptr;
  NativeSocketInterposer::send_fn send;
  NativeSocketInterposer::recv_fn recv;
  NativeSocketInterposer::write_fn write;
  NativeSocketInterposer::read_fn read;
  NativeSocketSampler::send_fn sampler_send;
  NativeSocketSampler::recv_fn sampler_recv;
  NativeSocketSampler::write_fn sampler_write;
  NativeSocketSampler::read_fn sampler_read;
  static NativeIoRollbackQualificationTest* current;
};

NativeIoRollbackQualificationTest* NativeIoRollbackQualificationTest::current = nullptr;

TEST_F(NativeIoRollbackQualificationTest, InitialAdmissionRollbackDisablesEitherOwnerAndAllowsReinstall) {
  for (int owners : {1, 2, 3}) {
    SCOPED_TRACE(owners);
    NativeSocketInterposer::instance()->setActiveForTest((owners & 1) != 0);
    NativeSocketSampler::setActiveForTest((owners & 2) != 0);
    failure_calls = 0;
    partial_write_seen = false;
    previous_failure = LibraryPatcher::exchangeSocketImportFailureForTest(failRead);
    failure_installed = true;
    bool installed = LibraryPatcher::patch_socket_functions();
    LibraryPatcher::exchangeSocketImportFailureForTest(previous_failure);
    failure_installed = false;
    EXPECT_FALSE(installed);
    EXPECT_EQ(1, failure_calls);
    EXPECT_TRUE(partial_write_seen);
    expectSlots(false);
    expectPublishedForwarders();
    EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(0, LibraryPatcher::socket_library_count_for_test());
    EXPECT_FALSE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    EXPECT_FALSE(NativeSocketInterposer::instance()->active());
    EXPECT_FALSE(NativeSocketSampler::active());
    char buffer = 0;
    errno = 0;
    EXPECT_EQ(-1, NativeSocketInterposer::read_hook(-1, &buffer, 1));
    EXPECT_EQ(EBADF, errno);
    errno = 0;
    EXPECT_EQ(-1, NativeSocketSampler::read_hook(-1, &buffer, 1));
    EXPECT_EQ(EBADF, errno);

    NativeSocketInterposer::instance()->setActiveForTest((owners & 1) != 0);
    NativeSocketSampler::setActiveForTest((owners & 2) != 0);
    ASSERT_TRUE(LibraryPatcher::patch_socket_functions());
    expectSlots(true);
    expectPublishedForwarders();
    EXPECT_TRUE(LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    EXPECT_EQ((owners & 1) != 0, NativeSocketInterposer::instance()->active());
    EXPECT_EQ((owners & 2) != 0, NativeSocketSampler::active());
    EXPECT_EQ(2, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(1, LibraryPatcher::socket_library_count_for_test());
    // Reverse the inherited transaction test's two-owner stop order.
    NativeSocketSampler::instance()->stop();
    expectSlots((owners & 1) != 0);
    EXPECT_EQ((owners & 1) != 0,
              LibraryPatcher::_socket_active.load(std::memory_order_acquire));
    NativeSocketInterposer::instance()->stop();
    expectSlots(false);
    EXPECT_EQ(0, LibraryPatcher::socket_patch_count_for_test());
    EXPECT_EQ(0, LibraryPatcher::socket_library_count_for_test());
  }
}

} // namespace

#endif // __linux__
