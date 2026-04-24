#include "hotspot/compressedLinenumberStream.h"

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
