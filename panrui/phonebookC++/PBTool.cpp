#include "PBTool.h"

bool PBTool::analysisPara(string para,string &name,string &num)
{
		string::size_type name_f = para.find_first_not_of(' ',0);
		if(name_f == string::npos)
			return false ;

		string::size_type name_l = para.find_first_of(' ',name_f);
		if(name_l == string::npos)
			return false;

		string::size_type num_f = para.find_first_not_of(' ',name_l);
		if(num_f == string::npos)
			return false;


		name = para.substr(name_f,name_l - name_f);
		num = para.substr(num_f,para.length()-num_f);
			return true;
}

bool PBTool::analysisPara(string para,string &path)
{
		string::size_type path_f = para.find_first_not_of(' ',0);
		if(path_f == string::npos)
			return false;

		path = para.substr(path_f,para.length()-path_f);

			return true;
}
