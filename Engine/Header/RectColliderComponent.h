#pragma once
#include "ColliderComponent.h"

class CRectColliderComponent : public CColliderComponent
{
public:
	explicit CRectColliderComponent() = default;
	virtual ~CRectColliderComponent() = default;

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

public:
	const D3DXPLANE& GetPlane() const { return m_tD3DPlane; }

private:
	void UpdatePlane();

private:
	// 평면 구조체
	D3DXPLANE m_tD3DPlane{};
};

