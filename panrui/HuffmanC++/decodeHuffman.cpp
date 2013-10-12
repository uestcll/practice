#include "decodeHuffman.h"

decodeHuffman::decodeHuffman(string sourcePath,string destPath,TreeItem * h_tree):sourcePath(sourcePath),
	destPath(destPath),m_tree(h_tree),m_left(0),m_in(0),m_pos(7),stopFlag(false),originalfileLen(0)
{

}

decodeHuffman::~decodeHuffman()
{

}

void decodeHuffman::getleftBitAndLen(ifstream &istr)
{
	istr.seekg(-1,ios::end);
	originalfileLen = istr.tellg();

	m_left =istr.get();
	
	istr.seekg(0,ios::beg);
}

void decodeHuffman::findOriginalFileOffset(ifstream &istr)
{
	string::size_type size;
	istr.read((char *)&size,sizeof(size ));

	istr.seekg(size*(sizeof(unsigned char )+sizeof(unsigned long long )),ios::cur);
}

unsigned char decodeHuffman::decodeSingalWord(ifstream &istr,TreeItem * p_tree)
{
	if(p_tree->getRT() == NULL)
		return p_tree->getValue();
	unsigned char Next = getNextBitValue(istr);
	if(Next != 0)
		return decodeSingalWord(istr,p_tree->getRT());
	else
		return decodeSingalWord(istr,p_tree->getLT());
}

unsigned char decodeHuffman::getNextBitValue(ifstream &istr)
{
	if(m_pos == 0xFF||m_pos == 7)
	{
		m_in = istr.get();
		m_pos = 7;
	}
	unsigned char ans = 1;
	ans<<= m_pos;
	ans &= m_in;
	m_pos--;

	if(m_pos == m_left && istr.tellg() == originalfileLen )
		stopFlag = true;

	return ans;

}

void decodeHuffman::startDecode()
{
	ifstream istr(sourcePath.c_str(),ios::binary);
	ofstream ostr(destPath.c_str(),ios::binary);

	getleftBitAndLen(istr);
	findOriginalFileOffset(istr);
	
	while(!stopFlag)
	{
	ostr.put(decodeSingalWord(istr,m_tree));
	}

	istr.close();
	ostr.close();
}
