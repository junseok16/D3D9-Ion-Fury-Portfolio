#pragma once
#include "ColliderComponent.h"

class CSphereColliderComponent : public CColliderComponent
{

public:
	explicit CSphereColliderComponent() = default;
	virtual ~CSphereColliderComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	const float& GetRadius() { return m_fRadius; }

public:
	virtual bool IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent) override;

	void SetSphereColliderInfo(float _fRadius, int32 _iSlice, int32 _iStack);

protected:
	float m_fRadius = 1.0f;
	int32 m_iSlice = 10;
	int32 m_iStack = 10;
};

