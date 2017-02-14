#include "HCNode.h"
#include <iostream>
/*
  Compare this HCNode and other for priority ordering.

  Smaller count means higher priority.
  Use node symbol for deterministic tiebkreaking
*/
bool HCNode::operator<(HCNode const &other) const{
  // if counts are different, just compare counts
  if(this->count != other.count) return this->count > other.count;
  //counts are equal. use symbol value to break tie
  return this->symbol < other.symbol;
}
