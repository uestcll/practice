#ifndef _DICTIONARY_ITEM_
#define _DICTIONARY_ITEM_

#include "ItemBase.h"
#include <memory>

using namespace std;
class DicItem:public ItemBase
{
private:
	DicItem (const DicItem &);
	const DicItem & operator = ( const DicItem &);
	
	tr1::shared_ptr<ItemBase> firData;
	tr1::shared_ptr<ItemBase> secData;

	tr1::shared_ptr<ItemBase> Next;
	
public:
	virtual void init();
	explicit DicItem(void );
	virtual ~DicItem(void );
};

#endif