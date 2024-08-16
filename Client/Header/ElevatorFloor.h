#pragma once
#include "InteractiveBox.h"

class CCubeMeshComponent;
class CCubeColliderComponent;

class CElevatorFloor : public CInteractiveBox
{
public:
	explicit CElevatorFloor() = default;
	virtual ~CElevatorFloor() = default;

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


	// Getter Setter // 
	bool GetGateOpen() { return m_bGateOpen; }
	void SetGateOpen(bool _GateOpen) { m_bGateOpen = _GateOpen; }

	EGateState GetGateState() { return m_eGateState; }
	void SetGateState(EGateState _eGateState) { m_eGateState = _eGateState; }

public:
	void InGameSetting();
	void ColliderSetting();

private:
	bool m_bGateOpen = false;
	EGateState m_eGateState = EGateState::STOPPED;
	std::weak_ptr<CCubeMeshComponent> m_wpElevatorFloor;
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;
};

