#pragma once
#include "Actor.h"

class CEffectComponent;

// 테스트용 액터입니다.
class CEffectActor :
    public CActor
{
public:
	explicit CEffectActor() = default;
	virtual ~CEffectActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	std::weak_ptr<CEffectComponent> GetEffectComponent() { return m_wpEffectComponent; }

private:
	void RemoveSelf();

private:
	std::weak_ptr<CEffectComponent> m_wpEffectComponent;
};

