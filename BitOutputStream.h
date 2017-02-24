#include <iostream>
/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 23
   Overview: An output stream that reads a single bit at a time
   Assignment number: 3
*/

class BitOutputStream {
 private:
  char buf; // one byte buffer of bits
  int nbits; // how many bits have been written to buf
  std::ostream & out; // reference to the output stream to use

public:
  /** Initialize a BitOutputStream that will use
   * the given ostream for output */
 BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0){};

  //send the buffer to the output and clear it
  void flush();

  //write the least significant bit to buffer and increment buffer index
  void writeBit(int i);
};
