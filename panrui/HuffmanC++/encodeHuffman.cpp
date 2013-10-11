#include "encodeHuffman.h"

encodeHuffman::encodeHuffman(string sourcePath,string destPath,GenerateHuffmanTree *ght,MapOfTree *m_map):sourcePath(sourcePath)
	,destPath(destPath),m_ght(ght),m_out(0),m_pos(7),m_map(m_map)
{

}

encodeHuffman::~encodeHuffman()
{

}

void encodeHuffman::startEncode()
{
	ofstream ostr(destPath.c_str(),ios::binary);
	if(!ostr.is_open())
	{
		cout<<"cannot open destfile while Encoding"<<endl;
		return ;
	}	

	m_ght->SaveWordFrequency(ostr);

	startEnCodeOriginFile(ostr);

	ostr.close();
}

void encodeHuffman::startEnCodeOriginFile(ofstream &ostr)
{
	ifstream istr(sourcePath.c_str(),ios::binary);
	if(!istr.is_open())
	{
		cout<<"cannot open sourcefile while Encoding"<<endl;
		return;
	}
	while(istr.peek()!=EOF)
	{
		doSingalEncode((const unsigned char )istr.get(),ostr);
	}
	ostr.put(m_out);
	ostr.put(m_pos);
	istr.close();
}

void encodeHuffman::doSingalEncode(const unsigned char value,ofstream &ostr)
{
	TreeItem * aim = m_map->fdTreeItem( value);
	aim->reset();
	string::size_type size = aim->getSize();

	for(unsigned int i = 0; i<size;i++)
	{
		if(m_pos == 0xFF)
		{
			ostr.put(m_out);
			m_out = 0;
			m_pos = 7;
		}
		unsigned char tmp = aim->getNextBit();
		tmp<<=m_pos;
		m_out|=tmp;
		m_pos--;
	}
}