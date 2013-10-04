#include "PBadapter.h"

int main()
{
	PBadapter * pb_adapter = new PBadapter;
	pb_adapter->start();
	delete pb_adapter;
	return 0;
}