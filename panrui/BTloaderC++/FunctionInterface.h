#ifndef _FUNCTION_INTERFACE_
#define _FUNCTION_INTERFACE_
#include "ItemBase.h"

#include <memory>
using namespace std;

class FunctionInterface
{
private:
	std::tr1::shared_ptr<ItemBase> pTorrent;
public:
	FunctionInterface();
	~FunctionInterface();
	void OpenTorrentFile(const char * path);
	void SearchItem();
	void ShowAllItem();

};
#endif