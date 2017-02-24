#include <iostream>
#include "BitOutputStream.h"
/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: inmplements methods in BitOutputStrream.h
   Assignment number: 3
*/

//send buffer to output and clear buffer
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

//write least significant bit to buffer and increment buffer index
void BitOutputStream::writeBit(int i) {
  if(nbits==8){//if full, flush
    flush();
  }
  buf = buf|((i&1)<<nbits);
  nbits++;
}
