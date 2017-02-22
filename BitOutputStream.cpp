#include <iostream>
#include "BitOutputStream.h"

void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

void BitOutputStream::writeBit(int i) {
  if(nbits==8){
    flush();
  }
  buf = buf|((i&1)<<nbits);
  nbits++;
}
