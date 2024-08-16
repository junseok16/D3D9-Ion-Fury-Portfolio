
#include "pch.h"
#include "LoverboyActor.h"

#include "ResourceManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TimerManager.h"
#include "InputManager.h"

#include "Level.h"
#include "Actor.h"
#include "Creature.h"
#include "PlayerActor.h"
#include "PlayerEffectActor.h"
#include "ItemObjectActor.h"

#include "AnimationComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"
#include "OutGameUI.h"

#include "CubeColliderComponent.h"

using namespace std;

void CLoverboyActor::Initialize()
{
	m_eWeaponType = EWeaponType::LOVERBOY;

	m_iDamage = 30;
	m_iBulletLoaded = 6;
	m_iBulletHolding = 200;
	m_iMagazine = 6;
	m_iBulletMaximum = 90;

	m_vBasePosition = { 100.0f, -150.f, 5.0f };

	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SetIsRootComponent(true);
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Loverboy_", 0 , 15, L"Idle", EAnimationType::LOOP, 1.0f);

	m_wpAnimationComponent.lock()->SetComponentScale({ 6.0f, 6.0f, 6.0f });

	// ����: �Ѿ� �߻�
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
	m_wpSoundComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);

	CWeaponActor::Initialize();
}

void CLoverboyActor::BeginPlay()
{
	m_wpPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));

	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpAnimationComponent.lock()->AddState(L"Attack1", 1, 7);
	m_wpAnimationComponent.lock()->AddState(L"AutoAttack", 1, 4);
	m_wpAnimationComponent.lock()->AddState(L"Reload", 8, 15);

	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 1, 1, 0.05f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 2, 7, 0.03f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"AutoAttack", 1, 1, 0.05f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"AutoAttack", 2, 4, 0.03f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Reload", 12, 13, 0.15f);

	m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 1.0f, 10.0f, 0.0f, 100.0f);
	CWeaponActor::BeginPlay();
}

int32 CLoverboyActor::Update(const float& _fDeltaSeconds)
{
	if (m_bEnable)
	{
		AnimationSetting();
		AutoReload();

		if (!m_bAutoAttack)
			LockOn(_fDeltaSeconds);
		else if(m_bAutoAttack)
			AutoAttack();
	}

	return CWeaponActor::Update(_fDeltaSeconds);
}

int32 CLoverboyActor::LateUpdate(const float& _fDeltaSeconds)
{
	CWeaponActor::UpdateFSM();
	return CWeaponActor::LateUpdate(_fDeltaSeconds);
}

void CLoverboyActor::Render()
{
	CWeaponActor::Render();
}

void CLoverboyActor::EndPlay()
{
	CWeaponActor::EndPlay();
}

void CLoverboyActor::Release()
{
	CWeaponActor::Release();
}

void CLoverboyActor::SetFrameInteract(int32 OffFire)
{
	if (m_wpAnimationComponent.lock()->GetCurFrame() == OffFire)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Loverboy_Fire", 100.f, ESoundType::EFFECT);

			m_iBulletLoaded -= 1;
			m_bFrameButton = false;
			// m_wpParticleComponent.lock()->AddParticle();

			weak_ptr<CPlayerActor> wpPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
			weak_ptr<CCubeColliderActor> wpHitedCubeActor = wpPlayer.lock()->HitScan();

			weak_ptr<CCreature> wpHitedCreature;
			weak_ptr<CItemObjectActor> wpHitedItemObjectActor;

			if (wpHitedCubeActor.expired())
				return;

			ECollisionLayerType eTargetCollisionLayer = wpHitedCubeActor.lock()->GetCubeColliderComponent().lock()->GetCollisionLayerType();

			switch (eTargetCollisionLayer)
			{
			case ECollisionLayerType::PLAYER:
			case ECollisionLayerType::GROUND:
			case ECollisionLayerType::WALL:
			case ECollisionLayerType::INTERACTION:
			case ECollisionLayerType::ITEM:
			case ECollisionLayerType::PROJECTILE:
				break;

			case ECollisionLayerType::ITEMOBJECT:
				wpHitedItemObjectActor = dynamic_pointer_cast<CItemObjectActor>(wpHitedCubeActor.lock());
				wpHitedItemObjectActor.lock()->GetDamaged();
				break;

			case ECollisionLayerType::MONSTER:
				wpHitedCreature = dynamic_pointer_cast<CCreature>(wpHitedCubeActor.lock());
				wpHitedCreature.lock()->GetDamaged(GetDamage());
				break;

			default:
				break;
			}
		}
	}

	else if (m_wpAnimationComponent.lock()->GetCurFrame() == OffFire + 1)
	{
		m_bFrameButton = true;
	}
}

void CLoverboyActor::AnimationSetting()
{
	if (m_wpAnimationComponent.lock()->GetCurrentState() == L"Attack1")
	{
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::DESIGNATED_TIME);
		m_wpAnimationComponent.lock()->SetAnimationCount(1);
	}

	if (m_wpAnimationComponent.lock()->GetCurrentState() == L"AutoAttack")
	{
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::DESIGNATED_TIME);
		m_wpAnimationComponent.lock()->SetAnimationCount(2);
	}

	SetFrameInteract(2);

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 9)         // ������
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Loverboy_Reload", 100.f, ESoundType::EFFECT);
			m_bFrameButton = false;
		}
	}
	if (m_wpAnimationComponent.lock()->GetCurFrame() == 10)			// ������
	{
		m_bFrameButton = true;
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 15)      // ������
	{
		Reload();
		SetActivate(true);
	}
}

void CLoverboyActor::AutoReload()
{
	if (m_iBulletLoaded == 0 && m_iBulletHolding > 0 && m_wpAnimationComponent.lock()->GetCurrentState() == L"Idle")
	{
		m_wpAnimationComponent.lock()->SetCurrentState(L"Reload");
	}
}

void CLoverboyActor::LockOn(float _fDeltaSeconds)
{
	if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::RIGHT_BUTTON))
	{
		if (!m_bSeokyangSound)
		{
			// ������ ����
			m_wpSoundComponent.lock()->PlayPlayerSound("Mcree_Seokyang", 50.0f, ESoundType::VOICE);
			m_bSeokyangSound = true;
		}

		// �ڵ����� ȭ�� ����Ʈ on
		dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetEffectVec()[0].lock()->SetIsLockOn(true);

		if (m_lstHitedCreatures.size() >= 3) { return; }
		
		weak_ptr<CCubeColliderActor> wpHitedCubeActor = m_wpPlayer.lock()->HitScan();
		if (wpHitedCubeActor.expired()) return;

		ECollisionLayerType eTargetCollisionLayer = wpHitedCubeActor.lock()->GetCubeColliderComponent().lock()->GetCollisionLayerType();

		switch (eTargetCollisionLayer)
		{
		case ECollisionLayerType::MONSTER:
		{
			shared_ptr<CCreature> spCurHitedCreature = dynamic_pointer_cast<CCreature>(wpHitedCubeActor.lock());

			for (const auto& wpHitedCreature : m_lstHitedCreatures)
			{
				if (wpHitedCreature.lock() == spCurHitedCreature) { return; }
			}

			m_lstHitedCreatures.push_back(spCurHitedCreature);
		}
		break;

		default: break;
		}
	}

	if (CInputManager::GetInstance()->IsMouseUp(EMouseButtonType::RIGHT_BUTTON))
	{
		// �ڵ����� ȭ�� ����Ʈ off
		dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetEffectVec()[0].lock()->SetIsLockOn(false);

		// ������ ���� �� ���
		// m_wpSoundComponent.lock()->PlayPlayerSound("Mcree_EndFire", 50.0f, ESoundType::VOICE);

		m_iPreBulletLoaded = m_iBulletLoaded;
		m_bAutoAttack = true;
		m_bSeokyangSound = false;
	}
}

void CLoverboyActor::AutoAttack()
{
	if (auto iter = m_lstHitedCreatures.begin(); iter == m_lstHitedCreatures.end())
	{
		m_bAutoAttack = false;
		m_lstHitedCreatures.clear();
	}

	if (auto iter = m_lstHitedCreatures.begin(); iter != m_lstHitedCreatures.end())
	{
		if(m_bAutoAttackCycle)
		{
			if (iter->expired())
			{
				m_bAutoAttack = false;
				m_lstHitedCreatures.clear();
				return;
			}

			// ù ��°, �÷��̾��� Y���� �������� ȸ���մϴ�.
			FMatrix matMouseRotate = m_wpPlayer.lock()->GetMouseRotateMatrix();

			// �÷��̾��� ������ ���͸� ����ȭ�մϴ�.
			FVector3 vPlayerForwardY = m_wpPlayer.lock()->GetForwardVector();
			FVector3 vPlayerForwardProjY = { vPlayerForwardY.x, 0.0f, vPlayerForwardY.z };
			D3DXVec3Normalize(&vPlayerForwardProjY, &vPlayerForwardProjY);

			// �÷��̾�� ���ͷ� ���ϴ� ���͸� ����ȭ�մϴ�.
			FVector3 vPlayerToMonster = (*iter).lock()->GetActorPosition() - m_wpPlayer.lock()->GetActorPosition();
			FVector3 vPlayerToMonsterY = { vPlayerToMonster.x, 0.0f, vPlayerToMonster.z };
			D3DXVec3Normalize(&vPlayerToMonsterY, &vPlayerToMonsterY);

			// �� ����(y��)�� �������� ȸ���� ������ ���մϴ�.
			float fYRadian = acos(D3DXVec3Dot(&vPlayerForwardProjY, &vPlayerToMonsterY));
			float fYDegree = D3DXToDegree(fYRadian);

			// ���Ͱ� ���� Ȥ�� �����ʿ� �ִ��� �ľ��մϴ�.
			FVector3 vUp = { 0.0f, 1.0f, 0.0f };
			FVector3 vCrossY;
			D3DXVec3Cross(&vCrossY, &vPlayerForwardProjY, &vPlayerToMonsterY);

			// �� ������ ������ �� ���͸� ������ ���� ���Ͱ� �ü� ���⿡�� ���ʿ� �ִ� ��� �����̰�, �����ʿ� �ִ� ��� ����Դϴ�.
			if (D3DXVec3Dot(&vCrossY, &vUp) < 0.0f) { fYRadian *= -1; fYDegree *= -1; }

			// �� ���� �������� ȸ���� ���콺 ȸ�� ����� �����մϴ�.
			FMatrix matRotateY;
			D3DXMatrixRotationAxis(&matRotateY, &vUp, fYRadian);
			D3DXMatrixMultiply(&matMouseRotate, &matMouseRotate, &matRotateY);


			// �� ��°, �÷��̾��� ����Ʈ ���͸� �������� ȸ���մϴ�.
			FVector3 vPlayerForwardX = { matMouseRotate._31, matMouseRotate._32, matMouseRotate._33 };
			D3DXVec3Normalize(&vPlayerForwardX, &vPlayerForwardX);

			FVector3 vPlayerToMonsterX = vPlayerToMonster;
			D3DXVec3Normalize(&vPlayerToMonsterX, &vPlayerToMonsterX);

			// ����Ʈ ���͸� �������� ȸ���� ������ ���մϴ�.
			float fXRadian = acos(D3DXVec3Dot(&vPlayerForwardX, &vPlayerToMonsterX));
			float fXDegree = D3DXToDegree(fXRadian);

			// ���Ͱ� ���� Ȥ�� �Ʒ��ʿ� �ִ��� �ľ��մϴ�.
			FVector3 vRight = { matMouseRotate._11, matMouseRotate._12, matMouseRotate._13 };
			FVector3 vCrossX;
			D3DXVec3Cross(&vCrossX, &vPlayerForwardX, &vPlayerToMonsterX);

			// �� ������ ������ ����Ʈ ����(right vector)�� ������ ���� ���Ͱ� �ü� ���⿡�� ���ʿ� �ִ� ��� �����̰�, �Ʒ��ʿ� �ִ� ��� ����Դϴ�.
			if (D3DXVec3Dot(&vCrossX, &vRight) < 0.0f) { fXRadian *= -1; fXDegree *= -1; }

			FMatrix matRotateX;
			D3DXMatrixRotationAxis(&matRotateX, &vRight, fXRadian);
			D3DXMatrixMultiply(&matMouseRotate, &matMouseRotate, &matRotateX);
			m_wpPlayer.lock()->SetMouseRotateMatrix(matMouseRotate);

			m_wpAnimationComponent.lock()->SetCurrentState(L"AutoAttack");
			m_bAutoAttackCycle = false;
		}

		// ���� �Ѿ��� 2�� ���ٸ� iter++
		if (m_iBulletLoaded == m_iPreBulletLoaded - 2 || m_iBulletLoaded == 0)
		{
			m_iPreBulletLoaded = m_iBulletLoaded;
			m_bAutoAttackCycle = true;

			m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");
			m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::LOOP);
			m_wpAnimationComponent.lock()->SetCurrentAnimationCount(0);
			m_wpAnimationComponent.lock()->SetCurFrame(m_wpAnimationComponent.lock()->GetStateFrame(L"Idle").first);
			m_wpAnimationComponent.lock()->SetIsAnimate(true);

			m_lstHitedCreatures.pop_front();
		}
	}

}
