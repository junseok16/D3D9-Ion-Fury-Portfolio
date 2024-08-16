#pragma once
#include "BTNode.h"

class CBTDecorator : public CBTNode
{
public:
	explicit CBTDecorator() = default;
	virtual ~CBTDecorator() = default;

public:
	virtual const bool EvaluateOnBlackboard() { return false; }
};

