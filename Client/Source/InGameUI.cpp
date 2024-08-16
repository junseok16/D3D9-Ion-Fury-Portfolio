#include "pch.h"
#include "InGameUI.h"

#include "Level.h"
#include "Actor.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"

#include "Monster.h"
#include "Mechsect.h"
#include "PlayerActor.h"

#include "CameraComponent.h"
#include "SpriteUIComponent.h"
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"



void CInGameUI::Initialize()
{
	InGameUISetting();

	// 시도 해봤는데 잘 안됌
	ColliderSetting();

	SetRenderType(ERenderType::ALPHA_BLEND);
	CUI::Initialize();
}

void CInGameUI::BeginPlay()
{
	//m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	//
	//m_wpButton0UIComponent.lock()->AddState(L"Button_0", 0, 2);
	//m_wpButton0UIComponent.lock()->SetFrameTime(L"Button_0", 0, 2, 0.8f);

	//m_wpButton1UIComponent.lock()->AddState(L"Button_1", 3, 7);
	//m_wpButton1UIComponent.lock()->SetFrameTime(L"Button_1", 3, 7, 0.05f);
	// 
	//m_wpButton2UIComponent.lock()->AddState(L"Button_2", 8, 10);
	//m_wpButton2UIComponent.lock()->SetFrameTime(L"Button_2", 8, 10, 0.05f);
	//
	//m_wpButton3UIComponent.lock()->AddState(L"Button_3", 11, 17);
	//m_wpButton3UIComponent.lock()->SetFrameTime(L"Button_3", 11, 17, 0.05f);
	//
	//m_wpButton4UIComponent.lock()->AddState(L"Button_4", 18, 22);
	//m_wpButton4UIComponent.lock()->SetFrameTime(L"Button_4", 18, 22, 0.05f);
	//
	//m_wpButton5UIComponent.lock()->AddState(L"Button_5", 23, 29);
	//m_wpButton5UIComponent.lock()->SetFrameTime(L"Button_5", 23, 29, 0.05f);
	//
	//m_wpButton6UIComponent.lock()->AddState(L"Button_6", 30, 36);
	//m_wpButton6UIComponent.lock()->SetFrameTime(L"Button_6", 30, 36, 0.05f);
	//
	//m_wpButton7UIComponent.lock()->AddState(L"Button_X_7", 37, 41);
	//m_wpButton7UIComponent.lock()->AddState(L"Button_O_7", 42, 42);
	//m_wpButton7UIComponent.lock()->SetFrameTime(L"Button_X_7", 37, 41, 0.05f);
	//m_wpButton7UIComponent.lock()->SetFrameTime(L"Button_O_7", 42, 42, 0.05f);



	CUI::BeginPlay();
}

int32 CInGameUI::Update(const float& _fDeltaSeconds)
{
	KeyInput();

	//if()

	std::wstring wstrCurrentState = m_wpButton0UIComponent.lock()->GetCurrentState();
	int32 iEndFrame = m_wpButton0UIComponent.lock()->GetStateFrame(wstrCurrentState).second;
	if (m_wpButton0UIComponent.lock()->GetCurFrame() == iEndFrame)
	{
		m_wpButton0UIComponent.lock()->SetIsAnimate(false);
	}

	return CUI::Update(_fDeltaSeconds);
}

int32 CInGameUI::LateUpdate(const float& _fDeltaSeconds)
{

	return CUI::LateUpdate(_fDeltaSeconds);
}

void CInGameUI::Render()
{
	CUI::Render();
}

void CInGameUI::EndPlay()
{
	CUI::EndPlay();
}

void CInGameUI::Release()
{
	CUI::Release();
}

int32 CInGameUI::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CInGameUI::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{

}

void CInGameUI::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CInGameUI::KeyInput()
{
	float fDis = CalculateTwoVectorDistance(m_wpButton0UIComponent);

	if (CInputManager::GetInstance()->IsKeyDown(DIK_E) && fDis <= 50.f)
	{
		int32 iEndIndex = m_wpButton0UIComponent.lock()->GetFileEndIndex();
		//m_wpButton0UIComponent.lock()->SetAnimationCount(1);
		//m_wpButton0UIComponent.lock()->SetCurrentAnimationCount(0);
		//m_wpButton0UIComponent.lock()->SetFrame(0, 0, 2);
		m_wpButton0UIComponent.lock()->SetIsAnimate(true);
		//m_wpButton0UIComponent.lock()->SetFrameTime(L"Button_0", 2, 1, 5.f);
	}







}

float CInGameUI::CalculateTwoVectorDistance(std::weak_ptr<CAnimationComponent> _wpButtonUIComponent)
{
	FVector3 vDistance{ 0.0f, 0.0f, 0.0f };
	vDistance.x = fabs(m_wpPlayerActor.lock()->GetActorWorldPosition().x - _wpButtonUIComponent.lock()->GetComponentWorldPosition().x);
	vDistance.y = fabs(m_wpPlayerActor.lock()->GetActorWorldPosition().y - _wpButtonUIComponent.lock()->GetComponentWorldPosition().y);
	vDistance.z = fabs(m_wpPlayerActor.lock()->GetActorWorldPosition().z - _wpButtonUIComponent.lock()->GetComponentWorldPosition().z);
	return vDistance.x + vDistance.y + vDistance.z;
}

void CInGameUI::InGameUISetting()
{
	// 결국에는 엑터의 포지션을 바꿔야 하는건가? // Component 위치가 안바뀌네
	//m_wpButton0UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_0");
	//m_wpButton0UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton0UIComponent.lock()->SettingAnimationInfo(L"Button_", 0, 2, L"Button_0", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton0UIComponent.lock()->SetComponentScale({ 5.f, 10.f, 0.f });
	//m_wpButton0UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton0UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton0UIComponent.lock()->SetCurFrame(0);
	//m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	//m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);
	//
	//m_wpButton1UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_1");
	////SetRootComponent(m_wpButton1UIComponent.lock());
	//m_wpButton1UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton1UIComponent.lock()->SettingAnimationInfo(L"Button_", 3, 7, L"Button_1", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton1UIComponent.lock()->SetComponentScale({ 10.f, 10.f, 0.f });
	//m_wpButton1UIComponent.lock()->SetComponentLocalPosition({ -120.f, 5.f, -30.f });
	//m_wpButton1UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton1UIComponent.lock()->SetCurFrame(3);
	// m_wpButton1UIComponent.lock()->AddState(L"Button_1", 3, 7);

	//
	//m_wpButton2UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_2");
	//m_wpButton2UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton2UIComponent.lock()->SettingAnimationInfo(L"Button_", 8, 10, L"Button_2", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton2UIComponent.lock()->SetComponentScale({ 10.f, 10.f, 0.f });
	//m_wpButton2UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton2UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton2UIComponent.lock()->SetCurFrame(8);
	////m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	////m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);
	//
	//m_wpButton3UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_3");
	//m_wpButton3UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton3UIComponent.lock()->SettingAnimationInfo(L"Button_", 11, 17, L"Button_3", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton3UIComponent.lock()->SetComponentScale({ 10.f, 10.f, 0.f });
	//m_wpButton3UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton3UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton3UIComponent.lock()->SetCurFrame(11);
	////m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	////m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);
	//
	//m_wpButton4UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_4");
	//m_wpButton4UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton4UIComponent.lock()->SettingAnimationInfo(L"Button_", 18, 22, L"Button_4", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton4UIComponent.lock()->SetComponentScale({ 10.f, 10.f, 0.f });
	//m_wpButton4UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton4UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton4UIComponent.lock()->SetCurFrame(18);
	////m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	////m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);
	//
	//m_wpButton5UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_5");
	//m_wpButton5UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton5UIComponent.lock()->SettingAnimationInfo(L"Button_", 23, 29, L"Button_5", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton5UIComponent.lock()->SetComponentScale({ 5.f, 10.f, 0.f });
	//m_wpButton5UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton5UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton5UIComponent.lock()->SetCurFrame(23);
	////m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	////m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);
	//
	//m_wpButton6UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_6");
	//m_wpButton6UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton6UIComponent.lock()->SettingAnimationInfo(L"Button_", 30, 36, L"Button_6", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton6UIComponent.lock()->SetComponentScale({ 10.f, 10.f, 0.f });
	//m_wpButton6UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton6UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton6UIComponent.lock()->SetCurFrame(30);
	//m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	//m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);

	//m_wpButton7UIComponent = CreateActorComponent<CAnimationComponent>(L"Button_7");
	//m_wpButton7UIComponent.lock()->SetIsRootComponent(true);
	//m_wpButton7UIComponent.lock()->SettingAnimationInfo(L"Button_", 37, 42, L"Button_", EAnimationType::DESIGNATED_TIME, 0.5f);
	//m_wpButton7UIComponent.lock()->SetComponentScale({ 10.f, 5.f, 0.f });
	//m_wpButton7UIComponent.lock()->SetComponentLocalPosition({ -100.f, 5.f, -30.f });
	//m_wpButton7UIComponent.lock()->SetIsAnimate(false);
	//m_wpButton7UIComponent.lock()->SetCurFrame(37);
	//m_wpButtonUIComponent.lock()->SetAnimationCount(0);
	//m_wpButtonUIComponent.lock()->SetFrame(0, 0, 0);

}

void CInGameUI::ColliderSetting()
{
	// 육면체 콜라이더
	//_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	//_wpCubeColliderComponent.lock()->SetOwnerComponent(CRenderManager::GetInstance()->GetCurRenderCamera());
	//_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::INTERACTION);
	//_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	//m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::);
	//m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::);

	//CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}



//f (CInputManager::GetInstance()->IsKeyDown(DIK_E) && fDis <= 50.f)
//
//	int32 iEndIndex = m_wpButtonUIComponent.lock()->GetFileEndIndex();
//	m_wpButtonUIComponent.lock()->SetCurrentAnimationCount(2);
//	m_wpButtonUIComponent.lock()->SetFrame(0, 0, iEndIndex);
//	m_wpButtonUIComponent.lock()->SetCurrentState(L"Button_0");
//	m_wpButtonUIComponent.lock()->SetIsAnimate(true);
//
	//POINT pMouse{};
	//::GetCursorPos(&pMouse);
	//::ScreenToClient(hWnd,&pMouse);
	//
	//float x = m_wpButtonUIComponent.lock()->GetComponentWorldPosition().x; 
	//float y = m_wpButtonUIComponent.lock()->GetComponentWorldPosition().y;
	//
	//float x1 = m_wpButtonUIComponent.lock()->GetComponentLocalPosition().x;
	//float y1 = m_wpButtonUIComponent.lock()->GetComponentLocalPosition().y;
	//
	//float x2 = CInputManager::GetInstance()->GetMouseDeltaX();
	//float y2 = CInputManager::GetInstance()->GetMouseDeltaY();
	//
	//if (pMouse.x >= (m_wpButtonUIComponent.lock()->GetComponentWorldPosition().x - 20.f)
	//	&& pMouse.x <= (m_wpButtonUIComponent.lock()->GetComponentWorldPosition().x + 20.f))
	//{
	//	int a = 5;
	//
	//	if (pMouse.y >= (m_wpButtonUIComponent.lock()->GetComponentWorldPosition().y - 20.f)
	//		&& pMouse.y <= (m_wpButtonUIComponent.lock()->GetComponentWorldPosition().y + 20.f))
	//	{
			//int32 iEndIndex = m_wpButtonUIComponent.lock()->GetFileEndIndex();
			//m_wpButtonUIComponent.lock()->SetCurrentAnimationCount(2);
			//m_wpButtonUIComponent.lock()->SetFrame(0, 0, iEndIndex);
			//m_wpButtonUIComponent.lock()->SetCurrentState(L"Button_0");
			//m_wpButtonUIComponent.lock()->SetIsAnimate(true);
			//m_wpButtonUIComponent.lock()->SetCurFrame(2);
	//	}
	//}
//}
