//
// util.h
//
// Project: File Compression
// Author: Mariyam Haji
// System: Visual Studio Code with Ubuntu (WSL 2) on Windows 10
//
// This is a file compression algorithm that uses binary trees, priority queues, 
// and a custom hashmap class to allow file compression and decompression 
// using the standard Huffman algorithm for encoding and decoding.
//
//

#pragma once

#include "bitstream.h"
#include "hashmap.h"
#include "mainprog.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

// Binary tree node
struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;      // left child
    HuffmanNode* one;       // right child
};

// Comparison functor for priority queue to sort upon insertion
struct compare
{
    bool operator()(const HuffmanNode *lhs,
        const HuffmanNode *rhs)
    {
        // Smaller counts have higher priority
        return lhs->count > rhs->count;
    }
};

//
// *Helper function for buildFrequencyMap()
// Character is passed in as type int for ASCII conversion
//
void countFrequency (hashmapF &map, int c)
{
    if (map.containsKey(c)) {
        int currValue = map.get(c);
        map.put(c, currValue + 1);
    }
    else {
        map.put(c, 1);
    }
}

//
// *This function build the frequency map. If isFile is true, then it reads
// from filename. If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) 
{ 
    // Read from filename file (assume it exists and can be read)
    // Map each character ASCII (key) to the number of times it appears (value)
    if (isFile) 
    {
        ifstream inFS(filename);
        char c;

        while (inFS.get(c)) {
            countFrequency(map, c);
        }
    }

    // Read from filename string
    // Map each character ASCII (key) to the number of times it appears (value)
    else {
        for (char c: filename) {
            countFrequency(map, c);
        }
    }

    // Add a single occurrence of the fake character PSEUDO_EOF into the map
    map.put(PSEUDO_EOF, 1);
}

//
// *This function builds an encoding tree from the frequency map.
// Assume the frequency map is valid: 
//  1) does not contain any keys other than char values, PSEUDO_EOF, and NOT_A_CHAR
//  2) all counts are positive integers
//  3) contains at least one key/value pairing
//
HuffmanNode* buildEncodingTree(hashmapF &map) 
{
    // Use priority queue to keep track of which nodes to process next 
    //  based on priority defined by compare functor
    priority_queue < HuffmanNode*, vector<HuffmanNode*>, compare > pq;

    // For each key(character)-value(count) pair in frequency map..
    vector<int> keysInFreqMap = map.keys();
    for (int key : keysInFreqMap) 
    {
        int value = map.get(key);

        // Create new node
        HuffmanNode* newNode = new HuffmanNode();
        newNode->character = key;
        newNode->count = value;
        
        // Insert new node into priority queue
        pq.push(newNode);
    }

    // Construct encoding tree
    // Until 1 binary tree node remains, where other nodes are its children..
    while (pq.size() > 1) 
    {
        // Remove 2 nodes from the front of the queue (smallest counts)
        HuffmanNode* first = pq.top();
        pq.pop();
        HuffmanNode* second = pq.top();
        pq.pop();

        // Join the 2 nodes into a new joint node
        HuffmanNode* jointNode = new HuffmanNode();
        jointNode->character = NOT_A_CHAR;
        jointNode->count = first->count + second->count;

        // Position the 2 nodes as children of the joint node
        jointNode->zero = first;        // left child
        jointNode->one = second;        // right child

        // Insert joint node into queue (sorted by compare functor upon insertion)
        pq.push(jointNode);
    }

    // Remaining node is the root of the finished Huffman encoding tree
    return pq.top();
}

//
// *Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string binaryString, HuffmanNode* prev)
{
    // Base case
    if (node == nullptr) {
        return;
    }
    // Pre-order traversal: operation, left, right
    else {
        // Search for leaf node
        if (node->character != NOT_A_CHAR) {	
            encodingMap.emplace(node->character, binaryString);
            return;
        }
        // Each left branch is a bit value of 0 
        _buildEncodingMap(node->zero, encodingMap, binaryString+"0", prev);
        // Each right branch is a bit value of 1
        _buildEncodingMap(node->one, encodingMap, binaryString+"1", prev);
    }
}

//
// *This function builds the encoding map from a Huffman encoding tree
// Function parameter is a pointer to the root node of the tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) 
{
    hashmapE encodingMap;               // key: character as ASCII, value: binary encoding of character
    string binaryString = "";           // stores the binary representation of a character
    HuffmanNode* prev = nullptr;        // provided, unused
    
    // Traverse the binary tree to discover the binary encodings of each character
    _buildEncodingMap(tree, encodingMap, binaryString, prev);
    
    return encodingMap;
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap. This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference. This function also returns a string representation of
// the output file, which is particularly useful for testing.
// Assume encoding map, input stream, output stream parameters are valid.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output, int &size, bool makeFile)
{
    int numOfBits = 0;              // Total number of bits written to the output stream
    char c;                         // A character in the source file
    string binaryString = "";       // String representation of the bits 

    // For each character from the input stream (source file)..
    while (input.get(c)) 
    {
        // For each bit (0 or 1) in the binary encoding of the character..
        for (char bit : encodingMap.at(c)) 
        {
            // Write the bit to: 1) the output stream (destination file), 2) the string of bits
            if (makeFile) {
                // May also use character arithmetic instead of if/else
                if (bit == '0') {
                    output.writeBit(0);
                }
                else if (bit == '1') {
                    output.writeBit(1);
                }
            }
            binaryString += bit;
            numOfBits++;
        }
    }

    // Write a single occurrence of the binary encoding for PSEUDO_EOF
    for (char bit : encodingMap.at(PSEUDO_EOF)) 
    {
        if (makeFile) {
            if (bit == '0') {
                output.writeBit(0);
            }
            else if (bit == '1') {
                output.writeBit(1);
            }
        }
        binaryString += bit;
        numOfBits++;
    }

    size = numOfBits;

    // Return the string representation of the encoded text
    return binaryString;
}

//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree. This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) 
{
    HuffmanNode* curr = encodingTree;       // Initiate traversal at the root node
    string textString = "";                 // String representation of the characters

    // For each bit from the input stream (source file)..
    while (!input.eof())
    {
        int bit = input.readBit();

        // Traverse the Huffman tree based on the bit value
        if (bit == 0) {
            curr = curr->zero;
        }
        else if (bit == 1) {
            curr = curr->one;
        }

        // If this is a leaf node..
        if (curr->character != NOT_A_CHAR) 
        {	
            // If the character is PSEUDO_EOF, the decoding process has concluded
            if (curr->character == PSEUDO_EOF) {
                break;
            }
            
            // Else, write the character/byte to: 1) the output stream (destination file), 
            //                                    2) the string of characters
            output.put(curr->character);
            textString += curr->character;

            // Initiate traversal for next character at the root node 
            curr = encodingTree;
        }
    }

    // Return the string representation of the decoded characters
    return textString;
}

//
// *Recursive helper function for freeing the Huffman encoding tree.
//
void _freeTree (HuffmanNode* node)
{
    // Base case
    if (node == nullptr) {
        return;
    }

    // Post-order traversal: left, right, operation
    _freeTree (node->zero);
    _freeTree (node->one);
    delete (node);
}

//
// *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) 
{
    // Post-order tree traversal using recursion
    _freeTree(node);
}

//
// *This function completes the entire compression process. Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file). This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) 
{
    hashmapF frequencyMap;
    HuffmanNode* encodingTree = nullptr;
    hashmapE encodingMap;
    bool isFile = true;

    // Build frequency map
    buildFrequencyMap(filename, isFile, frequencyMap);

    // Build encoding tree
    encodingTree = buildEncodingTree(frequencyMap);

    // Build encoding map
    encodingMap = buildEncodingMap(encodingTree);
    
    // Prepare an output bit stream to a new .huf file
    ofbitstream output(filename + ".huf");

    // Output the frequency map to the ofbitstream (file)
    output << frequencyMap;    
    
    // Prepare an input stream from the original filename
    ifstream input(filename);

    // Encode text
    int size = 0;
    string binaryString = encode(input, encodingMap, output, size, true);
    
    // Free the encoding tree
    freeTree(encodingTree);
    
    // Return a string representation of the bit pattern
    return binaryString;
}

//
// *This function completes the entire decompression process. Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file. This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt". The function should return a string version of the
// uncompressed file. Note: this function should reverse what the compress
// function did.
//
string decompress(string filename) 
{
    // Prepare an input bit stream from the .huf file given
	ifbitstream input(filename);

    // Prepare an output stream to a new file
    size_t pos = filename.find(".huf");
    if ((int)pos >= 0) {
        filename = filename.substr(0, pos);
    }
    pos = filename.find(".");
    string ext = filename.substr(pos, filename.length() - pos);
    filename = filename.substr(0, pos);
    ofstream output(filename + "_unc" + ext);

    // Build frequency map from the ifbitstream
    hashmapF frequencyMap;
    input >> frequencyMap;

    // Build encoding tree
    HuffmanNode* encodingTree = nullptr;  
    encodingTree = buildEncodingTree(frequencyMap); 

    // Decode text
    string textString  = decode(input, encodingTree, output);

    // Free the encoding tree
    freeTree(encodingTree);

    // Return a string representation of the uncompressed file
    return textString;
}
