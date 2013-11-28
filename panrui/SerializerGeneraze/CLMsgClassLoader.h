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

#define DEFINITION_TYPE		0
#define DEFINITION_FLAG		1
	namespace VAR_TYPE_DEF
	{
#define BASIC_TYPE	0
#define POINT_TYPE	1
#define STRING_TYPE	2
#define USER_TYPE	3
		const int type_num = 12;
		struct type_map
		{
			string type_name[type_num];
			int	type_code[type_num];
		}t_map = {"*",
				"char","int","float","double","bool","long","long double","wchar_t","short",
				"string",
				" ",
				POINT_TYPE,
				BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,BASIC_TYPE,
				STRING_TYPE,
				USER_TYPE};
		
	}
	namespace KEY_WORD_DEF{//为函数识别做准备
#define KEY_WORD_STATIC		"static"
#define KEY_WORD_PUBLIC		"public"
#define KEY_WORD_PRIVATE	"private"
#define KEY_WORD_PROTECTED	"protected"
#define KEY_WORD_VIRTUAL	"virtual"
#define KEY_WORD_TYPEDEF	"typedef"
#define KEY_WORD_INLINE		"inline"
#define	KEY_WORD_UNION		"union"
#define KEY_WORD_MUTABLE	"mutable"
#define KEY_WORD_UNSIGNED	"unsigned"
#define KEY_WORD_EXPLICIT	"explicit"
#define KEY_WORD_USING		"using"
#define KEY_WORD_OPERATOR	"operator"
#define KEY_WORD_VOLATILE	"volatile"
#define KEY_WORD_THROW		"throw"
#define KEY_WORD_FRIEND		"friend"
#define KEY_WORD_DOUBLE		"double"
#define KEY_WORD_SHORT		"short"
#define KEY_WORD_BOOL		"bool"
#define KEY_WORD_INT		"int"
#define KEY_WORD_SIGNED		"signed"
#define KEY_WORD_LONG		"long"
#define KEY_WORD_CHAR		"char"
#define KEY_WORD_FLOAT		"float"
#define KEY_WORD_WCHAR_T	"wchar_t"
}

	using namespace KEY_WORD_DEF;
	using namespace VAR_TYPE_DEF;
	
	void getNextObj(ifstream & istr,string &ret);
	bool judgeKeyWordType(string &tmp,int &type);
	bool classSentence(ifstream & istr,CLMsgClass * t_class,string &tmp);
	bool classJudge(ifstream & istr,string & classname,bool & is_needSerial,bool & is_struct);
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