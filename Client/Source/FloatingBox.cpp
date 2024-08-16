// Default
#include "pch.h"
#include "FloatingBox.h"

// Framework
#include "Level.h"

// Component
#include "CubeMeshComponent.h"
#include "CubeColliderComponent.h"

// Manager
#include "CollisionManager.h"
#include "TimerManager.h"
#include "InputManager.h"

// Client
#include "FlameEmitter.h"
#include "LaserEmitter.h"
using namespace std;

/********************
	Framework
********************/
void CFloatingBox::Initialize()
{
	InitializeCubeMeshComponent();
	InitializeCubeColliderComponent();

	SetRenderType(ERenderType::NON_ALPHA);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CFloatingBox::BeginPlay()
{
	SetActorScale({ 36.0f, 72.0f, 36.0f });

	for (int32 iIndex = 0; iIndex < 2; ++iIndex)
	{
		for (int32 jIndex = 0; jIndex < 2; ++jIndex)
		{
			const wstring& wstrName = GetActorName() + L"FlameEmitter" + to_wstring(iIndex) + to_wstring(jIndex);

			m_wpFlameEmitter[iIndex][jIndex] = GetLevel().lock()->CreateActor<CFlameEmitter>(wstrName, L"Gimmick", L"Actor");
			m_wpFlameEmitter[iIndex][jIndex].lock()->SetFloatingBox(dynamic_pointer_cast<CActor>(shared_from_this()));
			m_wpFlameEmitter[iIndex][jIndex].lock()->SetEmitterIndex(iIndex * 2 + jIndex);
			m_wpFlameEmitter[iIndex][jIndex].lock()->Initialize();
			m_wpFlameEmitter[iIndex][jIndex].lock()->BeginPlay();
		}
	}
	
	//for (int32 iIndex = 0; iIndex < 4; ++iIndex)
	//{
	int32 iIndex = 0;
		const wstring& wstrName = GetActorName() + L"LaserEmitter" + to_wstring(iIndex);

		m_wpLaserEmitter[iIndex] = GetLevel().lock()->CreateActor<CLaserEmitter>(wstrName, L"Gimmick", L"Actor");
		m_wpLaserEmitter[iIndex].lock()->SetFloatingBox(dynamic_pointer_cast<CActor>(shared_from_this()));
		m_wpLaserEmitter[iIndex].lock()->SetLaserEmitterType((ELaserEmitterType)iIndex);
		m_wpLaserEmitter[iIndex].lock()->Initialize();
		m_wpLaserEmitter[iIndex].lock()->BeginPlay();
	//}

	// 발판을 분리하고 결합하기 위해 방향 벡터를 구합니다.
	m_vSeparatingDir = GetActorPosition() - FVector3(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&m_vSeparatingDir, &m_vSeparatingDir);
	m_vCombiningDir = -m_vSeparatingDir;

	CCubeColliderActor::BeginPlay();
}

int32 CFloatingBox::Update(const float& _fDeltaSeconds)
{
	UpdateFloatingBoxState(_fDeltaSeconds);
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CFloatingBox::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CFloatingBox::Render()
{
	CCubeColliderActor::Render();
}

void CFloatingBox::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CFloatingBox::Release()
{
	CCubeColliderActor::Release();
}

/********************
	Component
********************/
void CFloatingBox::InitializeCubeMeshComponent()
{
	m_wpCubeMeshComponent = CreateActorComponent<CCubeMeshComponent>(L"CubeMeshComponent");
	m_wpCubeMeshComponent.lock()->SetCubeMeshInfo(L"FloatingBox0_0");
	SetRootComponent(m_wpCubeMeshComponent);
}

void CFloatingBox::InitializeCubeColliderComponent()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpCubeMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::ITEM);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CFloatingBox::UpdateFloatingBoxState(float _fDeltaSeconds)
{
	FVector3 vPos = GetActorPosition();

	// 발판을 올립니다.
	switch (m_eCurFloatingBoxState)
	{
	case EFloatingBoxState::ASCENDING:
	{
		vPos += FVector3(0.0f, 1.0f, 0.0f) * _fDeltaSeconds * m_fSpeed;
		SetActorPosition(vPos);

		if (vPos.y >= 0.0f)
		{
			SetActorPosition({ vPos.x, 0.0f, vPos.z });
			m_eCurFloatingBoxState = EFloatingBoxState::ASCEND;
			m_ePrevFloatingBoxState = EFloatingBoxState::ASCENDING;
		}
	}
	break;

	// 발판을 내립니다.
	case EFloatingBoxState::DESCENDING:
	{
		vPos += FVector3(0.0f, -1.0f, 0.0f) * _fDeltaSeconds * m_fSpeed;
		SetActorPosition(vPos);

		if (vPos.y <= -36.0f)
		{
			SetActorPosition({ vPos.x, -36.0f, vPos.z });
			m_eCurFloatingBoxState = EFloatingBoxState::DESCEND;
			m_ePrevFloatingBoxState = EFloatingBoxState::DESCENDING;
		}
	}
	break;

	case EFloatingBoxState::SEPARATING:
	{
		// 짝수 발판인 경우
		if (m_iFloatingBoxIndex % 2 == 0)
		{
			vPos += m_vSeparatingDir * _fDeltaSeconds * m_fSpeed;
			SetActorPosition(vPos);

			FVector3 vDist = m_vTranslate - FVector3(0.0f, 0.0f, 0.0f);
			float fDist = D3DXVec3Length(&vDist);

			if (fDist >= 101.82f)
			{
				m_eCurFloatingBoxState = EFloatingBoxState::SEPARATE;
				m_ePrevFloatingBoxState = EFloatingBoxState::SEPARATING;
			}
		}
		// 홀수 발판인 경우
		else
		{
			vPos += m_vSeparatingDir * _fDeltaSeconds * m_fSpeed;
			SetActorPosition(vPos);

			FVector3 vDist = m_vTranslate - FVector3(0.0f, 0.0f, 0.0f);
			float fDist = D3DXVec3Length(&vDist);

			if (fDist >= 72.0f)
			{
				m_eCurFloatingBoxState = EFloatingBoxState::SEPARATE;
				m_ePrevFloatingBoxState = EFloatingBoxState::SEPARATING;
			}
		}
	}
	break;

	case EFloatingBoxState::COMBINING:
	{
		vPos += m_vCombiningDir * _fDeltaSeconds * m_fSpeed;
		SetActorPosition(vPos);

		FVector3 vDist = m_vTranslate - FVector3(0.0f, 0.0f, 0.0f);
		float fDist = D3DXVec3Length(&vDist);

		// 짝수 발판인 경우
		if (m_iFloatingBoxIndex % 2 == 0)
		{
			if (fDist <= 50.91f)
			{
				m_eCurFloatingBoxState = EFloatingBoxState::COMBINE;
				m_ePrevFloatingBoxState = EFloatingBoxState::COMBINING;
			}
		}
		// 홀수 발판인 경우
		else
		{
			if (fDist <= 36.0f)
			{
				m_eCurFloatingBoxState = EFloatingBoxState::COMBINE;
				m_ePrevFloatingBoxState = EFloatingBoxState::COMBINING;
			}
		}
	}
	break;

	case EFloatingBoxState::FLAME_ON:
	{
		for (int32 iIndex = 0; iIndex < 2; ++iIndex)
		{
			for (int32 jIndex = 0; jIndex < 2; ++jIndex)
			{
				m_wpFlameEmitter[iIndex][jIndex].lock()->SetFlameEmitterState(EFlameEmitterState::FLAME_ON);
			}
		}
	}
	break;


	case EFloatingBoxState::FLAME_OFF:
	{
		for (int32 iIndex = 0; iIndex < 2; ++iIndex)
		{
			for (int32 jIndex = 0; jIndex < 2; ++jIndex)
			{
				m_wpFlameEmitter[iIndex][jIndex].lock()->SetFlameEmitterState(EFlameEmitterState::FLAME_OFF);
			}
		}
	}
	break;

	case EFloatingBoxState::LASER_ON:
	{
		for (int32 iIndex = 0; iIndex < 4; ++iIndex)
		{
			m_wpLaserEmitter[iIndex].lock()->SetLaserEmitterState(ELaserEmitterState::LASER_ON);
		}
	}
	break;


	case EFloatingBoxState::LASER_OFF:
	{
		for (int32 iIndex = 0; iIndex < 4; ++iIndex)
		{
			m_wpLaserEmitter[iIndex].lock()->SetLaserEmitterState(ELaserEmitterState::LASER_OFF);
		}
	}
	break;
	}
}

void CFloatingBox::SetFloatingBoxState(EFloatingBoxState _eFloatingBoxState)
{
	if (m_eCurFloatingBoxState == _eFloatingBoxState) { return; }
	
	m_ePrevFloatingBoxState = m_eCurFloatingBoxState;
	m_eCurFloatingBoxState = _eFloatingBoxState;
}

/********************
	Callbacks
********************/
int32 CFloatingBox::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CFloatingBox::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CFloatingBox::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}
