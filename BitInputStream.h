#include <iostream>
class BitInputStream{
private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been read from bufstd::istream & in;
  std::istream & in; // the input stream to use

public:
  /** Initialize a BitInputStream that will use
   * the given istream for input.
   */
 BitInputStream(std::istream & is) : in(is), buf(0), nbits(8){};

  /** Fill the buffer from the input */
  void fill();

  int readBit();
};
