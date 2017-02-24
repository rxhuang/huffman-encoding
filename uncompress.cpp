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
  //check for correct number of args
  if (argc != 3) {
    cout << "Invalid number of arguments" << endl;
    return -1;
  }

  //1. Open the input file for reading.
  ifstream infile(argv[1], ios::binary);
  ofstream outfile(argv[2], ios::binary);
  int size = 0;
  byte byte;
  vector<int> freq(256, 0);

  //1. check for empty file
  infile.seekg(0, ios::end);
  if(infile.tellg()==0){
    infile.close();
    outfile.close();
    cout<<"empty file"<<endl;
    return 0;
  }

  //2. Read the file header at the beginning of the input file,
  //and reconstruct the Huffman coding tree.
  infile.seekg(0, ios::beg);
  BitInputStream binfile(infile);

  for (int i = 0; i < freq.size(); i++){	
    int temp = 0;
    //again we use 24 bits to store 32 bit ints for compression
    for(int j=1; j<=24; j++){
      temp |= binfile.readBit()<<(24-j);
    }
    freq[i] = temp;
    //cout<<freq[i]<<endl;
    size += temp;
  }
 
  //3. build the tree and open the output file for writing
  HCTree tree;
  tree.build(freq);

  //4. Using the Huffman coding tree, decode the bits from the input file
  //into the appropriate sequence of bytes, writing them to the output file
  for (int x = 0; x < size; x++){
    byte = tree.decode(binfile);
    outfile << byte;
  }
  //5. Close the input and output files.
  outfile.close();
  infile.close();

  return 0;
}
