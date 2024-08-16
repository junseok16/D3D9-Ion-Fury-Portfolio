#pragma once
#include "BTTaskNode.h"

class CDeadTask : public CBTTaskNode
{
public:
	explicit CDeadTask() = default;
	virtual ~CDeadTask() = default;

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

};

