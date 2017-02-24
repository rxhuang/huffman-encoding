#include "BitInputStream.h"
#include <iostream>
/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: implements methods in BitInputStream.h
   Assignment number: 3
*/

//fill the buffer from input
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

//read the next bit from buffer
int BitInputStream::readBit() {
  if(nbits==8){//fill if needed
    fill();
  }
  //return 1 if bit reads 1, 0 otherwise
  int i = (buf>>nbits)&1;
  nbits++;
  return i;
}
