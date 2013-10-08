#ifndef PB_TOOL
#define PB_TOOL
#include <string>
using namespace std;
class PBTool
{
private:
	PBTool(const PBTool &);
	PBTool & operator = (const PBTool &);
protected:
public:
	static bool analysisPara(string para,string &name,string &num);	
	static bool analysisPara(string para,string &path);

};

#endif
