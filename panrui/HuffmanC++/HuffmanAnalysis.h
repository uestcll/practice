#ifndef HUFFMAN_ANALYSIS
#define HUFFMAN_ANALYSIS
#include "CmdAnalysis.h"
class HuffmanAnalysis:public CmdAnalysis
{
private:
	HuffmanAnalysis(const HuffmanAnalysis &);
	const HuffmanAnalysis & operator = (const HuffmanAnalysis &);
	const static unsigned int Usage = 3;
	const static unsigned int Compress = 2;
	const static unsigned int Decompress = 1;
public:
	HuffmanAnalysis(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum);
	~HuffmanAnalysis();

	virtual void startAnalysis();


};


#endif
