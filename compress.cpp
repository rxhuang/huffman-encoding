/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 15
   Overview: compresses a file store in another file
   Assignment number: 3
*/

#include <iostream>
#include <fstream>
#include "HCTree.h"
using namespace std;
int main (int argc, char*argv[]){
  //check if number of arguements are correct
  if(argc != 3){
    cout << "Invalid number of arguments" << endl;
    return -1;
  }

  // 1.Open the input file for reading.
  ifstream infile(argv[1], ios::binary);
  ofstream outfile(argv[2], ios::binary);
  int size=0; //size of file
  byte byte;  //used to read information from input file
  vector<int> freq(256,0); //frequencies of each ascii character

  //check for empty file
  infile.seekg(0, ios::end);
  if(infile.tellg()==0){
    infile.close();
    outfile.close();
    cout<<"empty file"<<endl;
    return 0;
  }

  // 2.Read bytes from the file. Count the number of occurrences of each byte value. Close the file.
  infile.seekg(0, ios::beg);
  byte = infile.get();
  while(!infile.eof()){
    freq[byte]++;
    size++;
    byte = infile.get();
  }

  //  3. Use the byte counts to construct a Huffman coding tree. Each unique byte with a non-zero
  // count will be a leaf node in the Huffman tree.
  HCTree tree;
  tree.build(freq);

  // 4. Open the output file for writing. Done via constructor
  BitOutputStream boutfile(outfile);
 
  // 5. Write enough information (a "file header") to the output file to enable the coding tree to be 
  //reconstructed when the file is read by your uncompress program. 
  for(int i=0; i < freq.size(); i++){
    //to compress, we write only 24 bits to bit out stream for an int, instead of writing whole 32 bits 
    for(int j=1; j<=24; j++){
      boutfile.writeBit(freq[i]>>(24-j));
    }
  }

  // 6.Open the input file for reading, again.
  infile.clear();
  infile.seekg(0, ios::beg);

  //7. Using the Huffman coding tree, translate each byte from the input file into its code, and append these codes as a sequence of bits to the output file, after the header.
  for (int j = 0; j < size; j++){
    byte = infile.get();
    tree.encode(byte,boutfile);
  }
  boutfile.flush();
  
  // 8. Close the input and output files.
  outfile.close();
  infile.close();

  return 0;
}
