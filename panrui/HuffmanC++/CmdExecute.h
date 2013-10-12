#ifndef CMD_EXECUTE
#define CMD_EXECUTE

class CmdExecute
{
private:
	CmdExecute(CmdExecute &);
	const CmdExecute & operator = (const CmdExecute &);
protected:
	unsigned int &retValue;
	unsigned char ** cmd;
	unsigned int paraNum;
public:
	CmdExecute(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum);
	~CmdExecute();

	virtual void startExecute() = 0 ;
};
#endif
