#ifndef PB_ITEM
#define PB_ITEM

#include <string>


using namespace std;
class PBitem
{
private:
	string name;
	string number;
protected:

public:
	string	getName();
	string	getNum();
	PBitem();
	PBitem(string name,string number);
	~PBitem();
	void	modifyInfo(string name,string num);

};
#endif