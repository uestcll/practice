#include "ReadCtrler.h"
#include "GetNewItem.h"
#include "ItemBase.h"

#include <memory>
using namespace std;

int main()
{
	string path = "D:\\test.torrent";
	ReadCtrler::SetPath(path);
	GetNewItem::GetNewInit();

	tr1::shared_ptr<ItemBase> pTorrent(GetNewItem::getNewItem());
	return 0;
}