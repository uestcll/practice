#ifndef H_TREE
#define H_TREE

#include <vector>
#include <iostream>
using namespace std;

class TreeItem
{
private:
	TreeItem * lt;
	TreeItem * rt;
	unsigned long long count;
	unsigned char value;
	vector<unsigned char>::iterator it;
	vector<unsigned char> hfCode;
	TreeItem(TreeItem &);
	const TreeItem& operator = (const TreeItem &);
protected:
public:
	TreeItem(const unsigned char value,const unsigned long long count );
	TreeItem(TreeItem * lt,TreeItem * rt,const unsigned long long count );
	~TreeItem();
	inline void countAdd()
	{
		count++; 
	}

	inline const unsigned char getValue()const 
	{
		return value;
	}

	inline const unsigned long long getCount()const 
	{
		return count;
	}

	inline TreeItem * getLT()const 
	{
		return lt;
	}

	inline TreeItem * getRT()const 
	{
		return rt;
	}

	void modifyLT(TreeItem * );
	void modifyRT(TreeItem * );
	
	void setNextBit(const unsigned char next);
	void reset();
	const unsigned char getNextBit();
	bool operator<(TreeItem &)const ;
	void destroyHead(TreeItem *);

	void returnHFCode(vector<unsigned char>::iterator & begin,vector<unsigned char>::iterator & end);
	void copyHFCode(vector<unsigned char>::iterator & begin,vector<unsigned char>::iterator & end);
};

#endif
