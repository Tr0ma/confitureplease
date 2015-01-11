#ifndef _BASEMEDIATOR_H_
#define _BASEMEDIATOR_H_

#include <Mediator.h>

class BaseMediator : public Mediator
{
public:
	BaseMediator() {}
	~BaseMediator() {}

	virtual void OnInitialized() override;
};

#endif