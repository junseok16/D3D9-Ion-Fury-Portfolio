#include "pch.h"
#include "LaserEmitter.h"

#include "AnimationComponent.h"
#include "CubeColliderComponent.h"

#include "CollisionManager.h"
using namespace std;

void CLaserEmitter::Initialize()
{
	InitializeAnimationComponent();
	InitializeCubeColliderComponent();

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CLaserEmitter::BeginPlay()
{
	switch (m_eLaserEmitterType)
	{
	case ELaserEmitterType::VERTICAL:
	{
		SetActorRotation({ 90.0f, 90.0f, 0.0f });
		m_vDir = FVector3(+1.0f, 0.0f, 0.0f);
	}
	break;

	case ELaserEmitterType::HORIZONTAL:
	{
		SetActorRotation({ 90.0f, 0.0f, 0.0f });
		m_vDir = FVector3(0.0f, 0.0f, 1.0f);
	}
	break;

	case ELaserEmitterType::UP_DIAGONAL:
	{
		SetActorRotation({ 90.0f, -45.0f, 0.0f });
		m_vDir = FVector3(1.0f, 0.0f, -1.0f);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
	}
	break;

	case ELaserEmitterType::DOWN_DIAGONAL:
	{
		SetActorRotation({ 90.0f, 45.0f, 0.0f });
		m_vDir = FVector3(1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
	}
	break;
	}

	SetActorScale({ 42.0f, 8.0f, 8.0f });

	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 7);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");
	CCubeColliderActor::BeginPlay();
}

int32 CLaserEmitter::Update(const float& _fDeltaSeconds)
{
	UpdateEmitterPosition(_fDeltaSeconds);
	UpdateEmitterState();
	UpdateEmitterAnim();
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CLaserEmitter::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CLaserEmitter::Render()
{
	CCubeColliderActor::Render();
}

void CLaserEmitter::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CLaserEmitter::Release()
{
	CCubeColliderActor::Release();
}

/********************
	Component
********************/
void CLaserEmitter::InitializeAnimationComponent()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Laser1_0", 0, 7, L"Idle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);
}

void CLaserEmitter::InitializeCubeColliderComponent()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PROJECTILE);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

/********************
	Callbacks
********************/
int32 CLaserEmitter::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	switch (m_eLaserEmitterState)
	{
	case ELaserEmitterState::LASER_ON:
		// TODO: 플레이어의 체력을 감소시킵니다.
		break;
	}
	return 0;
}

void CLaserEmitter::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	switch (m_eLaserEmitterState)
	{
	case ELaserEmitterState::LASER_ON:
		// TODO: 플레이어의 체력을 감소시킵니다.
		break;
	}
}

/********************
	Methods
********************/
void CLaserEmitter::UpdateEmitterPosition(float _fDeltaSeconds)
{
	FVector3 vPos = m_wpFloatingBox.lock()->GetActorPosition();

	if (m_eLaserEmitterState == ELaserEmitterState::LASER_OFF)
	{
		switch (m_eLaserEmitterType)
		{
		case ELaserEmitterType::VERTICAL:		SetActorPosition(vPos + FVector3(-28.0f, 36.2f, 0.0f)); break;
		case ELaserEmitterType::HORIZONTAL:		SetActorPosition(vPos + FVector3(0.0f, 36.2f, -28.0f)); break;
		case ELaserEmitterType::UP_DIAGONAL:	SetActorPosition(vPos + FVector3(-28.0f, 36.2f, 28.0f)); break;
		case ELaserEmitterType::DOWN_DIAGONAL:	SetActorPosition(vPos + FVector3(-28.0f, 36.2f, -28.0f)); break;
		}
	}
	else if (m_eLaserEmitterState == ELaserEmitterState::LASER_ON)
	{
		switch (m_eLaserEmitterType)
		{
		case ELaserEmitterType::VERTICAL:		MoveVertical(_fDeltaSeconds);		break;
		case ELaserEmitterType::HORIZONTAL:		MoveHorizontal(_fDeltaSeconds);		break;
		case ELaserEmitterType::UP_DIAGONAL:	MoveUpDiagonal(_fDeltaSeconds);		break;
		case ELaserEmitterType::DOWN_DIAGONAL:	MoveDownDiagonal(_fDeltaSeconds);	break;
		}
	}
	
}

void CLaserEmitter::UpdateEmitterState()
{
	
}

void CLaserEmitter::UpdateEmitterAnim()
{
	switch (m_eLaserEmitterState)
	{
	case ELaserEmitterState::LASER_ON:
		m_wpAnimationComponent.lock()->SetIsRender(true);
		break;

	case ELaserEmitterState::LASER_OFF:
		m_wpAnimationComponent.lock()->SetIsRender(false);
		break;
	}
}

void CLaserEmitter::MoveVertical(float _fDeltaSeconds)
{
	m_vPos += m_vDir * m_fSpeed * _fDeltaSeconds;
	SetActorPosition(m_vPos);
}

void CLaserEmitter::MoveHorizontal(float _fDeltaSeconds)
{
}

void CLaserEmitter::MoveUpDiagonal(float _fDeltaSeconds)
{
}

void CLaserEmitter::MoveDownDiagonal(float _fDeltaSeconds)
{
}
