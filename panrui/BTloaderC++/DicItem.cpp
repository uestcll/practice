#include "DicItem.h"
#include "GetNewItem.h"
#include "ReadCtrler.h"
DicItem::DicItem(){}
DicItem::~DicItem(){std::cout<<"end of dic\n";}

void DicItem::init()
{
	this->element_type = dic_type;
	this->firData.reset(GetNewItem::getNewItem());
	this->secData.reset(GetNewItem::getNewItem());

	ReadCtrler * reader = ReadCtrler::GetInstence();
	if(!reader->tryEnd())
	{
		this->Next.reset(new DicItem);
		this->Next->init();
	}
}