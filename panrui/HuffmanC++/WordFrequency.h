#ifndef WORD_FREQUENCY
#define WORD_FREQUENCY
#include <map>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class WordFrequency
{
private:
	WordFrequency(const WordFrequency &);
	const WordFrequency & operator =(const WordFrequency & );

	map<unsigned char,unsigned long long> wd_freq;
	map<unsigned char,unsigned long long>::iterator it;
	string filepath;

	void doCountingForSingalWord(unsigned char value);

public:
	WordFrequency(string filepath);
	~WordFrequency();

	bool startCounting();

	inline void reset()
	{
		it = wd_freq.begin();
	}

	inline map<unsigned char,unsigned long long>::size_type getSize()
	{
		return wd_freq.size();
	}

	inline pair<unsigned char,unsigned long long> getPair()
	{
		return (*it++);
	}
};


#endif