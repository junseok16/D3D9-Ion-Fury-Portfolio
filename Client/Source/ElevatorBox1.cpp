#include "pch.h"
#include "ElevatorBox1.h"

// Level
#include "Level.h"

// Actor
#include "Actor.h"
#include "OutGameUI.h"
#include "PlayerActor.h"
#include "ElevatorFloor.h"
#include "CubeColliderActor.h"


// Component
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "CubeMeshComponent.h"
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"


// Manager
#include "InputManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"


using namespace std;

void CElevatorBox1::Initialize()
{
	InGameSetting();

	ColliderSetting();

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CElevatorBox1::BeginPlay()
{
	m_wpOutGameUI = dynamic_pointer_cast<COutGameUI>(GetLevel().lock()->FindActor(L"OutGameUI"));
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	//m_wpPhysicsComponent = dynamic_pointer_cast<CPhysicsComponent>(GetLevel().lock()->FindActor(L"PhysicsComponent"));

	m_wpElevatorBox.lock()->AddState(L"ElevatorBox", 0, 5);


	//m_wpElevatorBox.lock()->SetOwnerComponent(m_wpElevatorFloor);

	CInteractiveBox::BeginPlay();
}

int32 CElevatorBox1::Update(const float& _fDeltaSeconds)
{
	KeyInput();
	UpdateDoorState();
	//SetElevatorEndFrame();

	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CElevatorBox1::LateUpdate(const float& _fDeltaSeconds)
{
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CElevatorBox1::Render()
{
	CInteractiveBox::Render();
}

void CElevatorBox1::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CElevatorBox1::Release()
{
	CInteractiveBox::Release();
}

int32 CElevatorBox1::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CElevatorBox1::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	// 큐브 충돌
	//if (EColliderType::CUBE == _wpSrcCollider.lock()->GetColliderType()
	//	&& EColliderType::CUBE == _wpDstCollider.lock()->GetColliderType())
	//{
	//	CCollisionManager::BlockCubeToCube
	//	(
	//		dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
	//		dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
	//		m_fSpeed
	//	);
	//}
}

void CElevatorBox1::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return;
}

void CElevatorBox1::KeyInput()
{
	FVector3 fv = m_wpPlayerActor.lock()->GetActorWorldPosition() - m_wpElevatorBox.lock()->GetOwnerActor().lock()->GetActorWorldPosition();
	float fDis = D3DXVec3Length(&fv);

	m_wpOutGameUI.lock()->SetDisElevatorButtonActor(fDis);

	if (m_bGateOpen == true && m_eGateState == EGateState::STOPPED && CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f /*&& 광선충돌*/)
	{
		m_bGateOpen = false;
		m_eGateState = EGateState::CLOSED;
		m_wpElevatorBox.lock()->SetCurFrame(0);
	}
	else if (m_bGateOpen == false && m_eGateState == EGateState::STOPPED && CInputManager::GetInstance()->IsKeyDown(DIK_F) && fDis <= 50.f /*&& 광선충돌*/)
	{
		m_bGateOpen = true;
		m_eGateState = EGateState::OPENED;
		m_wpElevatorBox.lock()->SetIsAnimate(true);
	}
}

void CElevatorBox1::InGameSetting()
{
	//m_wpElevatorBox = CreateActorComponent<CAnimationComponent>(L"ElevatorBoxComponent");
	//SetRootComponent(m_wpElevatorBox);
	//m_wpElevatorBox.lock()->SettingAnimationInfo(L"ElevatorBox0_", 0, 5, L"ElevatorBox", EAnimationType::LOOP, 0.5f);
	//m_wpElevatorBox.lock()->SetIsAnimate(true);
	//m_wpElevatorFloor.lock()->SetOwnerActor(m_wpElevatorBox.lock()->GetOwnerActor());


	m_wpElevatorBox = CreateActorComponent<CAnimationComponent>(L"ElevatorBoxComponent");
	SetRootComponent(m_wpElevatorBox);
	m_wpElevatorBox.lock()->SettingAnimationInfo(L"ElevatorBoxSR0_", 0, 5, L"ElevatorBoxSR", EAnimationType::LOOP, 0.5f);
	m_wpElevatorBox.lock()->SetIsAnimate(true);
	//m_wpElevatorFloor.lock()->SetOwnerActor(m_wpElevatorBox.lock()->GetOwnerActor());

	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpElevatorBox.lock());
}

void CElevatorBox1::ColliderSetting()
{
	// 육면체 콜라이더
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpElevatorBox);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	//m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CElevatorBox1::SetElevatorEndFrame()
{
	std::wstring wstrCurrentState = m_wpElevatorBox.lock()->GetCurrentState();
	int32 iEndFrame = m_wpElevatorBox.lock()->GetStateFrame(wstrCurrentState).second;

	if (m_wpElevatorBox.lock()->GetCurFrame() == iEndFrame)
	{
		m_wpElevatorBox.lock()->SetIsAnimate(false);
	}
}

shared_ptr<CCubeColliderActor> CElevatorBox1::HitScanBox()
{
	FVector3 vFoward = m_wpPlayerActor.lock()->GetForwardVector();
	FVector3 vActorPos = m_wpPlayerActor.lock()->GetActorPosition();

	std::weak_ptr<CActor> wpHitedActor = CCollisionManager::IntersectRayToCollider(vActorPos, vFoward, dynamic_pointer_cast<CActor>(m_wpPlayerActor.lock()));
	if (wpHitedActor.expired())
		return nullptr;

	std::weak_ptr<CCubeColliderActor> wpHitedCubeActor = dynamic_pointer_cast<CCubeColliderActor>(wpHitedActor.lock());

	if (wpHitedCubeActor.expired())
		return nullptr;

	//std::weak_ptr<CCreature> wpHitedCreature = dynamic_pointer_cast<CCreature>(wpHitedActor.lock());
	//std::weak_ptr<CItemObjectActor> wpHitedItemObject = dynamic_pointer_cast<CItemObjectActor>(wpHitedActor.lock());	// 임시
	//
	//// 맞은 대상이 크리처나 아이템 오브젝트가 아닌 경우 예외처리
	//if (wpHitedCreature.expired() || wpHitedItemObject.expired())
	//	return nullptr;

	return wpHitedCubeActor.lock();
}

void CElevatorBox1::UpdateDoorState()
{
	if (m_bGateOpen == false && m_eGateState == EGateState::CLOSED)
	{
		m_wpElevatorFloor.lock()->SetActorPosition({ m_wpElevatorFloor.lock()->GetActorPosition().x,
			m_wpElevatorFloor.lock()->GetActorPosition().y - m_fElevatorFloorMovementY,
			m_wpElevatorFloor.lock()->GetActorPosition().z });

		m_wpPlayerActor.lock()->SetActorPosition({ m_wpPlayerActor.lock()->GetActorPosition().x,
			m_wpPlayerActor.lock()->GetActorPosition().y - m_fElevatorFloorMovementY,
			m_wpPlayerActor.lock()->GetActorPosition().z });

		if (m_wpElevatorFloor.lock()->GetActorPosition().y <= 0.f)
		{
			m_eGateState = EGateState::STOPPED;
		}
	}
	//else if (m_bGateOpen == true && m_eGateState == EGateState::OPENED)
	//{
	//	//m_wpPlayerActor.lock()->SetActorPosition({ m_wpPlayerActor.lock()->GetActorPosition().x,
	//	//	m_wpPlayerActor.lock()->GetActorPosition().y + m_fElevatorFloorMovementY ,
	//	//	m_wpPlayerActor.lock()->GetActorPosition().z });
	//   //
	//	m_wpElevatorFloor.lock()->SetActorPosition({ m_wpElevatorFloor.lock()->GetActorPosition().x,
	//	m_wpElevatorFloor.lock()->GetActorPosition().y + m_fElevatorFloorMovementY,
	//	m_wpElevatorFloor.lock()->GetActorPosition().z });
	//
	//
	//	if (m_wpElevatorFloor.lock()->GetActorPosition().y >= 160.f)
	//	{
	//		m_eGateState = EGateState::STOPPED;
	//	}
	//}
}
