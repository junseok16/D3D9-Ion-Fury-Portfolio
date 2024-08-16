#pragma once
#include "SceneComponent.h"

class CSpringArmComponent : public CSceneComponent
{
public:
	explicit CSpringArmComponent() = default;
	virtual ~CSpringArmComponent() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

/********************
	Getter/Setter
********************/
public:
	void SetTargetArmLength(float _fTargetArmLength) { m_fTargetArmLength = _fTargetArmLength; }

	float GetTargetArmLength() const { return m_fTargetArmLength; }

/********************
	Data Members
********************/
private:
	// 스프링 암 컴포넌트와 카메라 사이의 거리
	float m_fTargetArmLength = 0.0f;
};

