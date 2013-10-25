#include "ListItem.h"
#include "GetNewItem.h"
#include "ReadCtrler.h"

ListItem::ListItem(){}
ListItem::~ListItem(){}

void ListItem::init()
{
	this->element_type = list_type;
	this->data.reset(GetNewItem::getNewItem());
	ReadCtrler * reader = ReadCtrler::GetInstence();
	if(!reader->tryEnd())
	{
		this->Next.reset(GetNewItem::getNewItem());
	}	
}