#pragma once
#include "BTNode.h"

class CBTTaskNode : public CBTNode
{
public:
	explicit CBTTaskNode() = default;
	virtual ~CBTTaskNode() = default;

public:
	virtual void Initialize() override;
	virtual EBTNodeResult Update() override sealed;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() { return EBTNodeResult::ENUM_END; }
};
