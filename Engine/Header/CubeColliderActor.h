#pragma once
#include "Actor.h"

class CCubeColliderComponent;

class CCubeColliderActor : public CActor
{
public:
	explicit CCubeColliderActor() = default;
	virtual ~CCubeColliderActor() = default;

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

public:
	std::weak_ptr<CCubeColliderComponent> GetCubeColliderComponent() { CHECK(!m_wpCubeColliderComponent.expired()); return m_wpCubeColliderComponent; }

protected:
	std::weak_ptr<CCubeColliderComponent>	m_wpCubeColliderComponent;
};

