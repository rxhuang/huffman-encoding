#include HCNODE_H
#include <iostream>
/*
  Compare this HCNode and other for priority ordering.

  Smaller count means higher priority.
  Use node symbol for deterministic tiebkreaking
*/
bool HCNode::operator<(HCNode const &other) const{
  // if counts are different, just compare counts
  if(count != other.count) return count > other.count;
  //counts are equal. use symbol value to break tie
  return symbol < other.symbol;
}
