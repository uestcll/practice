#ifndef _NUMBER_ITEM_
#define _NUMBER_ITEM_
#include "ItemBase.h"
#include <memory>

using namespace std;
class NumItem:public ItemBase
{
private:
	NumItem (const NumItem &);
	const NumItem & operator = ( const NumItem &);
	
	unsigned long data;
	
public:
	virtual void init();
	explicit NumItem(void );
	virtual ~NumItem(void );
};

#endif