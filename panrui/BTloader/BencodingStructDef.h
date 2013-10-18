#ifndef BENCODING_STRUCT_DEF
#define BENCODING_STRUCT_DEF

#define INTERGER	1
#define STRING		2
#define LIST		3
#define ITEM		4
#define DICTIONARY	5

struct item
{
	char itemType;
	unsigned long len;
	char *data;
};
struct dictionary;
struct list
{
	char dataType;
	item * pitem;
	list * plist;
	dictionary * pdic;
	list * next;
};

struct dictionary
{
	char firType;
	char secType;

	item * fir;
	list * firl;
	dictionary * fird;

	item * sec;
	list * secl;
	dictionary * secd;

	dictionary * next;
};

#endif