#include "Unit.h"



int main()
{
	ifstream ifstr("D:\\test.torrent",ios::binary);
	Unit * pTest = Unit::build(ifstr);

	int len = ifstr.tellg();

	ifstr.close();
	return 0;
}