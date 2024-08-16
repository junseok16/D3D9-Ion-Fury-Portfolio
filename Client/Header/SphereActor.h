#pragma once
#include "Actor.h"

class CRectangleMeshComponent;
class CSphereColliderComponent;

class CSphereActor : public CActor
{
public:
	explicit CSphereActor() = default;
	virtual ~CSphereActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	virtual void OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

private:
	std::weak_ptr<CRectangleMeshComponent> m_wpRectangleMeshComponent;
	std::weak_ptr<CSphereColliderComponent> m_wpSphereColliderComponent;
};

