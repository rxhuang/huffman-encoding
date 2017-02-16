/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: implements a Huffman Compression Tree
   Assignment number: 3
*/

#include "HCTree.h"
#include <stack>
using namespace std;

HCTree::~HCTree(){
  deleteAll(root);
}
void HCTree::build(const vector<int> & freqs){
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> queue;

  for(int i = 0; i < freqs.size(); i++){
    if(freqs[i] != 0){
      HCNode* newNode = new HCNode(freqs[i], i);
      leaves[i] = newNode;
      queue.push(newNode);
    }
  }

  while(queue.size()!= 1){
    HCNode* left = queue.top();
    queue.pop();
    HCNode* right = queue.top();
    queue.pop();
    int count = left->count+right->count;
    HCNode* parent = new HCNode(count, left->symbol);
    left->p = parent;
    right->p = parent;
    parent->c0= left;
    parent->c1= right;
    queue.push(parent);
  }
  root = queue.top();

}
void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode* temp = leaves[symbol];
  string toWrite;
  while(temp->p != NULL){
    if(temp->p->c0==temp){
      toWrite = '0'+ toWrite;
    }else if(temp->p->c1==temp){
      toWrite = '1'+toWrite;
    }
    temp = temp->p;
  }
  out<<toWrite;
}

int HCTree::decode(ifstream& in) const{
  byte symbol;
  HCNode* curr = root;
  while(curr->c0 != NULL || curr->c1 != NULL){
    symbol =(byte) in.get();
    if(symbol== '0'){
      curr= curr->c0;
    }else if(symbol == '1'){
      curr = curr->c1;
    }
  }
  //return the symbol in leaf child
  return curr->symbol;
}


void HCTree::deleteAll(HCNode* node){
  if(node == NULL) return;
  deleteAll(node->c0);
  deleteAll(node->c1);
  delete(node);
}
