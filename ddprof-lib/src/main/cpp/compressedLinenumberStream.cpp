#include "compressedLinenumberStream.h"

CompressedLineNumberStream::CompressedLineNumberStream(unsigned char* buffer) :
  _buffer(buffer), _position(0), _bci(0), _line(0) {
};

void CompressedLineNumberStream::reset() {
    _position = 0;
    _bci = 0;
    _line = 0;
}

bool CompressedLineNumberStream::read_pair() {
  unsigned char next = read_byte();
  // Check for terminator
  if (next == 0) return false;
  if (next == 0xFF) {
    // Escape character, regular compression used
    _bci  += read_signed_int();
    _line += read_signed_int();
  } else {
    // Single byte compression used
    _bci  += next >> 3;
    _line += next & 0x7;
  }
  return true;
}

uint32_t CompressedLineNumberStream::read_uint() {
    const int pos = _position;
    const uint32_t b_0 = (uint8_t)_buffer[pos];  //b_0 = a[0]
    assert(b_0 >= X);
    uint32_t sum = b_0 - X;
    if (sum < L) {  // common case
      _position = pos + 1;
      return sum;
    }
    // must collect more bytes:  b[1]...b[4]
    int lg_H_i = lg_H;  // lg(H)*i == lg(H^^i)
    for (int i = 1; ; i++) {  // for i in [1..4]
      const uint32_t b_i = (uint8_t) _buffer[pos + i];  //b_i = a[i]
      assert(b_i >= X);
      sum += (b_i - X) << lg_H_i;  // sum += (b[i]-X)*(64^^i)
      if (b_i < X+L || i == MAX_LENGTH-1) {
        _position = pos + i + 1;
        return sum;
      }
      lg_H_i += lg_H;
    }
  }