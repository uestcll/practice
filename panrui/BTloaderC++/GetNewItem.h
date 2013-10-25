#ifndef _GET_NEW_ITEM_
#define _GET_NEW_ITEM_
#include <map>

class ItemBase;

using namespace std;
class GetNewItem
{
private:

	static map<int ,ItemBase *(*)()> f_map;

	static ItemBase * GetNewDic();
	static ItemBase * GetNewStr();
	static ItemBase * GetNewNum();
	static ItemBase * GetNewList();
	static ItemBase * ErrorDeal();
public:
	static void GetNewInit();
	static ItemBase * getNewItem();
};

#endif