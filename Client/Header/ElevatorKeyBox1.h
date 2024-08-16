#pragma once
#include "InteractiveBox.h"

// Actor
class COutGameUI;
class CPlayerActor;
class CElevatorFloor;
class CCubeColliderActor;

// Component
class CCameraComponent;
class CCubeMeshComponent;
class CAnimationComponent;
class CCubeColliderComponent;

class CElevatorKeyBox1 : public CInteractiveBox
{
public:
	explicit CElevatorKeyBox1() = default;
	virtual ~CElevatorKeyBox1() = default;

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

	void SetElevatorFloorActor(std::weak_ptr<CElevatorFloor> _wpElevatorGate) { m_wpElevatorFloor = _wpElevatorGate; }

private:
	void  KeyInput();
	void  InGameSetting();
	void  ColliderSetting();
	void  UpdateDoorState();


private:
	float m_fElevatorFloorMovementY = 1.f;
	float m_fElevatorFloorUpdatePosY = 0.f;

	// Actor
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CElevatorFloor> m_wpElevatorFloor;

	// Component
	std::weak_ptr<CAnimationComponent> m_wpElevatorKeyBox;
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;
};

