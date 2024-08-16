#pragma once
#include "ColliderComponent.h"

class CCubeColliderComponent : public CColliderComponent
{
public:
	explicit CCubeColliderComponent() = default;
	virtual ~CCubeColliderComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	virtual bool IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent) override;
};

