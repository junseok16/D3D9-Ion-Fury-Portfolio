#include "pch.h"
#include "ElevatorKeyBox1.h"

// Level
#include "Level.h"

// Actor
#include "Actor.h"
#include "OutGameUI.h"
#include "PlayerActor.h"
#include "ElevatorFloor.h"
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

void CElevatorKeyBox1::Initialize()
{
	InGameSetting();

	ColliderSetting(); 
	
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
	m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSoundComponent);

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CElevatorKeyBox1::BeginPlay()
{
	m_wpOutGameUI = dynamic_pointer_cast<COutGameUI>(GetLevel().lock()->FindActor(L"OutGameUI"));
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 1.f, 30.f, 1.f, 90.f);

	m_wpElevatorKeyBox.lock()->AddState(L"ElevatorKeyBox", 0, 3);
	m_wpElevatorKeyBox.lock()->SetFrameTime(L"ElevatorKeyBox", 0, 3, 0.4f);

	m_wpElevatorKeyBox.lock()->AddState(L"ElevatorKeyBox1", 5, 5);
	m_wpElevatorKeyBox.lock()->SetFrameTime(L"ElevatorKeyBox1", 5, 5, 0.f);

	CInteractiveBox::BeginPlay();
}

int32 CElevatorKeyBox1::Update(const float& _fDeltaSeconds)
{
	KeyInput();
	UpdateDoorState();

	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CElevatorKeyBox1::LateUpdate(const float& _fDeltaSeconds)
{
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CElevatorKeyBox1::Render()
{
	CInteractiveBox::Render();
}

void CElevatorKeyBox1::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CElevatorKeyBox1::Release()
{
	CInteractiveBox::Release();
}

void CElevatorKeyBox1::KeyInput()
{
	FVector3 fv = m_wpPlayerActor.lock()->GetActorWorldPosition() - m_wpElevatorKeyBox.lock()->GetOwnerActor().lock()->GetActorWorldPosition();
	float fDis = D3DXVec3Length(&fv);

	m_wpOutGameUI.lock()->SetDisElevatorButtonActor1(fDis);

	if (m_wpElevatorFloor.lock()->GetGateOpen() == true && m_wpElevatorFloor.lock()->GetGateState() == EGateState::STOPPED 
		&& CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f )
	{
		m_wpElevatorFloor.lock()->SetGateOpen(false); 
		m_wpElevatorFloor.lock()->SetGateState(EGateState::CLOSED);

		m_wpElevatorKeyBox.lock()->SetIsAnimate(false);
		m_wpElevatorKeyBox.lock()->SetCurFrame(5);

		m_wpSoundComponent.lock()->PlayBGMByDistance("Elevator_Move", 80.f);
		m_wpSoundComponent.lock()->PlayPlayerSound("keycard_unlock", 80.f, ESoundType::ITEM);
	}
}

void CElevatorKeyBox1::InGameSetting()
{
	m_wpElevatorKeyBox = CreateActorComponent<CAnimationComponent>(L"ElevatorKeyBoxComponent");
	SetRootComponent(m_wpElevatorKeyBox);
	m_wpElevatorKeyBox.lock()->SettingAnimationInfo(L"CardKeyBox0_", 0, 5, L"ElevatorKeyBox", EAnimationType::LOOP, 0.4f);
	m_wpElevatorKeyBox.lock()->SetIsAnimate(true);
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpElevatorKeyBox.lock());
}

void CElevatorKeyBox1::ColliderSetting()
{
}

void CElevatorKeyBox1::UpdateDoorState()
{
	if (m_wpElevatorFloor.lock()->GetGateOpen() == false && m_wpElevatorFloor.lock()->GetGateState() == EGateState::CLOSED)
	{
		m_wpElevatorFloor.lock()->SetActorPosition({ m_wpElevatorFloor.lock()->GetActorPosition().x,
		m_wpElevatorFloor.lock()->GetActorPosition().y - m_fElevatorFloorMovementY,
		m_wpElevatorFloor.lock()->GetActorPosition().z });

		m_wpPlayerActor.lock()->SetActorPosition({ m_wpPlayerActor.lock()->GetActorPosition().x,
			m_wpPlayerActor.lock()->GetActorPosition().y - m_fElevatorFloorMovementY + 0.54f,
			m_wpPlayerActor.lock()->GetActorPosition().z });

		if (m_wpElevatorFloor.lock()->GetActorPosition().y <= 0.f)
		{
			m_wpElevatorFloor.lock()->SetGateState(EGateState::STOPPED);
			m_wpElevatorKeyBox.lock()->SetIsAnimate(true);
			m_wpElevatorKeyBox.lock()->SetFrameTime(L"CardKeyBox0", 0, 4, 0.4f);
			m_wpSoundComponent.lock()->StopSoundEx(ESoundType::BGM);
		}
	}
}
