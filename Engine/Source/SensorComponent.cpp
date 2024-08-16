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
	// ������ ������ ��ġ�� �ҷ��ɴϴ�.
	FVector3 vSrcPosition = GetOwnerActor().lock()->GetActorWorldPosition();

	for (const auto& pair : m_wpEnterSeeingActors)
	{
		// �ǰ����� ������ ��ġ�� �ҷ��ɴϴ�.
		FVector3 vDstPosition = pair.second.lock()->GetActorWorldPosition();
		FVector3 vDir = vDstPosition - vSrcPosition;

		float fDistance = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		// �ǰ����ڿ� �Ÿ��� �ð� ���������� ū ���
		if (m_fSeeingRadius < fDistance)
		{
			m_eCurSeeingState = ESeeingState::SEE_FAR;

			// ���� ���°� ������� ���
			if (m_ePrevSeeingState == ESeeingState::SEE_NEAR)
			{
				m_ePrevSeeingState = ESeeingState::SEE_FAR;
				for (const auto& pair : m_umapSeeingExitCallbacks)
				{
					m_umapSeeingExitCallbacks[pair.first]();
				}
			}
		}

		// �ǰ����ڿ� �Ÿ��� �ð� ���������� ���� ���
		else if (fDistance <= m_fSeeingRadius)
		{
			m_eCurSeeingState = ESeeingState::SEE_NEAR;

			// ������ ������ ��ġ���� �ǰ����� ��ġ�� ���ͷ� ������ �߻��մϴ�.
			shared_ptr<CActor> spShortestActor = CCollisionManager::IntersectRayToCollider(vSrcPosition, vDir, GetOwnerActor().lock());

			// ������ �浹�� ���Ͱ� �ǰ����ڰ� �ƴ� ���
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
