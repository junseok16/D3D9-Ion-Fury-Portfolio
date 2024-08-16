#pragma once
#include "UI.h"

class CPlayerActor;
class CMechsect;
class CCameraComponent;
class CSpriteUIComponent;
class CAnimationComponent;
class CCubeColliderComponent;

class CInGameUI : public CUI
{
public:
	explicit CInGameUI() = default;
	virtual ~CInGameUI() = default;

public:
	virtual void  Initialize() override;
	virtual void  BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void  Render() override;
	virtual void  EndPlay() override;
	virtual void  Release() override;

private:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);
	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);
	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	void  KeyInput();
	void  InGameUISetting();
	void  ColliderSetting();
	float CalculateTwoVectorDistance(std::weak_ptr<CAnimationComponent> _wpButtonUIComponent);

private:
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CCubeColliderComponent> m_wpCubeColliderComponent;

	// 버튼,레버, 
	std::weak_ptr<CAnimationComponent> m_wpButton0UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton1UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton2UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton3UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton4UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton5UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton6UIComponent;
	std::weak_ptr<CAnimationComponent> m_wpButton7UIComponent;
};

