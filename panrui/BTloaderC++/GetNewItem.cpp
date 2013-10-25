#include "GetNewItem.h"
#include "ItemBase.h"
#include "DicItem.h"
#include "ListItem.h"
#include "NumItem.h"
#include "StrItem.h"
#include "ReadCtrler.h"

map<int ,ItemBase *(*)()> GetNewItem::f_map;

void GetNewItem::GetNewInit()
{
	f_map.insert(pair<int,ItemBase *(*)()>(ItemBase::dic_type,GetNewDic));
	f_map.insert(pair<int,ItemBase *(*)()>(ItemBase::list_type,GetNewList));
	f_map.insert(pair<int,ItemBase *(*)()>(ItemBase::str_type,GetNewStr));
	f_map.insert(pair<int,ItemBase *(*)()>(ItemBase::num_type,GetNewNum));
	f_map.insert(pair<int,ItemBase *(*)()>(ItemBase::end_type,ErrorDeal));
}

ItemBase * GetNewItem::getNewItem()
{
	ReadCtrler * reader = ReadCtrler::GetInstence();
	return	f_map.find(reader->GetNextType())->second();
}

ItemBase * GetNewItem::GetNewDic()
{
	DicItem * n_dic = new DicItem;
	n_dic->init();
	return n_dic;
}

ItemBase * GetNewItem::GetNewList()
{
	ListItem * n_list = new ListItem;
	n_list->init();
	return n_list;
}

ItemBase * GetNewItem::GetNewStr()
{
	StrItem * n_str = new StrItem;
	n_str->init();
	return n_str;
}

ItemBase * GetNewItem::GetNewNum()
{
	NumItem * n_num = new NumItem;
	n_num->init();
	return n_num;
}

ItemBase * GetNewItem::ErrorDeal()
{
	exit(0);
}