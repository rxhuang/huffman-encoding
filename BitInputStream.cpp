#include "BitInputStream.h"
#include <iostream>

void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

int BitInputStream::readBit() {
  if(nbits==8){
    fill();
  }
  int i = (buf>>nbits)&1;
  nbits++;
  return i;
}
