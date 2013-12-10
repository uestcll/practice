#ifndef CLOffsetSeter_H
#define CLOffsetSeter_H

class CLMsgClass;
class CLMsgClassManager;
struct offset;
class CLOffsetSeter
{
public:
	CLOffsetSeter(CLMsgClass * in_class);
	~CLOffsetSeter();
	virtual offset	setOffset(CLMsgClassManager * pmng);
private:
	CLMsgClass * m_class;
	CLOffsetSeter(const CLOffsetSeter &);
	const CLOffsetSeter & operator = (const CLOffsetSeter);
};

#endif
