#ifndef _STRING_ITEM_
#define _STRING_ITEM_
#include "ItemBase.h"
#include <string>

using namespace std;
class StrItem:public ItemBase
{
private:
	StrItem (const StrItem &);
	const StrItem & operator = ( const StrItem &);
	
	string str;
	unsigned long int len;
	
public:
	virtual void init();
	explicit StrItem(void );
	virtual ~StrItem(void );
};
#endif