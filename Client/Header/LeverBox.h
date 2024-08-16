#pragma once
#include "InteractiveBox.h"

// Actor
class COutGameUI;
class CPlayerActor;
class CCardKeyGate;
class CCubeColliderActor;

// Component
class CCameraComponent;
class CCubeMeshComponent;
class CAnimationComponent;
class CCubeColliderComponent;
//class CRectangleMeshComponent;

class CLeverBox : public CInteractiveBox
{
public:
	explicit CLeverBox() = default;
	virtual ~CLeverBox() = default;

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
	void SetLeverGateActor(std::weak_ptr<CCardKeyGate> _wpLeverGate) { m_wpLeverGate = _wpLeverGate; }
	std::weak_ptr<CCubeColliderComponent> GetCubeColliderComponent() { CHECK(!m_wpCubeColliderComponent.expired()); return m_wpCubeColliderComponent; }

private:
	void  KeyInput();
	void  InGameSetting();
	void  ColliderSetting();

	// 레버의 시작 프레임과 끝 프레임의 스프라이트로 고정시키기 위한 함수
	void  SetLeverEndFrame();
	void  UpdateDoorState();

private:
	bool m_bGateOpen = false;
	float m_fLeverUpdatePosY = 0.3f;

	EGateState m_eGateState = EGateState::STOPPED;

	// Actor
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CCardKeyGate> m_wpLeverGate;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CAnimationComponent> m_wpLeverBox;

	// Component
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;
};

