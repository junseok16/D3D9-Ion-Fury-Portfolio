#pragma once
#include "BTTaskNode.h"

class CRepositionTask : public CBTTaskNode
{
public:
	explicit CRepositionTask() = default;
	virtual ~CRepositionTask() = default;

private:
	virtual void Initialize() override;
	virtual void Release() override;

	// 랜덤하게 움직이게 하기 위한 함수 - 동연 -
	float GetRandomFloat(float _fLowBound, float _fHighBound);
	void GetRandomVector(FVector3* _vOut, FVector3* _vMin, FVector3* _vMax);

private:
	virtual EBTNodeResult UpdateTask() override;

	bool m_bReposition = false;
};

