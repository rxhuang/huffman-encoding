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


  infile.seekg(0, ios::beg);
  outfile.open(argv[2], ios::binary);

  //2. Read the file header at the beginning of the input file,
  //and reconstruct the Huffman coding tree.
  for (int i = 0; i < freq.size(); i++){
    getline(infile,str);
    freq[i] = stoi(str);
    size += freq[i];
  }
  // build the tree
  HCTree tree;
  tree.build(freq);

  //4. Using the Huffman coding tree, decode the bits from the input file
  //into the appropriate sequence of bytes, writing them to the output file
  for (int x = 0; x < size; x++){
    b = tree.decode(infile);
    outfile <<b;
  }
  //5. Close the input and output files.
  outfile.close();
  infile.close();

  return 0;
}
