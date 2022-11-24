//
// STARTER CODE: util.h
//
// TODO:  Write your own header
//

#pragma once

// TODO: includes go here
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
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
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
// *This function builds an encoding tree from the frequency map;
// assume it is valid: 
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
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str, HuffmanNode* prev)
{
    // Base case
    if (node == nullptr) {
        return;
    }
    // Pre-order recursion: operation, left, right
    else {
        // Search for leaf node
        if (node->character != NOT_A_CHAR) {	
            encodingMap.emplace(node->character, str);
            return;
        }
        // Each left branch is a bit value of 0 
        _buildEncodingMap(node->zero, encodingMap, str+"0", prev);
        // Each right branch is a bit value of 1
        _buildEncodingMap(node->one, encodingMap, str+"1", prev);
    }
}

//
// *This function builds the encoding map from a Huffman encoding tree
// Function parameter is a pointer to the root node of the tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) 
{
    hashmapE encodingMap;           // key: character as ASCII, value: binary encoding of character
    string str = "";                // stores the binary representation of a character
    HuffmanNode* prev = nullptr;    // provided, unused
    
    // Traverse the binary tree to discover the binary encodings of each character
    _buildEncodingMap(tree, encodingMap, str, prev);
    
    return encodingMap;
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}

//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}

//
// *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    
    // TO DO:  Write this function here.
    
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
//
string decompress(string filename) {
    
    // TO DO:  Write this function here.
    
    return "";  // TO DO: update this return
}
