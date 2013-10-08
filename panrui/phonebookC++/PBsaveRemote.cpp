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
	if(!PBTool::analysisPara(para,path))
	{
		cout<<"save para error while saving"<<endl;
		return true;
	}

	pb_save->doSave(path,pb_item);
	return true;
}

