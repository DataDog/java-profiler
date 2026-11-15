/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "recordingOutput.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <atomic>
#include <csignal>
#include <fcntl.h>
#include <sys/resource.h>
#include <thread>
#include <vector>

class RecordingOutputTest : public ::testing::Test {
protected:
    char _path[64] = "/tmp/ddprof-recording-output-XXXXXX";
    int _fd = -1;
    void SetUp() override {
        _fd = mkstemp(_path);
        ASSERT_GE(_fd, 0);
    }
    void TearDown() override {
        if (_fd >= 0) close(_fd);
        unlink(_path);
    }
    int target() {
        char path[] = "/tmp/ddprof-recording-target-XXXXXX";
        int fd = mkstemp(path);
        if (fd >= 0) unlink(path);
        return fd;
    }
};

TEST_F(RecordingOutputTest, CompleteWritesPatchesAndDeliveryAreIdentityQualified) {
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("abcdef", 6));
    ASSERT_TRUE(output.patch("XY", 2, 2));
    int destination = target();
    ASSERT_GE(destination, 0);
    ASSERT_TRUE(output.prepareTarget(destination));
    int reader = dup(destination);
    ASSERT_GE(reader, 0);
    auto delivery = output.deliverAndClose(destination, 2, 3);
    ASSERT_TRUE(delivery);
    EXPECT_NE(0U, delivery.recording_id);
    EXPECT_EQ(2U, delivery.first_chunk);
    EXPECT_EQ(3U, delivery.last_chunk);
    EXPECT_EQ(6U, delivery.bytes);
    char bytes[6];
    EXPECT_EQ(6, pread(reader, bytes, sizeof(bytes), 0));
    EXPECT_EQ("abXYef", std::string(bytes, sizeof(bytes)));
    close(reader);
    EXPECT_EQ(6, pread(_fd, bytes, sizeof(bytes), 0));  // Delivery alone does not retire source.
    EXPECT_TRUE(output.restart());
    struct stat state;
    ASSERT_EQ(0, fstat(_fd, &state));
    EXPECT_EQ(0, state.st_size);
}

TEST_F(RecordingOutputTest, FailedDestinationKeepsSourceAndAllowsLaterCompleteDelivery) {
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("owned", 5));
    int refused = open("/dev/null", O_RDONLY);
    ASSERT_GE(refused, 0);
    EXPECT_FALSE(output.deliverAndClose(refused, 1, 1));
    EXPECT_TRUE(output.good());
    char bytes[5];
    ASSERT_EQ(5, pread(_fd, bytes, sizeof(bytes), 0));
    EXPECT_EQ("owned", std::string(bytes, sizeof(bytes)));
    int destination = target();
    ASSERT_GE(destination, 0);
    ASSERT_TRUE(output.prepareTarget(destination));
    EXPECT_TRUE(output.deliverAndClose(destination, 1, 1));
}

TEST_F(RecordingOutputTest, InheritedPrefixIsReportedSeparatelyFromNativeChunkCustody) {
    ASSERT_EQ(3, write(_fd, "old", 3));
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("new", 3));
    int destination = target();
    ASSERT_GE(destination, 0);
    ASSERT_TRUE(output.prepareTarget(destination));
    int reader = dup(destination);
    ASSERT_GE(reader, 0);
    auto delivery = output.deliverAndClose(destination, 1, 1);
    ASSERT_TRUE(delivery);
    EXPECT_EQ(3U, delivery.inherited_prefix_bytes);
    EXPECT_EQ(6U, delivery.bytes);
    char bytes[6];
    ASSERT_EQ(6, pread(reader, bytes, sizeof(bytes), 0));
    EXPECT_EQ("oldnew", std::string(bytes, sizeof(bytes)));
    close(reader);
    ASSERT_TRUE(output.restart());
    ASSERT_TRUE(output.append("fresh", 5));
    destination = target();
    ASSERT_GE(destination, 0);
    ASSERT_TRUE(output.prepareTarget(destination));
    auto next = output.deliverAndClose(destination, 2, 2);
    ASSERT_TRUE(next);
    EXPECT_EQ(delivery.recording_id, next.recording_id);
    EXPECT_EQ(0U, next.inherited_prefix_bytes);
    EXPECT_EQ(5U, next.bytes);
}

TEST_F(RecordingOutputTest, FailedDestinationCloseQuarantinesSourceAndRetainsItsBytes) {
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("owned", 5));
    int destination = target();
    ASSERT_GE(destination, 0);
    ASSERT_EQ(0, close(destination));
    EXPECT_FALSE(output.closeTarget(destination));
    EXPECT_FALSE(output.good());
    EXPECT_EQ(EBADF, output.error());
    EXPECT_FALSE(output.append("later", 5));
    char bytes[5];
    ASSERT_EQ(5, pread(_fd, bytes, sizeof(bytes), 0));
    EXPECT_EQ("owned", std::string(bytes, sizeof(bytes)));
}

TEST_F(RecordingOutputTest, AliasIsRejectedBeforeDestinationTruncation) {
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("original", 8));
    int alias = open(_path, O_RDWR);
    ASSERT_GE(alias, 0);
    EXPECT_FALSE(output.prepareTarget(alias));
    close(alias);
    char bytes[8];
    ASSERT_EQ(8, pread(_fd, bytes, sizeof(bytes), 0));
    EXPECT_EQ("original", std::string(bytes, sizeof(bytes)));
}

TEST_F(RecordingOutputTest, ShortSourceAndInvalidDescriptorCannotCertifyCopy) {
    ASSERT_EQ(5, write(_fd, "owned", 5));
    int destination = target();
    ASSERT_GE(destination, 0);
    EXPECT_FALSE(OS::copyFile(_fd, destination, 0, 6));
    EXPECT_FALSE(OS::copyFile(-1, destination, 0, 1));
    close(destination);
    char bytes[5];
    ASSERT_EQ(5, pread(_fd, bytes, sizeof(bytes), 0));
    EXPECT_EQ("owned", std::string(bytes, sizeof(bytes)));
}

TEST_F(RecordingOutputTest, FailedPatchIsStickyAndDoesNotIssueDelivery) {
    ASSERT_EQ(5, write(_fd, "owned", 5));
    int readonly = open(_path, O_RDONLY);
    ASSERT_GE(readonly, 0);
    RecordingOutput output(readonly);
    EXPECT_FALSE(output.patch("lost", 4, 0));
    EXPECT_FALSE(output.good());
    EXPECT_EQ(EBADF, output.error());
    EXPECT_FALSE(output.append("later", 5));
    int destination = target();
    ASSERT_GE(destination, 0);
    EXPECT_FALSE(output.deliverAndClose(destination, 1, 1));
    close(readonly);
}

TEST_F(RecordingOutputTest, ActualPartialPwriteRetainsFailureAndRefusesLaterBytes) {
    struct rlimit original;
    ASSERT_EQ(0, getrlimit(RLIMIT_FSIZE, &original));
    struct sigaction previous, ignored{};
    ignored.sa_handler = SIG_IGN;
    sigemptyset(&ignored.sa_mask);
    ASSERT_EQ(0, sigaction(SIGXFSZ, &ignored, &previous));
    struct rlimit limited = original;
    limited.rlim_cur = 1;
    int installed = setrlimit(RLIMIT_FSIZE, &limited);
    RecordingOutput output(_fd);
    bool appended = installed == 0 && output.append("four", 4);
    int restored = setrlimit(RLIMIT_FSIZE, &original);
    int signal_restored = sigaction(SIGXFSZ, &previous, nullptr);
    ASSERT_EQ(0, installed);
    ASSERT_EQ(0, restored);
    ASSERT_EQ(0, signal_restored);
    EXPECT_FALSE(appended);
    EXPECT_FALSE(output.good());
    EXPECT_EQ(EFBIG, output.error());
    EXPECT_FALSE(output.append("later", 5));
    struct stat state;
    ASSERT_EQ(0, fstat(_fd, &state));
    EXPECT_EQ(1, state.st_size);  // One real byte, not a fabricated short-write return.
    char byte;
    ASSERT_EQ(1, pread(_fd, &byte, 1, 0));
    EXPECT_EQ('f', byte);
}

TEST_F(RecordingOutputTest, ConcurrentStripesOwnDisjointContiguousRanges) {
    RecordingOutput output(_fd);
    std::atomic<int> failed{0};
    std::vector<std::thread> workers;
    for (int stripe = 0; stripe < 4; ++stripe) {
        workers.emplace_back([&, stripe] {
            for (u64 i = 1; i <= 256; ++i) {
                u64 value = stripe * 256 + i;
                if (!output.append(reinterpret_cast<const char*>(&value), sizeof(value))) ++failed;
            }
        });
    }
    for (auto& worker : workers) worker.join();
    ASSERT_EQ(0, failed.load());
    ASSERT_TRUE(output.good());
    std::vector<u64> received(1024);
    ASSERT_EQ(static_cast<ssize_t>(received.size() * sizeof(u64)),
              pread(_fd, received.data(), received.size() * sizeof(u64), 0));
    std::sort(received.begin(), received.end());
    for (size_t i = 0; i < received.size(); ++i) EXPECT_EQ(i + 1, received[i]);
}

TEST_F(RecordingOutputTest, InvalidSourceCannotAppendPatchRestartOrSeal) {
    RecordingOutput output(-1);
    EXPECT_FALSE(output.good());
    EXPECT_EQ(EBADF, output.error());
    EXPECT_FALSE(output.append("x", 1));
    EXPECT_FALSE(output.patch("x", 1, 0));
    EXPECT_FALSE(output.restart());
    EXPECT_FALSE(output.sealAndClose(1, 1));
}

TEST_F(RecordingOutputTest, PatchBoundariesRejectBytesOutsideTheReservedRange) {
    for (u64 offset : {4U, 3U}) {
        int fd = target();
        ASSERT_GE(fd, 0);
        RecordingOutput output(fd);
        ASSERT_TRUE(output.append("abc", 3));
        EXPECT_TRUE(output.patch("", 0, 3));
        EXPECT_FALSE(output.patch("x", 1, offset));
        EXPECT_EQ(EINVAL, output.error());
        EXPECT_EQ(0, close(fd));
    }
}

TEST_F(RecordingOutputTest, OversizeReservationFailsBeforeReadingTheInput) {
    RecordingOutput output(_fd);
    EXPECT_FALSE(output.append("x", std::numeric_limits<size_t>::max()));
    EXPECT_EQ(EFBIG, output.error());
    struct stat state;
    ASSERT_EQ(0, fstat(_fd, &state));
    EXPECT_EQ(0, state.st_size);
}

TEST_F(RecordingOutputTest, InvalidChunkRangesCannotCertifyDelivery) {
    for (auto chunks : {std::make_pair(0U, 1U), std::make_pair(2U, 1U)}) {
        int source = target();
        ASSERT_GE(source, 0);
        RecordingOutput output(source);
        ASSERT_TRUE(output.append("owned", 5));
        int destination = target();
        ASSERT_GE(destination, 0);
        EXPECT_FALSE(output.deliverAndClose(destination, chunks.first, chunks.second));
        EXPECT_EQ(EINVAL, output.error());
        EXPECT_EQ(-1, fcntl(destination, F_GETFD));
        char bytes[5];
        EXPECT_EQ(5, pread(source, bytes, sizeof(bytes), 0));
        EXPECT_EQ(0, close(source));
    }
}

TEST_F(RecordingOutputTest, ChangedSourceSizeInvalidatesCustodyAndCountsFailureOnce) {
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("owned", 5));
    ASSERT_EQ(0, ftruncate(_fd, 4));
    long long before = Counters::getCounter(JFR_OUTPUT_FAILURES);
    int destination = target();
    ASSERT_GE(destination, 0);
    EXPECT_FALSE(output.deliverAndClose(destination, 1, 1));
    EXPECT_EQ(EIO, output.error());
    EXPECT_FALSE(output.invalidate(EINVAL));
    EXPECT_EQ(EIO, output.error());
#ifdef COUNTERS
    EXPECT_EQ(1, Counters::getCounter(JFR_OUTPUT_FAILURES) - before);
#endif
}

TEST_F(RecordingOutputTest, SealClosesSourceAndDifferentRecordingsHaveDifferentCustodyIds) {
    RecordingOutput first(_fd);
    ASSERT_TRUE(first.append("one", 3));
    auto sealed = first.sealAndClose(1, 1);
    ASSERT_TRUE(sealed);
    EXPECT_EQ(3U, sealed.bytes);
    EXPECT_EQ(-1, fcntl(_fd, F_GETFD));
    _fd = -1;
    int source = target();
    ASSERT_GE(source, 0);
    RecordingOutput second(source);
    ASSERT_TRUE(second.append("two", 3));
    auto next = second.sealAndClose(1, 1);
    ASSERT_TRUE(next);
    EXPECT_NE(sealed.recording_id, next.recording_id);
}

TEST_F(RecordingOutputTest, DestinationQualificationFailureDoesNotPoisonTheSource) {
    RecordingOutput output(_fd);
    ASSERT_TRUE(output.append("owned", 5));
    EXPECT_FALSE(output.prepareTarget(-1));
    EXPECT_TRUE(output.good());
    int destination = target();
    ASSERT_GE(destination, 0);
    ASSERT_EQ(8, write(destination, "obsolete", 8));
    ASSERT_TRUE(output.prepareTarget(destination));
    struct stat state;
    ASSERT_EQ(0, fstat(destination, &state));
    EXPECT_EQ(0, state.st_size);
    EXPECT_TRUE(output.deliverAndClose(destination, 1, 1));
}
