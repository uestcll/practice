#include "HuffmanExecute.h"

HuffmanExecute::HuffmanExecute(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum):CmdExecute(retValue,cmd,paraNum)
{

}

HuffmanExecute::~HuffmanExecute()
{

}

void HuffmanExecute::startExecute()
{
	initFeature();
	void (*aimFunction)(HuffmanExecute *);
	map<unsigned int,void (*)(HuffmanExecute *)>::iterator it = f_map.find(retValue);
	aimFunction = it->second;
	aimFunction(this);
}

void HuffmanExecute::initFeature()
{
	f_map.insert(pair<unsigned int,void (*)(HuffmanExecute *)>(Usage,doUsage));	
	f_map.insert(pair<unsigned int,void (*)(HuffmanExecute *)>(Compress,doCompress));
	f_map.insert(pair<unsigned int,void (*)(HuffmanExecute *)>(Decompress,doDecompress));

	this->source =(char *) cmd[2];
	this->dest = (char *) cmd[3];
	
}

void HuffmanExecute::doUsage(HuffmanExecute * aim)
{
	cout<<"Usage:"<<endl;
	cout<<"-c [filename] [compressed filename]"<<endl;
	cout<<"-d [compressed filename] [filename]"<<endl;
}

void HuffmanExecute::doCompress(HuffmanExecute * aim)
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree(aim->source);
	MapOfTree * map_t;
	huffman->GenerateStart(map_t);
	encodeHuffman * encode = new  encodeHuffman(aim->source,aim->dest,huffman,map_t);
	encode->startEncode();

	delete huffman;
	delete encode;
}

void HuffmanExecute::doDecompress(HuffmanExecute * aim)
{
	GenerateHuffmanTree * huffman = new GenerateHuffmanTree(aim->source);
	TreeItem * tree_t;
	huffman->GenerateStart(tree_t);
	decodeHuffman * decode = new decodeHuffman(aim->source,aim->dest,tree_t);
	decode->startDecode();

	delete huffman;
	delete decode;
}