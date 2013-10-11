#ifndef CMD_DISPATCH_FOR_HUFFMAN
#define CMD_DISPATCH_FOR_HUFFMAN
#include "CommandDispatcher.h"
#include "GenerateHuffmanTree.h"
#include "encodeHuffman.h"
#include "decodeHuffman.h"
class CmdDispatchForHuffman:public  CommandDispatcher
{
private:
	CmdDispatchForHuffman(const CmdDispatchForHuffman &);
	const CmdDispatchForHuffman & operator = (const CmdDispatchForHuffman &);

	string source;
	string dest;
	bool actionType;
	bool analysisRet;

	void compression();
	void decompression();
	void Usage();
protected:
	virtual void paraAnalysis();
public:
	CmdDispatchForHuffman(unsigned int num,...);
	~CmdDispatchForHuffman();
	virtual bool Dispatch();
};

#endif