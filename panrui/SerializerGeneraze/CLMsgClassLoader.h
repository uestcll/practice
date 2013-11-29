#ifndef CLMsgClassLoader_H
#define CLMsgClassLoader_H
#include <string>
using namespace std;


class CLMsgClassManager;
class CLMsgClass;
namespace filedeal
{
#define STRUCT_FLAG "struct"
#define CLASS_FLAG	"class"
#define KEY_WORD_PUBLIC		"public:"
#define KEY_WORD_PRIVATE	"private:"
#define KEY_WORD_PROTECTED	"protected:"
void getNextObj(ifstream & istr,string &ret);
void getNextObj(string & in,string &ret);
bool classJudge(ifstream & istr,string & classname,bool & is_needSerial,bool & is_struct);
bool sentenceJudge(string &in);
void classContent(ifstream & istr,CLMsgClass * t_class);
}

class CLMsgClassLoader
{
public:
	CLMsgClassLoader(const CLMsgClassManager *,string *filename,int strNum);
	~CLMsgClassLoader();
	static const string serialFlag;
private:
	void  loadFileFromDisk();
	void  loadSingleFile(string &);

	const CLMsgClassLoader & operator = (const CLMsgClassLoader &);
	CLMsgClassLoader(const CLMsgClassLoader &);
private:
	CLMsgClassManager*	m_msgClassMng;
	string *			m_filename;
	int					m_strNum;
};

#endif