#include "WordFrequency.h"

void WordFrequency::doCountingForSingalWord(unsigned char value)
{
	map<unsigned char , unsigned long long >::iterator it = wd_freq.find(value);
	
	if(it == wd_freq.end())
		wd_freq.insert(pair<unsigned char ,unsigned long long >(value , 1));
	else
		it->second += 1;
}

WordFrequency::WordFrequency(string filepath):filepath(filepath)
{

}

WordFrequency::~WordFrequency()
{

}

bool WordFrequency::startCounting()
{
	ifstream istr(filepath.c_str(),ios::binary);
	if(!istr.is_open())
	{
		cout<<"open file fail while counting file"<<endl;
		return false;
	}

	while(istr.peek()!=EOF)
	{
		doCountingForSingalWord((unsigned char )istr.get());
	}

	istr.close();
	return true;

}

void WordFrequency::saveFrequencyToFile(ofstream &ostr)
{
	reset();
	int size = getSize();
	ostr<<size;
	if(it!=wd_freq.end())
	{
		ostr<<it->first<<it->second;
		it++;
	}
}

void WordFrequency::loadFrequencyFromFile(ifstream &istr)
{
	int size;
	istr>>size;

	unsigned char value;
	unsigned long long count;

	for(int i = 0;i<size;i++)
	{
		istr>>value>>count;
		wd_freq.insert(pair<unsigned char,unsigned long long>(value,count));
	}
}
