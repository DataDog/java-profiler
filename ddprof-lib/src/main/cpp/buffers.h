#ifndef _BUFFERS_H
#define _BUFFERS_H

#include <cassert>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "os.h"

const int BUFFER_SIZE = 1024;
const int BUFFER_LIMIT = BUFFER_SIZE - 128;
// we use this space, which is larger than the longest string we will store,
// as a temporary defence against overflow. If we ever write into this space
// we may produce a corrupt recording, which is sad, but we can't overwrite
// offsets in the adjacent buffer, which has been a frequent cause of hard to
// diagnose crashes. Ultimately, the entire FlightRecorder implementation needs
// to be reworked for the sake of safety, but this small change derisks the legacy
// implementation at a runtime cost of 16 * 8KiB = 128KiB
const int RECORDING_BUFFER_OVERFLOW = 8192;
const int RECORDING_BUFFER_SIZE = 65536;
const int RECORDING_BUFFER_LIMIT = RECORDING_BUFFER_SIZE - 4096;
const int MAX_STRING_LENGTH = 8191;

typedef ssize_t (*FlushCallback)(char* data, int len);

class Buffer {
  private:
    int _offset;
    static const int _limit = BUFFER_SIZE - sizeof(int);
    char _data[_limit];

  public:
    Buffer() : _offset(0) {
        memset(_data, 0, _limit);
    }

    virtual int limit() const {
        return _limit;
    }

    bool flushIfNeeded(FlushCallback callback, int limit = BUFFER_LIMIT) {
        if (_offset > limit) {
            if (callback(_data, _offset) == _offset) {
                reset();
                return true;
            }
        }
        return false;
    }

    const char* data() const {
        return _data;
    }

    int offset() const {
        return _offset;
    }

    // ! This method returns the position *before* skipping !
    int skip(int delta) {
        assert(_offset + delta < limit());
        int here = _offset;
        _offset = here + delta;
        return here;
    }

    void reset() {
        _offset = 0;
    }

    void put(const char* v, u32 len) {
        assert(_offset + len < limit());
        memcpy(_data + _offset, v, len);
        _offset += (int)len;
    }

    void put8(char v) {
        assert(_offset < limit());
        _data[_offset++] = v;
    }

    void put16(short v) {
        assert(_offset + 2 < limit());
        *(short*)(_data + _offset) = htons(v);
        _offset += 2;
    }

    void put32(int v) {
        assert(_offset + 4 < limit());
        *(int*)(_data + _offset) = htonl(v);
        _offset += 4;
    }

    // alignment issue to be looked at
    //    runtime error: store to misaligned address 0x766bb5a1e814 for type 'u64', which requires 8 byte alignment
    //         0x766bb5a1e814: note: pointer points here
    __attribute__((no_sanitize("undefined")))
    void put64(u64 v) {
        assert(_offset + 8 < limit());
        *(u64*)(_data + _offset) = OS::hton64(v);
        _offset += 8;
    }

    void putFloat(float v) {
        union {
            float f;
            int i;
        } u;

        u.f = v;
        put32(u.i);
    }

    void putVar32(u32 v) {
        assert(_offset + 5 < limit());
        while (v > 0x7f) {
            _data[_offset++] = (char)v | 0x80;
            v >>= 7;
        }
        _data[_offset++] = (char)v;
    }

    void putVar64(u64 v) {
        assert(_offset + 9 < limit());
        int iter = 0;
        while (v > 0x1fffff) {
            _data[_offset++] = (char)v | 0x80; v >>= 7;
            _data[_offset++] = (char)v | 0x80; v >>= 7;
            _data[_offset++] = (char)v | 0x80; v >>= 7;
            if (++iter == 3) return;
        }
        while (v > 0x7f) {
            _data[_offset++] = (char)v | 0x80;
            v >>= 7;
        }
        _data[_offset++] = (char)v;
    }

    void putUtf8(const char* v) {
        if (v == NULL) {
            put8(0);
        } else {
            size_t len = strlen(v);
            putUtf8(v, len);
        }
    }

    void putUtf8(const char* v, u32 len) {
        len = len < MAX_STRING_LENGTH ? len : MAX_STRING_LENGTH;
        put8(3);
        putVar32(len);
        put(v, len);
    }

    void put8(int offset, char v) {
        _data[offset] = v;
    }

    void putVar32(int offset, u32 v) {
        _data[offset] = v | 0x80;
        _data[offset + 1] = (v >> 7) | 0x80;
        _data[offset + 2] = (v >> 14) | 0x80;
        _data[offset + 3] = (v >> 21) | 0x80;
        _data[offset + 4] = (v >> 28);
    }
};

class RecordingBuffer : public Buffer {
  private:
    static const int _limit = RECORDING_BUFFER_SIZE - sizeof(Buffer);
    // we reserve 8KiB to overflow in to in case event serialisers in
    // the flight recorder are buggy. If we ever use the overflow,
    // which is sized to accomodate the largest possible string, we
    // will truncate and may produce a corrupt recording, but we will
    // not write into arbitrary memory.
    char _buf[_limit + RECORDING_BUFFER_OVERFLOW];

  public:
    RecordingBuffer() : Buffer() {
        memset(_buf, 0, _limit);
    }

    int limit() const override {
        return _limit;
    }

    bool flushIfNeeded(FlushCallback callback, int limit = RECORDING_BUFFER_LIMIT) {
        return Buffer::flushIfNeeded(callback, limit);
    }
};

#endif // _BUFFERS_H
