#pragma once
#include "Actor.h"

class CPlaneColliderComponent;
class CAnimationComponent;

class CMonsterActor : public CActor
{
public:
	explicit CMonsterActor() = default;
	virtual ~CMonsterActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	void AnimationSetting();

private:
	std::weak_ptr<CAnimationComponent>		m_wpAnimationComponent;
	std::weak_ptr<CPlaneColliderComponent>	m_wpPlaneColliderComponent;
};
