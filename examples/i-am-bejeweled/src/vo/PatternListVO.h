#ifndef _PATTERNLISTVO_H_
#define _PATTERNLISTVO_H_

class PatternListVO
{
public:
	vector<GemVO*> m_GemList;
	vector<const char*> m_PatternList;

public:
	PatternListVO() {}
	~PatternListVO() {}
};

#endif