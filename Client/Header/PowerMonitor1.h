#pragma once
#include "InteractiveBox.h"

class COutGameUI;
class CPlayerActor;
class CAnimationComponent;

class CPowerMonitor1 : public CInteractiveBox
{
public:
	explicit CPowerMonitor1() = default;
	virtual ~CPowerMonitor1() = default;

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

private:
	void  InGameSetting();
	void  SetPowerMonitorFrame();
	void  KeyInput(const float& _fDeltaSeconds);

private:
	float m_fElapsedTime = 0.f;
	bool m_bPowerMonitor = false;
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CAnimationComponent> m_wpPowerMonitor;

};

