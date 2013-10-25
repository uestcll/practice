#include "ReadCtrler.h"
#include <iostream>
#include "ItemBase.h"

bool ReadCtrler::has_a = false;
ReadCtrler * ReadCtrler::reader = NULL;
string ReadCtrler::path = "";

ReadCtrler::ReadCtrler()
{
	try{
		has_a = true;
		if(path == "")
			throw "should set path before open the file";
		istr.open(path.c_str(),ios::binary);
		if(!istr.is_open())
			throw "open file error";
	}catch(string err)
	{
		cout<<err<<endl;
		exit(-1);
	}
}
ReadCtrler::~ReadCtrler()
{
	istr.close();
}

void ReadCtrler::SetPath(string &filepath)
{
	path = filepath;
}

ReadCtrler * ReadCtrler::GetInstence()
{
	if(!has_a)
		reader = new ReadCtrler;
		return reader;
}

int ReadCtrler::GetNextType()
{
	char Next = istr.get();
	if(Next >= '0'&&Next <= '9')
	{
		istr.seekg(-1,ios::cur);
		return ItemBase::str_type;
	}
	else if(Next == 'i')
		return ItemBase::num_type;
	else if(Next == 'd')
		return ItemBase::dic_type;
	else if(Next == 'l')
		return ItemBase::list_type;
	else if(Next == 'e')
		return ItemBase::end_type;
	else
	{
		cout<<"unrecognized synbol"<<endl;
		return ItemBase::end_type;
	}
}

string ReadCtrler::GetString(unsigned long len)
{
	char * buffer = new char[len+1];
	buffer[len] = 0;

	istr.read(buffer,len);
	string retStr = buffer;
	delete []buffer;
	return retStr;
}

unsigned long ReadCtrler::GetNumber()
{
	unsigned long  retValue = 0;
	unsigned long  weight = 100000000;
	char CurNum = 0;
	int  step = 9;
	while(true)
	{
		CurNum = istr.get();
		if(CurNum >'9'||CurNum<'0')
			break;
		retValue += weight * (CurNum - '0');
		weight /= 10;
		step --;
		if(step == -1)
		{
			retValue *= 10;
			retValue += CurNum - '0';
			step = 0;

		}
	}

	while(step--)
	{
		retValue /=10;
	}
	
	return retValue;	
}

bool ReadCtrler::tryEnd()
{
	char is_end = istr.get();
	if(is_end == 'e')
		return true;
	else
		istr.seekg(-1,ios::cur);
	return false;
}