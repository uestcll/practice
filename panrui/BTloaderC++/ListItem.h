#ifndef _LIST_ITEM_
#define _LIST_ITEM_
#include "ItemBase.h"
#include <memory>

using namespace std;
class ListItem:public ItemBase
{
private:
	ListItem (const ListItem &);
	const ListItem & operator = ( const ListItem &);
	
	tr1::shared_ptr<ItemBase> data;
	tr1::shared_ptr<ItemBase> Next;
	
public:
	virtual void init();
	explicit ListItem(void );
	virtual ~ListItem(void );
};

#endif
