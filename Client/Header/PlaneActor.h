#pragma once
#include "Actor.h"

class CRectangleMeshComponent;
class CRectColliderComponent;

class CPlaneActor : public CActor
{
public:
	explicit CPlaneActor() = default;
	virtual ~CPlaneActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	std::weak_ptr<CRectangleMeshComponent> m_wpRectangleMeshComponent;
	std::weak_ptr<CRectColliderComponent> m_wpRectColliderComponent;
};

