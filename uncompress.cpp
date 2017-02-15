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

  ofstream output;
  ifstream input;
  int size = 0;
  byte b = 0;
  string str;

  vector<int> freq(256, 0);

  //1. Open the input file for reading.
  input.open(argv[1], ios::binary);


  input.seekg(0, ios::beg);
  output.open(argv[2], ios::binary);

  //2. Read the file header at the beginning of the input file,
  //and reconstruct the Huffman coding tree.
  for (int i = 0; i < freq.size(); i++){
    input.read((char*)&freq[i], sizeof(int));
    size += freq[i];
  }

  HCTree tree;
  tree.build(freq);


  //find the begining of the file past the header
  //input.seekg(ios::beg+(256*sizeof(int)));
  //4. Using the Huffman coding tree, decode the bits from the input file
  //into the appropriate sequence of bytes, writing them to the output file
  for (int x = 0; x < size; x++){
    b = tree.decode(input);
    output.write((char*)&b, 1);
  }

  //5. Close the input and output files.
  output.close();
  input.close();

  return 0;
}
