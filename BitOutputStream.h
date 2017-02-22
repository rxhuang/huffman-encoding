#include <iostream>

class BitOutputStream {
 private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use

public:
  /** Initialize a BitOutputStream that will use
   * the given ostream for output */
 BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0){};

  void flush();

  void writeBit(int i);
};
