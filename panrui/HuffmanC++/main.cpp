#include "GenerateHuffmanTree.h"

int main()
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree("D:\\dudu.txt");
	MapOfTree * map_t;
	huffman->GenerateStart(map_t);
	return false;
}