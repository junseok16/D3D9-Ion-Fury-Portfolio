// Default
#include "pch.h"
#include "BossFireGunTask.h"

// Manager
#include "TimerManager.h"

// Component
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"

// Framework
#include "Level.h"
#include "Actor.h"

// Client
#include "WarmechBullet.h"
using namespace std;

int32 CBossFireGunTask::s_iBulletCounter = 0;

void CBossFireGunTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CBossFireGunTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CBossFireGunTask::UpdateTask()
{
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// �÷��̾� ��ġ�� ���մϴ�.
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrTargetKey);
	vDst.y -= vDst.y;

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// �������� �÷��̾�� ���ϴ� ���� ���͸� ���մϴ�.
	FVector3 vDir = vDst - spActor->GetActorWorldPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	FVector3 vUp = { 0.0f, 1.0f, 0.0f };
	FVector3 vBulletPos;
	D3DXVec3Cross(&vBulletPos, &vDir, &vUp);

	switch (m_eGunFireType)
	{
	// ���� ź�� �����մϴ�.
	case EGunFireType::STRAIGHT:
	{
		m_fSumFireInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
		if (m_fSumFireInterval >= m_fFireInterval)
		{
			shared_ptr<CWarmechBullet> spBossBullet = spActor->GetLevel().lock()->CreateActor<CWarmechBullet>(L"BossBullet" + to_wstring(s_iBulletCounter++), L"Projectile", L"Actor");
			spBossBullet->SetActorPosition(spActor->GetActorPosition() + 20.0f * vBulletPos);
			spBossBullet->SetTarget(nullptr);
			spBossBullet->SetDamage(m_fDamage);
			spBossBullet->SetSpeed(m_fSpeed);
			spBossBullet->Initialize();
			spBossBullet->BeginPlay();

			m_fSumFireInterval = 0.0f;
			++m_iSumBullets;
		}

		// �߻��� ����ü�� ������ �߻��ؾ��� �������� ���� ���
		if (m_iSumBullets < m_iBullets)
		{
			return EBTNodeResult::IN_PROGRESS;
		}

		m_fSumFireInterval = 0.0f;
		m_iSumBullets = 0;
		return EBTNodeResult::SUCCEEDED;
	}
	break;

	// ��� ź�� �����մϴ�.
	case EGunFireType::ROUND:
	{
		
	}
	break;

	default: break;
	}
}
