#include "PBitem.h"

PBitem::PBitem()
{

}

PBitem::PBitem(string name ,string number)
{
	this ->name = name;
	this ->number = number;
}

PBitem::~PBitem()
{

}

string PBitem::getName()
{
	return name;
}

string PBitem::getNum()
{
	return number;
}

void PBitem::modifyInfo(string name,string num)
{
	this->name = name;
	this->number = number;
}