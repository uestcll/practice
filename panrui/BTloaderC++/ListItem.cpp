#include "ListItem.h"
#include "GetNewItem.h"
#include "ReadCtrler.h"

ListItem::ListItem(){}
ListItem::~ListItem(){ std::cout<<"end of list\n";}

void ListItem::init()
{
	this->element_type = list_type;
	this->data.reset(GetNewItem::getNewItem());
	ReadCtrler * reader = ReadCtrler::GetInstence();
	if(!reader->tryEnd())
	{
		this->Next.reset(new ListItem);
		this->Next->init();
	}	
}