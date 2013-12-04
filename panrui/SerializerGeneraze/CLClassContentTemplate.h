#ifndef CLASS_CONTENT_TEMPLATE
#define CLASS_CONTENT_TEMPLATE

#include "CLClassTemplate.h"
#include <list>

using namespace std;
struct memberFunction;
struct memberVariable;
class CLClassTemplate;
struct memberFunctionContent
{
	string typeName;
	string className;
	string functionName;
	string paraName;
	string content;
	memberFunctionContent(string typeName,string className,string functionName,string paraName);
	void insertSentence(string sentence);
	friend ofstream& operator <<(ofstream & ostr,memberFunctionContent & cur_fc);
};
struct memberVarStatic
{
	string typeName;
	string className;
	string VariableName;
	string value;
	memberVarStatic(string typeName,string className,string VariableName,string value);
	friend ofstream& operator <<(ofstream & ostr,memberVarStatic & cur_vs);

};


class CLClassContentTemplate
{
private:
	CLClassContentTemplate(const CLClassContentTemplate &);
	const CLClassContentTemplate & operator = (const CLClassContentTemplate &);
	CLClassTemplate	* m_classHeader;
	
	string IncludingFile;

	list<memberVarStatic> var_l;
	list<memberFunctionContent> func_l;
protected:

public:
	CLClassContentTemplate(CLClassTemplate * classHeader);
	~CLClassContentTemplate();
	void writeCPPtoDisk();
	
	void addIncludingFile(string & i_include);

	memberFunctionContent * addNewFunction(string functionName);
	memberVarStatic * addNewVarStatic(string varName);
	friend ofstream& operator <<(ofstream & ostr,CLClassContentTemplate & cur_tc);

};

#endif