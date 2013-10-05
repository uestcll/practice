#include "PBsave.h"
#include <iostream>
PBsave::PBsave()
{

}

PBsave::~PBsave()
{

}

void PBsave::doSave(string path,vector<PBitem *> &pb_item)
{
	ostr = new ofstream();
	ostr->open(path,ios::binary|ios::trunc);
	
	if(!ostr->is_open())
	{
		cout<<"open file fail while saving file"<<endl;
		return ;
	}

	vector<PBitem *>::iterator it = pb_item.begin();
	while(it != pb_item.end())
	{
		*ostr<<getNewString(it)<<endl;
	}

	ostr->close();
}

string PBsave::getNewString(vector<PBitem *>::iterator &it)
{
	string outPutString = " ";
	outPutString +=(*it)->getName();
	
	outPutString += " ";
	outPutString +=(*it++)->getNum();
	
	return outPutString;
}