#include "GenerateHuffmanTree.h"
#include "encodeHuffman.h"

int main()
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree("D:\\HUFFMAN.mp4");
	MapOfTree * map_t;
	huffman->GenerateStart(map_t);
	encodeHuffman * encode = new  encodeHuffman("D:\\HUFFMAN.mp4","D:\\pp.bin",huffman,map_t);
	encode->startEncode();

	delete huffman;
	delete encode;
	return false;
}