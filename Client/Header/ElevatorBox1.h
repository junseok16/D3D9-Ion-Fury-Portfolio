#pragma once
#include "InteractiveBox.h"

// Actor
class COutGameUI;
class CPlayerActor;
class CElevatorFloor;
class CCubeColliderActor;

// Component
class CCameraComponent;
class CPhysicsComponent;
class CCubeMeshComponent;
class CAnimationComponent;
class CCubeColliderComponent;

class CElevatorBox1 : public CInteractiveBox
{
public:
	explicit CElevatorBox1() = default;
	virtual ~CElevatorBox1() = default;

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
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;
	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;
	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	void SetElevatorFloorActor(std::weak_ptr<CElevatorFloor> _wpElevatorGate) { m_wpElevatorFloor = _wpElevatorGate; }

private:
	void  KeyInput();
	void  InGameSetting();
	void  ColliderSetting();

	// ������ ���� �����Ӱ� �� �������� ��������Ʈ�� ������Ű�� ���� �Լ�
	void  UpdateDoorState();
	void  SetElevatorEndFrame();
	std::shared_ptr<CCubeColliderActor> HitScanBox();



private:
	// ����
	bool m_bGateOpen = false;
	float m_fElevatorFloorMovementY = 0.5f;
	//float m_fElevatorFloorUpdatePosY = 0.f;

	EGateState m_eGateState = EGateState::STOPPED;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CPhysicsComponent> m_wpPhysicsComponent;
	std::weak_ptr<CAnimationComponent> m_wpElevatorBox;
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;

	// ť��� �����ؾ� �մϴ�.
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CElevatorFloor> m_wpElevatorFloor;


};
