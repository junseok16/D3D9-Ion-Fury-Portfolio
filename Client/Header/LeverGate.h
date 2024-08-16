#pragma once
#include "InteractiveBox.h"

class CCubeMeshComponent;
class CCubeColliderComponent;

class CLeverGate : public CInteractiveBox
{
public:
	explicit CLeverGate() = default;
	virtual ~CLeverGate() = default;

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
	void InGameSetting();
	void ColliderSetting();

private:
	std::weak_ptr<CCubeMeshComponent> m_wpLeverGate;	
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;

};

