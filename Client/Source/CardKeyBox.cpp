#include "pch.h"
#include "CardKeyBox.h"

// Level
#include "Level.h"

// Actor
#include "Actor.h"
#include "OutGameUI.h"
#include "LeverGate.h"
#include "PlayerActor.h"
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

void CCardKeyBox::Initialize()
{
	InGameSetting();

	ColliderSetting();

	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
	m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSoundComponent);

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CCardKeyBox::BeginPlay()
{
	m_wpOutGameUI = dynamic_pointer_cast<COutGameUI>(GetLevel().lock()->FindActor(L"OutGameUI"));
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));

	m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 1.f, 10.f, 1.f, 90.f);

	m_wpCardKeyBox.lock()->AddState(L"CardKeyBox", 0, 3);
	m_wpCardKeyBox.lock()->SetFrameTime(L"CardKeyBox", 0, 3, 0.4f);	

	m_wpCardKeyBox.lock()->AddState(L"CardKeyBox1", 5, 5);
	m_wpCardKeyBox.lock()->SetFrameTime(L"CardKeyBox1", 5, 5, 0.f);

	CInteractiveBox::BeginPlay();
}

int32 CCardKeyBox::Update(const float& _fDeltaSeconds)
{
	KeyInput();
	UpdateDoorState();
	//m_wpSoundComponent.lock()->Update(_fDeltaSeconds);
	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CCardKeyBox::LateUpdate(const float& _fDeltaSeconds)
{
	m_wpCardKeyBox.lock()->SetIsAnimate(true);
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CCardKeyBox::Render()
{
	CInteractiveBox::Render();
}

void CCardKeyBox::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CCardKeyBox::Release()
{
	CInteractiveBox::Release();
}

void CCardKeyBox::KeyInput()
{
	FVector3 fv = m_wpPlayerActor.lock()->GetActorWorldPosition() - m_wpCardKeyBox.lock()->GetOwnerActor().lock()->GetActorWorldPosition();
	float fDis = D3DXVec3Length(&fv);

	m_wpOutGameUI.lock()->SetDisCardKeyActor(fDis);

	if (m_bGateOpen == true && m_eGateState == EGateState::STOPPED && CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f /*&& ±§º±√Êµπ*/)
	{
		m_bGateOpen = false;
		m_eGateState = EGateState::CLOSED;
		m_wpCardKeyBox.lock()->SetIsAnimate(true);
		m_wpCardKeyBox.lock()->SetFrameTime(L"CardKeyBox0", 0, 4, 0.4f);
		m_wpSoundComponent.lock()->PlayBGMByDistance("Door_Stone", 80.f);


	}
	else if (m_bGateOpen == false && m_eGateState == EGateState::STOPPED && CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f /*&& ±§º±√Êµπ*/)
	{
		if (m_wpPlayerActor.lock()->GetCardKeyItem() == 0)
		{
			m_wpCardKeyBox.lock()->SetIsAnimate(false);
			m_wpCardKeyBox.lock()->SetCurFrame(4);
			m_wpSoundComponent.lock()->PlayPlayerSound("keycard_locked", 80.f, ESoundType::ITEM);
		}
		else if (m_wpPlayerActor.lock()->GetCardKeyItem() == 1)
		{
			m_wpCardKeyBox.lock()->SetIsAnimate(false);
			m_wpCardKeyBox.lock()->SetCurFrame(4);
			m_wpSoundComponent.lock()->PlayPlayerSound("keycard_locked", 80.f, ESoundType::ITEM);
		}
		else if (m_wpPlayerActor.lock()->GetCardKeyItem() == 2)
		{
			m_bGateOpen = true;
			m_eGateState = EGateState::OPENED;
			m_wpCardKeyBox.lock()->SetIsAnimate(false);
			m_wpCardKeyBox.lock()->SetCurFrame(5);
			m_wpSoundComponent.lock()->PlayBGMByDistance("Door_Stone", 80.f); 
			m_wpSoundComponent.lock()->PlayPlayerSound("keycard_unlock", 80.f, ESoundType::ITEM); 
		}

	}
}

void CCardKeyBox::InGameSetting()
{
	m_wpCardKeyBox = CreateActorComponent<CAnimationComponent>(L"CardKeyBoxComponent");
	SetRootComponent(m_wpCardKeyBox);
	m_wpCardKeyBox.lock()->SettingAnimationInfo(L"CardKeyBox0_", 0, 5, L"CardKeyBox", EAnimationType::LOOP, 0.4f);
	m_wpCardKeyBox.lock()->SetIsAnimate(true);
	//m_fCardKeyGateBeginPosY = m_wpCardKeyBox.lock()->GetOwnerActor().lock()->GetActorPosition().y;
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpCardKeyBox.lock());
}

void CCardKeyBox::ColliderSetting()
{
	// ¿∞∏È√º ƒ›∂Û¿Ã¥ı
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpCardKeyBox);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CCardKeyBox::UpdateDoorState()
{
	if (m_bGateOpen == false && m_eGateState == EGateState::CLOSED)
	{
		//m_fCardKeyGateUpdatePosY += 0.1f;
		m_wpCardKeyGate.lock()->SetActorPosition({ 
			m_wpCardKeyGate.lock()->GetActorPosition().x,
			m_wpCardKeyGate.lock()->GetActorPosition().y + m_fCardKeyGateUpdatePosY, 
			m_wpCardKeyGate.lock()->GetActorPosition().z });


		if (m_wpCardKeyGate.lock()->GetActorPosition().y >= 18.f)
		{
			m_eGateState = EGateState::STOPPED;
			m_wpSoundComponent.lock()->StopSoundEx(ESoundType::BGM);
		}
	}
	else if (m_bGateOpen == true && m_eGateState == EGateState::OPENED)
	{
		m_wpCardKeyGate.lock()->SetActorPosition({ 
			m_wpCardKeyGate.lock()->GetActorPosition().x,
			m_wpCardKeyGate.lock()->GetActorPosition().y - m_fCardKeyGateUpdatePosY,
			m_wpCardKeyGate.lock()->GetActorPosition().z });

		if (m_wpCardKeyGate.lock()->GetActorPosition().y <= -23.f)
		{
			m_eGateState = EGateState::STOPPED;
			m_wpSoundComponent.lock()->StopSoundEx(ESoundType::BGM);
		}
	}
}
