#include "NumItem.h"
#include "GetNewItem.h"
#include "ReadCtrler.h"

NumItem::NumItem():data(0){}
NumItem::~NumItem(){};
void NumItem::init()
{
	this->element_type = num_type;

	ReadCtrler * reader = ReadCtrler::GetInstence();
	this->data = reader->GetNumber();
}

