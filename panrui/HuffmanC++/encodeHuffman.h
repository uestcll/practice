#ifndef ENCODE_HUFFMAN
#define ENCODE_HUFFMAN

#include "GenerateHuffmanTree.h"
#include <string>
#include <fstream>

using namespace std;


class encodeHuffman
{
private:
	encodeHuffman(encodeHuffman &);
	const encodeHuffman & operator = (const encodeHuffman &);

	string sourcePath;
	string destPath;
	GenerateHuffmanTree * m_ght;
	MapOfTree *	m_map;
	unsigned char m_out;
	unsigned char m_pos;
	void startEnCodeOriginFile(ofstream &ostr);
	void doSingalEncode(const unsigned char value,ofstream &ostr);
protected:

public:
	encodeHuffman(string sourcePath,string destPath,GenerateHuffmanTree *ght,MapOfTree *m_map);
	~encodeHuffman();

	void startEncode();
};


#endif