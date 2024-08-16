#pragma once
#include "BTTaskNode.h"
class CAttackTask :
    public CBTTaskNode
{
public:
	explicit CAttackTask() = default;
	virtual ~CAttackTask() = default;

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;
};

