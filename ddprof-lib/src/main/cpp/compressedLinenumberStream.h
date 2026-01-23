#ifndef _COMPRESSED_LINENUMBER_STREAM_H
#define _COMPRESSED_LINENUMBER_STREAM_H

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
  static const int lg_H  = 6;        // log-base-2 of H (lg 64 == 6)
  static const int H     = 1<<lg_H;  // number of "high" bytes (64)
  static const int X     = 1  ;      // there is one excluded byte ('\0')
  static const int MAX_b = (1<<BitsPerByte)-1;  // largest byte value
  static const int L     = (MAX_b+1)-X-H;       // number of "low" bytes (191)
  static const int MAX_LENGTH = 5;   // lengths are in [1..5]
  static const uint32_t MAX_VALUE = (uint32_t)-1;  // 2^^32-1


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
  int read_signed_int() { return decode_sign(read_uint()); }
  uint32_t read_uint();
};

#endif // _COMPRESSED_LINENUMBER_STREAM_H