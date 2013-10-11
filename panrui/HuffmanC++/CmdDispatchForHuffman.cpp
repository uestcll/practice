#include "CmdDispatchForHuffman.h"
#include <iostream>

using namespace std;
CmdDispatchForHuffman::CmdDispatchForHuffman(unsigned int num,...):CommandDispatcher(num),analysisRet(true)
{
	va_list ap;
	va_start(ap,num);
	if(num != 0)
		cmd = new unsigned char *[num];
	for(unsigned int i = 0;i<num;i++)
	{
		cmd[i] = va_arg(ap,unsigned char *);
	}
	va_end(ap);
}

CmdDispatchForHuffman::~CmdDispatchForHuffman()
{

}

void CmdDispatchForHuffman::paraAnalysis()
{
	if(num != 4)
	{
		analysisRet = false;
		return ;
	}
	source = (char *)cmd[2];
	dest = (char *)cmd[3];
	if(strcmp((char *)cmd[1],"-c")==0)
		this->actionType = true;
	else if(strcmp((char *)cmd[1],"-d")==0)
		this->actionType = false;
	else
		analysisRet = false;
}

bool CmdDispatchForHuffman::Dispatch()
{
	paraAnalysis();
	if(analysisRet)
	{
		Usage();
		return false;
	}

	actionType == true?compression():decompression();
	return true;
}

void CmdDispatchForHuffman::compression()
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree(source);
	MapOfTree * map_t;
	huffman->GenerateStart(map_t);
	encodeHuffman * encode = new  encodeHuffman(source,dest,huffman,map_t);
	encode->startEncode();

	delete huffman;
	delete encode;
}
void CmdDispatchForHuffman::decompression()
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree(source);
	TreeItem * tree_t;
	huffman->GenerateStart(tree_t);
	decodeHuffman * decode = new decodeHuffman(source,dest,tree_t);
	decode->startDecode();

	delete huffman;
	delete decode;
}

void CmdDispatchForHuffman::Usage()
{
	cout<<"Usage:"<<endl;
	cout<<"-c [filename] [compressed filename]"<<endl;
	cout<<"-d [compressed filename] [filename]"<<endl;
}