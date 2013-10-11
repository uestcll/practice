#include "GenerateHuffmanTree.h"
#include "encodeHuffman.h"
#include "decodeHuffman.h"

int main()
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree("D:\\dudu.txt");
	MapOfTree * map_t;
	huffman->GenerateStart(map_t);
	encodeHuffman * encode = new  encodeHuffman("D:\\dudu.txt","D:\\pp.bin",huffman,map_t);
	encode->startEncode();
	delete huffman;
	delete encode;


	TreeItem * tree_t;
	huffman = new GenerateHuffmanTree("D:\\pp.bin");
	huffman->GenerateStart(tree_t);
	decodeHuffman * decode = new decodeHuffman("D:\\pp.bin","D:\\boom.txt",tree_t);
	decode->startDecode();

	delete huffman;
	delete decode;

	return false;
}