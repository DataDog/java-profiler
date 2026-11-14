/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _RECORDINGOUTPUT_H
#define _RECORDINGOUTPUT_H

#include "os.h"
#include "counters.h"
#include <atomic>
#include <cerrno>
#include <limits>
#include <sys/stat.h>
#include <unistd.h>

// Native delivery custody only: never a decoded receiving ACK. The source
// Recording remains the owner until every write, patch, copy and close succeeds.
class RecordingOutput {
    static_assert(std::atomic<u64>::is_always_lock_free, "recording offsets require lock-free atomics");
public:
    struct Delivery {
        u64 recording_id = 0;
        u64 first_chunk = 0;
        u64 last_chunk = 0;
        u64 bytes = 0;
        u64 inherited_prefix_bytes = 0;
        explicit operator bool() const { return recording_id != 0; }
    };

private:
    inline static std::atomic<u64> _next_id{1};
    static u64 nextId() {
        u64 value = _next_id.load(std::memory_order_acquire);
        while (value != std::numeric_limits<u64>::max()) {
            if (_next_id.compare_exchange_weak(value, value + 1, std::memory_order_acq_rel,
                                              std::memory_order_acquire)) return value;
        }
        return 0;
    }

    const int _fd;
    const u64 _id;
    std::atomic<u64> _offset;
    u64 _inherited_prefix_bytes = 0;
    std::atomic<int> _error{0};

    bool fail(int error) {
        int expected = 0;
        if (_error.compare_exchange_strong(expected, error == 0 ? EIO : error,
                                           std::memory_order_acq_rel, std::memory_order_acquire)) {
            Counters::increment(JFR_OUTPUT_FAILURES);
        }
        return false;
    }

    bool qualifySource(u64 first_chunk, u64 last_chunk) {
        if (!good()) return false;
        if (first_chunk == 0 || last_chunk < first_chunk) return fail(EINVAL);
        struct stat source;
        if (fstat(_fd, &source) != 0) return fail(errno);
        if (source.st_size < 0 || static_cast<u64>(source.st_size) != size()) return fail(EIO);
        return true;
    }

    bool writeAt(const char* bytes, size_t size, u64 offset) {
        constexpr u64 max_offset = static_cast<u64>(std::numeric_limits<off_t>::max());
        if (!good() || offset > max_offset || size > max_offset - offset) return fail(EFBIG);
        size_t done = 0;
        // Bounded even under interrupted or adversarial one-byte writes.
        for (unsigned attempt = 0; done < size && attempt < 256; ++attempt) {
            ssize_t written = pwrite(_fd, bytes + done, size - done, static_cast<off_t>(offset + done));
            if (written > 0) done += static_cast<size_t>(written);
            else if (written < 0 && errno == EINTR) continue;
            else return fail(written == 0 ? EIO : errno);
        }
        return done == size || fail(EIO);
    }

public:
    explicit RecordingOutput(int fd)
        : _fd(fd), _id(nextId()),
          _offset(0) {
        off_t end = lseek(fd, 0, SEEK_END);
        if (end < 0) fail(errno);
        else {
            _inherited_prefix_bytes = static_cast<u64>(end);
            _offset.store(static_cast<u64>(end), std::memory_order_release);
        }
        if (_id == 0) fail(EOVERFLOW);
    }

    bool good() const { return _error.load(std::memory_order_acquire) == 0; }
    u64 size() const { return _offset.load(std::memory_order_acquire); }
    int error() const { return _error.load(std::memory_order_acquire); }
    bool invalidate(int error) { return fail(error); }

    bool append(const char* bytes, size_t size) {
        if (!good()) return false;
        // Separate stripes must not interleave partial writes within one event.
        u64 offset = _offset.fetch_add(size, std::memory_order_acq_rel);
        return writeAt(bytes, size, offset);
    }

    bool patch(const char* bytes, size_t size, u64 offset) {
        u64 end = this->size();
        if (offset > end || size > end - offset) return fail(EINVAL);
        return writeAt(bytes, size, offset);
    }

    // Before truncating a dump destination, reject hard links/symlinks to the
    // source. Opening with O_TRUNC before this check would destroy owned bytes.
    bool prepareTarget(int target_fd) const {
        struct stat source, target;
        if (fstat(_fd, &source) != 0 || fstat(target_fd, &target) != 0) return false;
        if (source.st_dev == target.st_dev && source.st_ino == target.st_ino) {
            errno = EINVAL;
            return false;
        }
        return !S_ISREG(target.st_mode) || ftruncate(target_fd, 0) == 0;
    }

    // Delivery requires owner exclusion of appenders. Consumes target_fd even
    // on failure; failure never truncates the source.
    Delivery deliverAndClose(int target_fd, u64 first_chunk, u64 last_chunk) {
        u64 bytes = size();
        bool copied = qualifySource(first_chunk, last_chunk) &&
                      OS::copyFile(_fd, target_fd, 0, bytes);
        if (!closeTarget(target_fd)) return {};
        return copied ? Delivery{_id, first_chunk, last_chunk, bytes, _inherited_prefix_bytes} : Delivery{};
    }

    Delivery sealAndClose(u64 first_chunk, u64 last_chunk) {
        if (!qualifySource(first_chunk, last_chunk) || !closeTarget(_fd)) return {};
        return {_id, first_chunk, last_chunk, size(), _inherited_prefix_bytes};
    }

    bool closeTarget(int target_fd) {
        if (close(target_fd) == 0) return true;
        // Quarantine instead of retrying a possibly recycled descriptor after close failure.
        return fail(errno);
    }

    bool restart() {
        if (!good() || ftruncate(_fd, 0) != 0) return fail(errno);
        _offset.store(0, std::memory_order_release);
        _inherited_prefix_bytes = 0;
        return true;
    }
};

#endif // _RECORDINGOUTPUT_H
