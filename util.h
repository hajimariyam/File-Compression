//
// STARTER CODE: util.h
//
// TODO:  Write your own header
//

#pragma once

// TODO: includes go here

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

// Binary tree node
struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;      // left
    HuffmanNode* one;       // right
};

// Comparison function for priority queue to sort upon insertion
struct compare
{
    bool operator()(const HuffmanNode *lhs,
        const HuffmanNode *rhs)
    {
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
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF &map) {
    
    // TO DO:  Write this function here.
    
    return nullptr;  // TO DO: update this return
}

//
// *Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str,
                       HuffmanNode* prev) {
    
    // TO DO:  Write this function here.
    
}

//
// *This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;
    
    // TO DO:  Write this function here.
    
    return encodingMap;  // TO DO: update this return
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
