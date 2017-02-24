#include <iostream>
/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: input stream that reads a single bit ata time
   Assignment number: 3
*/

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

  //read the next bit in buffer
  int readBit();
};
