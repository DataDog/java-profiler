#ifndef _HOTSPOT_COMPRESSED_LINENUMBER_STREAM_H
#define _HOTSPOT_COMPRESSED_LINENUMBER_STREAM_H

#include <cassert>
#include <cstdint>

/**
 * Implementation of openjdk CompressedLineNumberStream
 * https://github.com/openjdk/jdk/blob/master/src/hotspot/share/oops/method.hpp#L910
 *
 * Based on open jdk source:
 * https://github.com/openjdk/jdk/blob/master/src/hotspot/share/code/compressedStream.hpp/cpp
 * https://github.com/openjdk/jdk/blob/master/src/hotspot/share/utilities/unsigned5.hpp/cpp
 */

class CompressedLineNumberStream {
private:
  // Math constants for the modified UNSIGNED5 coding of Pack200
  static const int BitsPerByte = 8;
  enum {   
    // Constants for UNSIGNED5 coding of Pack200
    lg_H = 6, H = 1<<lg_H,    // number of high codes (64)
    L = (1<<BitsPerByte)-H,   // number of low codes (192)
    MAX_i = 4                 // bytes are numbered in (0..4), max 5 bytes
  };

  unsigned char* _buffer;
  int _position;

  int _bci;
  int _line;

public:
  CompressedLineNumberStream(unsigned char* buffer);

  bool read_pair();
  void reset();

  int bci() const    { return _bci; }
  int line() const   { return _line; }

private:
  unsigned char read_byte() { return _buffer[_position++]; }
  static int decode_sign(uint32_t value) { return (value >> 1) ^ -(int)(value & 1); }
  int read_signed_int() { return decode_sign(read_int()); }
  int read_int() {
    int   b0 = read_byte();
    if (b0 < L)  return b0;
    else return read_int_mb(b0);
  }

    // This encoding, called UNSIGNED5, is taken from J2SE Pack200.
  // It assumes that most values have lots of leading zeroes.
  // Very small values, in the range [0..191], code in one byte.
  // Any 32-bit value (including negatives) can be coded, in
  // up to five bytes.  The grammar is:
  //    low_byte  = [0..191]
  //    high_byte = [192..255]
  //    any_byte  = low_byte | high_byte
  //    coding = low_byte
  //           | high_byte low_byte
  //           | high_byte high_byte low_byte
  //           | high_byte high_byte high_byte low_byte
  //           | high_byte high_byte high_byte high_byte any_byte
  // Each high_byte contributes six bits of payload.
  // The encoding is one-to-one (except for integer overflow)
  // and easy to parse and unparse.
  int read_int_mb(int b0) {
    int     pos = _position - 1;
    unsigned char* buf = _buffer + pos;
    assert(buf[0] == b0 && b0 >= L && "correctly called");
    int    sum = b0;
    // must collect more bytes:  b[1]...b[4]
    int lg_H_i = lg_H;
    for (int i = 0; ; ) {
      int b_i = buf[++i]; // b_i = read(); ++i;
      sum += b_i << lg_H_i;  // sum += b[i]*(64**i)
      if (b_i < L || i == MAX_i) {
        _position = (pos+i+1);
        return sum;
      }
      lg_H_i += lg_H;
    }
  }
};

#endif // _HOTSPOT_COMPRESSED_LINENUMBER_STREAM_H