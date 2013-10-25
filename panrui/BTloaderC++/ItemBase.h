#ifndef _ITEM_BASE_
#define _ITEM_BASE_
#include "ReadCtrler.h"

#include <iostream>

class ItemBase
{
private:
	ItemBase(const ItemBase &);
	const ItemBase & operator = (const ItemBase &);
protected:
	int element_type;
public:

	const static int num_type = 1;
	const static int str_type = 2;
	const static int dic_type = 3;
	const static int list_type = 4;
	const static int end_type = 5;

	virtual void init() = 0;
	explicit ItemBase(void );
	virtual ~ItemBase(void );
};

#endif