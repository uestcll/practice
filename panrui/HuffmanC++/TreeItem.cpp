#include "TreeItem.h"

TreeItem::TreeItem(unsigned char value,const unsigned long long count ):lt(NULL),rt(NULL),count(count),value(value)
{
	
}

TreeItem::TreeItem(TreeItem * lt,TreeItem * rt,const unsigned long long count ):lt(lt),rt(rt),count(count),value(0)
{

}

TreeItem::~TreeItem()
{
	if(hfCode.size() != 0)
	{
		hfCode.clear();
	}

}

void TreeItem::modifyLT(TreeItem * h_tree)
{
	this->lt = h_tree;
}

void TreeItem::modifyRT(TreeItem *  h_tree)
{
	this->rt = h_tree;
}

void TreeItem::setNextBit(const unsigned char next)
{
	this->hfCode.push_back(next);
}

void TreeItem::reset()
{
	this->it = this->hfCode.begin();
}

const unsigned char TreeItem::getNextBit()
{
	if(it!=hfCode.end())
		return *it++;
	else
		return 0xFF;
}

bool TreeItem::operator<(TreeItem & sec)const
{
	return count<sec.getCount();
}

void TreeItem::destroyHead(TreeItem * p_tree)
{
	if(p_tree->getLT()!=NULL)
		destroyHead(p_tree->getLT());
	if(p_tree->getRT()!=NULL)
		destroyHead(p_tree->getRT());
	delete p_tree;
}

void TreeItem::returnHFCode(vector<unsigned char>::iterator & begin,vector<unsigned char>::iterator & end)
{
	begin = hfCode.begin();
	end = hfCode.end();
}

void TreeItem::copyHFCode(vector<unsigned char>::iterator & begin,vector<unsigned char>::iterator & end)
{
	hfCode.assign(begin,end);
}

string::size_type TreeItem::getSize()
{
	return hfCode.size();
}