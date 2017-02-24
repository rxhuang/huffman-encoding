/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: implements a Huffman Compression Tree
   Assignment number: 3
*/

#include "HCTree.h"
#include <stack>

using namespace std;
//destructor of HCTree
HCTree::~HCTree(){
  deleteAll(root);
}

/* method to build a HCTree
 * take as param a vector containing frequencies
 */
void HCTree::build(const vector<int> & freqs){
  //create priority queue of HCNode pointers
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> queue;

  for(int i = 0; i < freqs.size(); i++){//for each symbol in freqs
    if(freqs[i] != 0){
      HCNode* newNode = new HCNode(freqs[i], i);//create a node new node for that symbol
      leaves[i] = newNode;//add the node to leaves
      queue.push(newNode);//push it into priority queue
    }
  }

  while(queue.size()!= 1){// while queue is not empty
    //use top 2 trees in queue to create a new tree
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
    //push the tree back into the queue
    queue.push(parent);
  }
  //set root to the root node of the final tree
  root = queue.top();
}

/* method that takes as param symbol that is a byte that stores some data
 * and a param out that is a type of ouput stream that we will write to.
 * The method encodes the data in symbol and writes it to output.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  HCNode* temp = leaves[symbol];// let temp be the leaf node containing the sybol
  string toWrite; //create string
  //While temp has a prent, we write 0 if temp is c0 child and 1 otherwise
  while(temp->p != NULL){
    if(temp->p->c0==temp){
      toWrite = '0'+ toWrite;
    }else if(temp->p->c1==temp){
      toWrite = '1'+toWrite;
    }
    temp = temp->p;//let temp move up the tree and repeat
  }
  for(int i=0; i<toWrite.size();i++){
    out.writeBit(toWrite[i]=='1'); //output a bit at a time
  }
}

/* method that takes as param symbol that is a byte that stores some data
 * and a param out that is a type of ouput stream that we will write to.
 * The method encodes the data in symbol and writes it to out.
 */
void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode* temp = leaves[symbol];// let temp be the leaf node containing the sybol 
  string toWrite; //create string
  //While temp has a prent, we write 0 if temp is c0 child and 1 otherwise
  while(temp->p != NULL){ 
    if(temp->p->c0==temp){
      toWrite = '0'+ toWrite;
    }else if(temp->p->c1==temp){
      toWrite = '1'+toWrite;
    }
    temp = temp->p;//let temp move up the tree and repeat
  }
  out<<toWrite; //output formatted data
}

int HCTree::decode(BitInputStream& in) const{
  int symbol;// a bit of data
  HCNode* curr = root;//set curr to root
  //while the cur has any child
  while(curr->c0 || curr->c1){
    symbol =in.readBit();// read data from input stream
    //go down the tree according to the data
    if(symbol== 0){
      curr= curr->c0;
    }else if(symbol == 1){
      curr = curr->c1;
    }
  }
  //return the symbol in leaf child
  return curr->symbol;
}

/* This method takes param an input stream and us it to read data
 * Then decode this data and return it
 */
int HCTree::decode(ifstream& in) const{
  byte symbol;// a byte of data
  HCNode* curr = root;//set curr to root
  //while the cur has any child
  while(curr->c0 != NULL || curr->c1 != NULL){
    symbol =(byte) in.get();// read data from input stream
    //go down the tree according to the data
    if(symbol=='0'){
      curr= curr->c0;
    }else if(symbol =='1'){
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
