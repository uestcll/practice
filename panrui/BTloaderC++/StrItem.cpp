#include "StrItem.h"
#include "GetNewItem.h"
#include "ReadCtrler.h"

StrItem::StrItem():len(0)
{}
StrItem::~StrItem(){std::cout<<"end of str\n";};
void StrItem::init()
{
	ReadCtrler * reader = ReadCtrler::GetInstence();
	this->element_type = str_type;
	this->len = reader->GetNumber();
	this->str = reader->GetString(len);
}