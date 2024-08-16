#include "pch.h"
#include "BossFireBombTask.h"

// Manager
#include "TimerManager.h"

// Component
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"

// Framework
#include "Level.h"
#include "Actor.h"

// Client
#include "WarmechMissile.h"
#include "WarmechBomb.h"
using namespace std;

int32 CBossFireBombTask::s_iBombCounter = 0;

void CBossFireBombTask::Initialize()
{
	CBTTaskNode::Initialize();
}

EBTNodeResult CBossFireBombTask::UpdateTask()
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
	FVector3 vBombDir = vDir + vUp;

	FVector3 vBombPos;
	D3DXVec3Cross(&vBombPos, &vUp, &vDir);

	switch (m_eBombFireType)
	{
	// ���� �̻����� �����մϴ�.
	case EBombFireType::STRAIGHT:
	{
		m_fSumFireInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
		if (m_fSumFireInterval >= m_fFireInterval)
		{
			shared_ptr<CWarmechMissile> spBossMissile = spActor->GetLevel().lock()->CreateActor<CWarmechMissile>(L"BossMissile" + to_wstring(s_iBombCounter++), L"Projectile", L"Actor");
			spBossMissile->SetActorPosition(spActor->GetActorPosition());
			spBossMissile->SetTarget(nullptr);
			spBossMissile->SetDamage(m_fDamage);
			spBossMissile->SetSpeed(m_fSpeed);
			spBossMissile->Initialize();
			spBossMissile->BeginPlay();

			m_fSumFireInterval = 0.0f;
			++m_iSumBombs;
		}

		// �߻��� ����ü�� ������ �߻��ؾ��� �������� ���� ���
		if (m_iSumBombs < m_iBombs)
		{
			return EBTNodeResult::IN_PROGRESS;
		}

		m_iSumBombs = 0;
		return EBTNodeResult::SUCCEEDED;
	}
	break;

	// ������ �̻����� �����մϴ�.
	case EBombFireType::PARABOLA:
	{
		m_fSumFireInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
		if (m_fSumFireInterval >= m_fFireInterval)
		{
			FVector3 vBombDirs[3] = { vBombDir - 0.3f * vBombPos, vBombDir, vBombDir + 0.3f * vBombPos };
			FVector3 vBombUps[3] = { { 0.0f, -0.2f, 0.0f }, { 0.0f, 0.2f, 0.0f } };

			for (int32 i = 0; i < 2; ++i)
			{
				// �Ӹ��� ���� ��ġ���� ��ź�� �����մϴ�.
				shared_ptr<CWarmechBomb> spBossBomb = spActor->GetLevel().lock()->CreateActor<CWarmechBomb>(L"BossBomb" + to_wstring(s_iBombCounter++), L"Projectile", L"Actor");
				spBossBomb->SetActorPosition(spActor->GetActorPosition() + 18 * vBombPos + vBombUps[i]);
				spBossBomb->SetTarget(nullptr);
				spBossBomb->SetDamage(m_fDamage);
				spBossBomb->SetSpeed(m_fSpeed);
				spBossBomb->SetDirection(vBombDirs[i]);

				spBossBomb->Initialize();
				spBossBomb->BeginPlay();
			}
			
			m_fSumFireInterval = 0.0f;
			++m_iSumBombs;
		}

		// �߻��� ����ü�� ������ �߻��ؾ��� �������� ���� ���
		if (m_iSumBombs < m_iBombs) { return EBTNodeResult::IN_PROGRESS; }

		m_iSumBombs = 0;
		return EBTNodeResult::SUCCEEDED;
	}
		break;

	default: break;
	}
}

void CBossFireBombTask::Release()
{
	CBTTaskNode::Release();
}
