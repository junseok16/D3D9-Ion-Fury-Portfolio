#include "pch.h"
#include "LeverBox.h"

// Level
#include "Level.h"

// Actor
#include "Actor.h"
#include "OutGameUI.h"
#include "PlayerActor.h"
#include "CardKeyGate.h"
#include "CubeColliderActor.h"

// Component
#include "SoundComponent.h"
#include "CameraComponent.h"
#include "CubeMeshComponent.h"
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"


// Manager
#include "InputManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"


using namespace std;

void CLeverBox::Initialize()
{
	InGameSetting();

	ColliderSetting();

	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
	m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSoundComponent);

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CLeverBox::BeginPlay()
{	
	m_wpOutGameUI = dynamic_pointer_cast<COutGameUI>(GetLevel().lock()->FindActor(L"OutGameUI"));
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 1.f, 30.f, 1.f, 90.f);

	m_wpLeverBox.lock()->AddState(L"LeverBox", 0, 4);

	CInteractiveBox::BeginPlay();
}

int32 CLeverBox::Update(const float& _fDeltaSeconds)
{
	KeyInput();
	UpdateDoorState();
	SetLeverEndFrame();

	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CLeverBox::LateUpdate(const float& _fDeltaSeconds)
{
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CLeverBox::Render()
{
	CInteractiveBox::Render();
}

void CLeverBox::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CLeverBox::Release()
{
	CInteractiveBox::Release();
}

void CLeverBox::KeyInput()
{
	FVector3 fv = m_wpPlayerActor.lock()->GetActorWorldPosition() - m_wpLeverBox.lock()->GetOwnerActor().lock()->GetActorWorldPosition();
	float fDis = D3DXVec3Length(&fv);

	m_wpOutGameUI.lock()->SetDisLeverActor(fDis);

	if (m_bGateOpen == true && m_eGateState == EGateState::STOPPED && CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f /*&& ±§º±√Êµπ*/)
	{
		m_bGateOpen = false;
		m_eGateState = EGateState::CLOSED;
		m_wpLeverBox.lock()->SetCurFrame(0);
		m_wpSoundComponent.lock()->PlayBGMByDistance("Door_Stone", 80.f);
		m_wpSoundComponent.lock()->PlayPlayerSound("Door_Lever", 80.f, ESoundType::EFFECT);

	}
	else if (m_bGateOpen == false && m_eGateState == EGateState::STOPPED && CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f /*&& ±§º±√Êµπ*/)
	{
		m_bGateOpen = true;
		m_eGateState = EGateState::OPENED;
		m_wpLeverBox.lock()->SetIsAnimate(true);
		m_wpSoundComponent.lock()->PlayBGMByDistance("Door_Stone", 80.f);
		m_wpSoundComponent.lock()->PlayPlayerSound("Door_Lever", 80.f, ESoundType::EFFECT);


	}
}

void CLeverBox::InGameSetting()
{
	m_wpLeverBox = CreateActorComponent<CAnimationComponent>(L"LeverBoxComponent");
	SetRootComponent(m_wpLeverBox);
	m_wpLeverBox.lock()->SettingAnimationInfo(L"InteractiveBox0_", 0, 4, L"LeverBox", EAnimationType::LOOP, 0.2f);
	m_wpLeverBox.lock()->SetIsAnimate(false);

	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpLeverBox.lock());
}

void CLeverBox::ColliderSetting()
{
	// ¿∞∏È√º ƒ›∂Û¿Ã¥ı
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpLeverBox); 
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::INTERACTION);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CLeverBox::SetLeverEndFrame()
{
	std::wstring wstrCurrentState = m_wpLeverBox.lock()->GetCurrentState();
	int32 iEndFrame = m_wpLeverBox.lock()->GetStateFrame(wstrCurrentState).second;
	
	if (m_wpLeverBox.lock()->GetCurFrame() == iEndFrame)
	{
		m_wpLeverBox.lock()->SetIsAnimate(false);
	}
}

void CLeverBox::UpdateDoorState()
{
	if (m_bGateOpen == false && m_eGateState == EGateState::CLOSED)
	{
		m_wpLeverGate.lock()->SetActorPosition({ 
			m_wpLeverGate.lock()->GetActorPosition().x,
			m_wpLeverGate.lock()->GetActorPosition().y + m_fLeverUpdatePosY, 
			m_wpLeverGate.lock()->GetActorPosition().z });

		if (m_wpLeverGate.lock()->GetActorPosition().y >= 34.5f)
		{
			m_eGateState = EGateState::STOPPED;
			m_wpSoundComponent.lock()->StopSoundEx(ESoundType::BGM);
		}
	}
	else if (m_bGateOpen == true && m_eGateState == EGateState::OPENED)
	{
		m_wpLeverGate.lock()->SetActorPosition({ 
			m_wpLeverGate.lock()->GetActorPosition().x,
			m_wpLeverGate.lock()->GetActorPosition().y - m_fLeverUpdatePosY, 
			m_wpLeverGate.lock()->GetActorPosition().z });

		if (m_wpLeverGate.lock()->GetActorPosition().y <= -38.f)
		{
			m_eGateState = EGateState::STOPPED;
			m_wpSoundComponent.lock()->StopSoundEx(ESoundType::BGM);
		}
	}
}

