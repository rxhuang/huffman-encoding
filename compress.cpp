#include <iostream>
#include <fstream>
#include "HCTree.h"
using namespace std;
int main (int argc, char*argv[]){

  if(argc != 3){
    cout << "Invalid number of arguments" << endl;
    return -1;
  }

  ifstream infile;
  ofstream outfile;
  byte b;
  vector<int> freq(256,0);
  int size = 0;
  // 1.Open the input file for reading.
  infile.open(argv[1], ios::binary);

  // 2.Read bytes from the file. Count the number of occurrences of each byte value. Close the file.

  while(1){
    b = infile.get();
    if(infile.eof()) break;
    freq[b]++;
    size++;
  }

  //  3. Use the byte counts to construct a Huffman coding tree. Each unique byte with a non-zero count will be a leaf node in the Huffman tree.

  HCTree tree;
  tree.build(freq);

  // 4. Open the output file for writing.
  outfile.open(argv[2],ios::binary);

  // 5. Write enough information (a "file header") to the output file to enable the coding tree to be reconstructed when the file is read by your uncompress program. You should write the header as plain (ASCII) text for the checkpoint. See "the file header demystified" and "designing your header" for more details.

  for(int i =0; i < freq.size(); i++){
    //outfile.write((char*)&freq[i], sizeof(int));
    outfile<<freq[i] << endl;
  }

  // 6.Open the input file for reading, again.
  infile.clear();
  infile.seekg(0, ios::beg);

  //7. Using the Huffman coding tree, translate each byte from the input file into its code, and append these codes as a sequence of bits to the output file, after the header.
  for (int j = 0; j < size; j++){
    b = infile.get();
    tree.encode(b,outfile);
  }


  // 8. Close the input and output files.
  outfile.close();
  infile.close();


}
