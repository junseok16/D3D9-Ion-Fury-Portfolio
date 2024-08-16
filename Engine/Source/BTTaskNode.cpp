#include "pch.h"
#include "BTTaskNode.h"

#include "BTDecorator.h"
using namespace std;

void CBTTaskNode::Initialize()
{
	CBTNode::Initialize();
}

void CBTTaskNode::Release()
{
	CBTNode::Release();
}

EBTNodeResult CBTTaskNode::Update()
{
	CBTNode::Update();

	// 데코레이터가 있는 경우
	
	return UpdateTask();
}
