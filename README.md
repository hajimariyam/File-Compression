# File Compression

This C++ program allows a user to compress and decompress files using the standard Huffman algorithm for encoding and decoding. The algorithm is implemented using binary trees, priority queues, and a custom hashmap class.

## Huffman Encoding

Huffman encoding is an algorithm devised by David A. Huffman of MIT in 1952 for compressing textual data to make a file occupy a smaller number of bytes. It abandons the 8-bits-per-character ASCII encoding and instead uses binary encodings of different lengths for different characters. Frequent characters such as space and 'e' have shorter encodings (fewer bits), making the overall file smaller, while infrequently occuring characters like 'z' have longer encodings (more bits). The tradeoff is that some rare characters may need to use encodings that are longer than 8 bits, but on the balance, the extra cost is worth it.

This lossless compression algorithm works particularly well on text but it can be applied to any type of file, potentially reducing the required file storage by a third, half, or even more. Though it is a relatively simple compression algorithm, Huffman is powerful enough that variations of it are still used today in computer networks, fax machines, modems, HDTV, and other areas.

## How To Use

<img src='https://github.com/hajimariyam/File-Compression/blob/main/gif2.gif' width='65%' />

The menu options 1-6 are for debugging purposes and represent the steps used to perform a Huffman encoding of a given text source file into a destination compressed file and vice versa.

**COMPRESSION:**
1) Choose menu option C
2) Enter the file name, for example: myfile.txt
3) Find the compressed file saved as myfile.txt.huf
4) Use menu option B to view the binary compressed file

**DECOMPRESSION:**
1) Choose menu option D
2) Enter the file name, for example: myfile.txt.huf
3) Find the decompressed file saved as myfile_unc.txt
4) Use menu option T to view the decompressed text file


