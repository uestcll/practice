#ifndef CMD_EXECUTE
#define CMD_EXECUTE

class CmdExecute
{
private:
	CmdExecute(const CmdExecute &);
	const CmdExecute & operator = (const CmdExecute &);
protected:
	unsigned int &retValue;
	unsigned char ** cmd;
	unsigned int paraNum;
public:
	CmdExecute(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum);
	virtual ~CmdExecute();

	virtual void startExecute() = 0 ;
};
#endif
