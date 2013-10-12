#ifndef CMD_ANALYSIS
#define CMD_ANALYSIS

class CmdAnalysis
{
private:
	CmdAnalysis(const CmdAnalysis &);
	const CmdAnalysis & operator = (const CmdAnalysis &);
protected:	
	unsigned int &retValue;
	unsigned char ** cmd;
	unsigned int paraNum;

public:
	CmdAnalysis(unsigned int &retValue,unsigned char ** cmd,unsigned int paraNum);
	~CmdAnalysis();

	virtual void startAnalysis() = 0;
};

#endif
