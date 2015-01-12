#ifndef _MOVEDOWNUPDATEDEVENT_H_
#define _MOVEDOWNUPDATEDEVENT_H_

#include <vector>
#include <Event.h>

using namespace std;

class GemVO;

class MoveDownUpdatedEvent : public Event
{
public:
	static const char* TYPE;
	vector<GemVO*>& m_MoveDownList;
	vector<GemVO*>& m_NewGemsList;

public:
	explicit MoveDownUpdatedEvent(vector<GemVO*>& moveDownList, vector<GemVO*>& newGemsList) 
		: Event(TYPE), m_MoveDownList(moveDownList), m_NewGemsList(newGemsList) {}
	~MoveDownUpdatedEvent() {}
};

#endif