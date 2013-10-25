#include "FunctionInterface.h"
#include "ReadCtrler.h"
#include "GetNewItem.h"

FunctionInterface::FunctionInterface(){}
FunctionInterface::~FunctionInterface(){}

void FunctionInterface::OpenTorrentFile(const char * path)
{
	string t_path = path;
	ReadCtrler::SetPath(t_path);
	GetNewItem::GetNewInit();

	pTorrent.reset(GetNewItem::getNewItem());
}