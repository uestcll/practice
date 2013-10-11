#ifndef DECODE_HUFFMAN
#define DECODE_HUFFMAN
#include "TreeItem.h"
#include <fstream>

using namespace std;

class decodeHuffman
{
private:
	decodeHuffman(decodeHuffman &);
	const decodeHuffman & operator = (decodeHuffman &);

	string sourcePath;
	string destPath;
	fstream::pos_type originalfileLen;
	unsigned char m_left;
	unsigned char m_in;
	unsigned char m_pos;
	TreeItem * m_tree;
	bool   stopFlag;

	void getleftBitAndLen(ifstream &);
	void findOriginalFileOffset(ifstream &);
	unsigned char decodeSingalWord(ifstream & istr,TreeItem * p_tree);
	unsigned char getNextBitValue(ifstream &);

protected:
public:
	decodeHuffman(string sourcePath,string destPath,TreeItem * h_tree);
	~decodeHuffman();

	void startDecode();
};

#endif