#ifndef CLASS_TEMPLATE
#define CLASS_TEMPLATE
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct memberFunction
{
	string typeName;
	string functionName;
	string paraName;
	memberFunction(string Typename,string functionName,string paraName);
	friend ofstream& operator << (ofstream& ostr,memberFunction& cur_f );
};
struct memberVariable
{
	string typeName;
	string VariableName;
	memberVariable(string typeName,string VariableName);
	friend ofstream& operator << (ofstream& ostr,memberVariable& cur_v);
};

class ClassTemplate
{
private:
	string className;
    vector<memberFunction> public_f;
	vector<memberFunction> private_f;
	vector<memberFunction> protected_f;
	vector<memberVariable> public_v;
	vector<memberVariable> private_v;
	vector<memberVariable> protected_v;
/*wait for achieved*/	
	vector<string>		   header;
	vector<string>		   relations;

	void writeSingleTeamTofile(ofstream &ostr,vector<memberFunction> & cur_f,vector<memberVariable> & cur_v,string teamName);
	string initDef(string &);
	const ClassTemplate& operator = (const ClassTemplate &);
	ClassTemplate(const ClassTemplate &);
public:
	ClassTemplate(string className,bool isNoConstructer);
	~ClassTemplate();
	void addItem(string access,string typeName,string functionName,string paraName);
	void addItem(string access,string typeName,string VariableName);
	void writeToFile();
	friend ofstream& operator << (ofstream & str ,ClassTemplate& cur_c);
};

#endif
