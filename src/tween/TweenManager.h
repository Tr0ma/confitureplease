#ifndef _TWEENMANAGER_H_
#define _TWEENMANAGER_H_

#include "Updateable.h"
#include "Tween.h"
#include <vector>

using namespace std;

class DisplayObject;

class TweenManager : public IUpdateable
{
private:
	vector<Tween*>	m_Tweens;
	vector<Tween*>	m_CompleteTweens;

public:
	TweenManager() {}
	~TweenManager() {}
	
	void		Update(float deltaTime = 0.0f) override;

	template<class C>
	C&			CreateTween(DisplayObject& target);

private:
	void		AddTween(Tween& tween);
	int			GetTweenIndex(Tween& tween);
	void		ClearCompleteTweens();
	void		onTweenComplete(Event& evt);

};

template<class C>
C& TweenManager::CreateTween(DisplayObject& target)
{
	C* c = new C(target);
	AddTween(*c);
	return *c;
}

#endif
