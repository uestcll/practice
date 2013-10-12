#ifndef HUFFMAN_EXECUTE
#define HUFFMAN_EXECUTE
#include "CommandDispatcher.h"
#include "GenerateHuffmanTree.h"
#include "encodeHuffman.h"
#include "decodeHuffman.h"
#include "CmdExecute.h"
#include <map>
#include <string>
using namespace std;
class HuffmanExecute:public CmdExecute
{
private:
	HuffmanExecute(const HuffmanExecute &);
	const HuffmanExecute & operator = (const HuffmanExecute &);

	string source;
	string dest;
	map<unsigned int ,void (*)(HuffmanExecute *)> f_map; 

	const static unsigned int Usage = 3;
	const static unsigned int Compress = 2;
	const static unsigned int Decompress = 1;
public:
	HuffmanExecute(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum);
	~HuffmanExecute();
	virtual void startExecute();
	void initFeature();
	static void doUsage(HuffmanExecute *);
	static void doCompress(HuffmanExecute *);
	static void doDecompress(HuffmanExecute *);
};
#endif
