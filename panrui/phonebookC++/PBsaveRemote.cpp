#include "PBsaveRemote.h"

PBsaveRemote::PBsaveRemote()
{
	pb_save = new PBsave();
}

PBsaveRemote::~PBsaveRemote()
{
	delete pb_save;
}

bool PBsaveRemote::isExecute(string cmd)
{
	if(cmd.substr(0,CMD_LEN) == "-sa")
		return true;
	return false;	
}

bool PBsaveRemote::executeCMD(vector<PBitem *> &pb_item,string para)
{
	string path;
	if(!analysisPara(para,path))
	{
		cout<<"save para error while saving"<<endl;
		return true;
	}

	pb_save->doSave(path,pb_item);
	return true;
}

bool PBsaveRemote::analysisPara(string para,string &path)
{
	string::size_type path_f = para.find_first_not_of(' ',0);
	if(path_f == string::npos)
		return false;

	path = para.substr(path_f,para.length()-path_f);

	return true;
}