#include "Unit.h"



int main()
{
	ifstream ifstr("D:\\test.torrent",ios::binary);
	Unit * pTest = Unit::build(ifstr);

	long long len = ifstr.tellg();

	ifstr.close();
	delete pTest;
	return 0;
}