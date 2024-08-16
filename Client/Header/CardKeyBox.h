#pragma once
#include "InteractiveBox.h"

// Actor
class COutGameUI;
class CLeverGate;
class CPlayerActor;
class CCubeColliderActor;

// Component
class CCameraComponent;
class CCubeMeshComponent;
class CAnimationComponent;
class CCubeColliderComponent;

class CCardKeyBox : public CInteractiveBox
{
public:
	explicit CCardKeyBox() = default;
	virtual ~CCardKeyBox() = default;

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
	void SetCardKeyGateActor(std::weak_ptr<CLeverGate> _wpCardKeyGate) { m_wpCardKeyGate = _wpCardKeyGate; }

private:
	void  KeyInput();
	void  InGameSetting();
	void  ColliderSetting();
	void  UpdateDoorState();


private:
	bool m_bGateOpen = false;
	float m_fCardKeyGateUpdatePosY = 0.2f;

	EGateState m_eGateState = EGateState::STOPPED;

	// Actor
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CLeverGate> m_wpCardKeyGate;

	// Component
	std::weak_ptr<CAnimationComponent> m_wpCardKeyBox;
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;
};

