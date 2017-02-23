/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: unpresses a file and stores in another file
   Assignment number: 3
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "HCTree.h"
using namespace std;

int main(int argc, char*argv[]){

  if (argc != 3) {
    cout << "Invalid number of arguments" << endl;
    return -1;
  }

  ofstream outfile;
  ifstream infile;
  int size = 0;
  byte b;
  string str;
  vector<int> freq(256, 0);

  //1. Open the input file for reading.
  infile.open(argv[1], ios::binary);
  infile.seekg(0, ios::end);
  if(infile.tellg()==0){
    infile.close();
    cout<<"nothing to uncompress"<<endl;
    exit(-1);
  }

  //2. Read the file header at the beginning of the input file,
  //and reconstruct the Huffman coding tree.
  infile.seekg(0, ios::beg);
  BitInputStream bin(infile);

  for (int i = 0; i < freq.size(); i++){	
    int temp = 0;
    for(int j=1; j<=32; j++){
      temp |= bin.readBit();
      temp <<= 1;
    }
    freq[i] = temp;
    size += temp;
  }
 
  //3. build the tree and open the output file for writing
  HCTree tree;
  tree.build(freq);
  outfile.open(argv[2], ios::binary);

  //4. Using the Huffman coding tree, decode the bits from the input file
  //into the appropriate sequence of bytes, writing them to the output file
  for (int x = 0; x < size; x++){
    b = tree.decode(bin);
    outfile << b;
  }
  //5. Close the input and output files.
  outfile.close();
  infile.close();

  return 0;
}
