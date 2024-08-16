#include "pch.h"
#include "SensorComponent.h"

#include "CollisionManager.h"
#include "TimerManager.h"
#include "Actor.h"
using namespace std;

void CSensorComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CSensorComponent::BeginPlay()
{
	CActorComponent::BeginPlay();
}

int32 CSensorComponent::Update(const float& _fDeltaSeconds)
{
	m_fSumInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumInterval >= m_fInterval)
	{
		m_fSumInterval = 0.0f;
		UpdateSeeingActor();
	}

	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CSensorComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CSensorComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CSensorComponent::Render()
{
	CActorComponent::Render();
}

void CSensorComponent::Release()
{
	CActorComponent::Release();
}

void CSensorComponent::UpdateSeeingActor()
{
	// 관찰자 액터의 위치를 불러옵니다.
	FVector3 vSrcPosition = GetOwnerActor().lock()->GetActorWorldPosition();

	for (const auto& pair : m_wpEnterSeeingActors)
	{
		// 피관찰자 액터의 위치를 불러옵니다.
		FVector3 vDstPosition = pair.second.lock()->GetActorWorldPosition();
		FVector3 vDir = vDstPosition - vSrcPosition;

		float fDistance = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		// 피관찰자와 거리가 시각 반지름보다 큰 경우
		if (m_fSeeingRadius < fDistance)
		{
			m_eCurSeeingState = ESeeingState::SEE_FAR;

			// 이전 상태가 가까웠던 경우
			if (m_ePrevSeeingState == ESeeingState::SEE_NEAR)
			{
				m_ePrevSeeingState = ESeeingState::SEE_FAR;
				for (const auto& pair : m_umapSeeingExitCallbacks)
				{
					m_umapSeeingExitCallbacks[pair.first]();
				}
			}
		}

		// 피관찰자와 거리가 시각 반지름보다 작은 경우
		else if (fDistance <= m_fSeeingRadius)
		{
			m_eCurSeeingState = ESeeingState::SEE_NEAR;

			// 관찰자 액터의 위치에서 피관찰자 위치의 액터로 광선을 발사합니다.
			shared_ptr<CActor> spShortestActor = CCollisionManager::IntersectRayToCollider(vSrcPosition, vDir, GetOwnerActor().lock());

			// 광선에 충돌한 액터가 피관찰자가 아닌 경우
			if (spShortestActor != pair.second.lock())
			{
				for (const auto& pair : m_umapSeeingExitCallbacks) { m_umapSeeingExitCallbacks[pair.first](); }
			}
			else
			{
				for (const auto& pair : m_umapSeeingEnterCallbacks) { m_umapSeeingEnterCallbacks[pair.first](); }
				m_ePrevSeeingState = ESeeingState::SEE_NEAR;
			}
		}
	}
}
