// Default
#include "pch.h"
#include "WarmechLeg.h"
#include "WarmechHead.h"
#include "PlayerActor.h"

#include "Stage3.h"
#include "OutGameUI.h"

// Manager
#include "CollisionManager.h"
#include "InputManager.h"

// Component
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"
#include "PhysicsComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"
#include "ParticleComponent.h"

// Framework
#include "World.h"
#include "Level.h"

// Client
#include "WarmechBullet.h"
#include "WarmechBomb.h"
#include "WarmechMissile.h"
#include "Mechsect.h"
#include "Deacon.h"
using namespace std;

uint32 CWarmechHead::s_iGunBulletCounter = 0;

uint32 CWarmechHead::s_iBombCounter = 0;

uint32 CWarmechHead::s_iMonsterCounter = 0;

void CWarmechHead::Initialize()
{
	AnimationSetting();
	ColliderSetting();
	ParticleSetting(); // 11.20 - 동연 -
	InitializeEffectComponent();
	InitializeSoundComponent();

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CCreature::Initialize();
}

void CWarmechHead::BeginPlay()
{
	FVector3 vHeadPosition = m_wpWarmechLeg.lock()->GetActorPosition() + FVector3(0.0f, 26.0f, 0.0f);
	SetActorPosition(vHeadPosition);

	// 보스 머리 체력을 설정합니다.
	m_fCurHp = 2400.0f;

	// 머리 애니메이션을 바인드합니다.
	{
		// 머리 페이즈0 애니메이션
		m_wpAnimationComponent.lock()->AddState(L"P0HdE_Idle", 0, 0);
		m_wpAnimationComponent.lock()->AddState(L"P0HdE_FireGun", 1, 2);
		m_wpAnimationComponent.lock()->AddState(L"P0HdE_FireMissile", 3, 4);

		m_wpAnimationComponent.lock()->AddState(L"P0HdN_Idle", 5, 5);
		m_wpAnimationComponent.lock()->AddState(L"P0HdN_FireGun", 6, 7);
		m_wpAnimationComponent.lock()->AddState(L"P0HdN_FireMissile", 8, 9);

		m_wpAnimationComponent.lock()->AddState(L"P0HdNE_Idle", 10, 10);
		m_wpAnimationComponent.lock()->AddState(L"P0HdNE_FireGun", 11, 12);
		m_wpAnimationComponent.lock()->AddState(L"P0HdNE_FireMissile", 13, 14);

		m_wpAnimationComponent.lock()->AddState(L"P0HdNW_Idle", 15, 15);
		m_wpAnimationComponent.lock()->AddState(L"P0HdNW_FireGun", 16, 17);
		m_wpAnimationComponent.lock()->AddState(L"P0HdNW_FireMissile", 18, 19);

		m_wpAnimationComponent.lock()->AddState(L"P0HdS_Idle", 20, 20);
		m_wpAnimationComponent.lock()->AddState(L"P0HdS_FireGun", 21, 22);
		m_wpAnimationComponent.lock()->AddState(L"P0HdS_FireMissile", 23, 24);

		m_wpAnimationComponent.lock()->AddState(L"P0HdSE_Idle", 25, 25);
		m_wpAnimationComponent.lock()->AddState(L"P0HdSE_FireGun", 26, 27);
		m_wpAnimationComponent.lock()->AddState(L"P0HdSE_FireMissile", 28, 29);

		m_wpAnimationComponent.lock()->AddState(L"P0HdSW_Idle", 30, 30);
		m_wpAnimationComponent.lock()->AddState(L"P0HdSW_FireGun", 31, 32);
		m_wpAnimationComponent.lock()->AddState(L"P0HdSW_FireMissile", 33, 34);

		m_wpAnimationComponent.lock()->AddState(L"P0HdW_Idle", 35, 35);
		m_wpAnimationComponent.lock()->AddState(L"P0HdW_FireGun", 36, 37);
		m_wpAnimationComponent.lock()->AddState(L"P0HdW_FireMissile", 38, 39);

		// 머리 페이즈1애니메이션
		m_wpAnimationComponent.lock()->AddState(L"P1HdE_Idle", 40, 40);
		m_wpAnimationComponent.lock()->AddState(L"P1HdE_FireGun", 41, 42);
		m_wpAnimationComponent.lock()->AddState(L"P1HdE_FireMissile", 43, 44);

		m_wpAnimationComponent.lock()->AddState(L"P1HdN_Idle", 45, 45);
		m_wpAnimationComponent.lock()->AddState(L"P1HdN_FireGun", 46, 47);
		m_wpAnimationComponent.lock()->AddState(L"P1HdN_FireMissile", 48, 49);

		m_wpAnimationComponent.lock()->AddState(L"P1HdNE_Idle", 50, 50);
		m_wpAnimationComponent.lock()->AddState(L"P1HdNE_FireGun", 51, 52);
		m_wpAnimationComponent.lock()->AddState(L"P1HdNE_FireMissile", 53, 54);

		m_wpAnimationComponent.lock()->AddState(L"P1HdNW_Idle", 55, 55);
		m_wpAnimationComponent.lock()->AddState(L"P1HdNW_FireGun", 56, 57);
		m_wpAnimationComponent.lock()->AddState(L"P1HdNW_FireMissile", 58, 59);

		m_wpAnimationComponent.lock()->AddState(L"P1HdS_Idle", 60, 60);
		m_wpAnimationComponent.lock()->AddState(L"P1HdS_FireGun", 61, 62);
		m_wpAnimationComponent.lock()->AddState(L"P1HdS_FireMissile", 63, 64);

		m_wpAnimationComponent.lock()->AddState(L"P1HdSE_Idle", 65, 65);
		m_wpAnimationComponent.lock()->AddState(L"P1HdSE_FireGun", 66, 67);
		m_wpAnimationComponent.lock()->AddState(L"P1HdSE_FireMissile", 68, 69);

		m_wpAnimationComponent.lock()->AddState(L"P1HdSW_Idle", 70, 70);
		m_wpAnimationComponent.lock()->AddState(L"P1HdSW_FireGun", 71, 72);
		m_wpAnimationComponent.lock()->AddState(L"P1HdSW_FireMissile", 73, 74);

		m_wpAnimationComponent.lock()->AddState(L"P1HdW_Idle", 75, 75);
		m_wpAnimationComponent.lock()->AddState(L"P1HdW_FireGun", 76, 77);
		m_wpAnimationComponent.lock()->AddState(L"P1HdW_FireMissile", 78, 79);

		// 머리 페이즈2 애니메이션
		m_wpAnimationComponent.lock()->AddState(L"P2HdE_Idle", 80, 80);
		m_wpAnimationComponent.lock()->AddState(L"P2HdE_FireGun", 81, 82);
		m_wpAnimationComponent.lock()->AddState(L"P2HdE_FireMissile", 83, 84);

		m_wpAnimationComponent.lock()->AddState(L"P2HdN_Idle", 85, 85);
		m_wpAnimationComponent.lock()->AddState(L"P2HdN_FireGun", 86, 87);
		m_wpAnimationComponent.lock()->AddState(L"P2HdN_FireMissile", 88, 89);

		m_wpAnimationComponent.lock()->AddState(L"P2HdNE_Idle", 90, 90);
		m_wpAnimationComponent.lock()->AddState(L"P2HdNE_FireGun", 91, 92);
		m_wpAnimationComponent.lock()->AddState(L"P2HdNE_FireMissile", 93, 94);

		m_wpAnimationComponent.lock()->AddState(L"P2HeadNW_Idle", 95, 95);
		m_wpAnimationComponent.lock()->AddState(L"P2HeadNW_FireGun", 96, 97);
		m_wpAnimationComponent.lock()->AddState(L"P2HeadNW_FireMissile", 98, 99);

		m_wpAnimationComponent.lock()->AddState(L"P2HdS_Idle", 100, 100);
		m_wpAnimationComponent.lock()->AddState(L"P2HdS_FireGun", 101, 102);
		m_wpAnimationComponent.lock()->AddState(L"P2HdS_FireMissile", 103, 104);

		m_wpAnimationComponent.lock()->AddState(L"P2HdSE_Idle", 105, 105);
		m_wpAnimationComponent.lock()->AddState(L"P2HdSE_FireGun", 106, 107);
		m_wpAnimationComponent.lock()->AddState(L"P2HdSE_FireMissile", 108, 109);

		m_wpAnimationComponent.lock()->AddState(L"P2HdSW_Idle", 110, 110);
		m_wpAnimationComponent.lock()->AddState(L"P2HdSW_FireGun", 111, 112);
		m_wpAnimationComponent.lock()->AddState(L"P2HdSW_FireMissile", 113, 114);

		m_wpAnimationComponent.lock()->AddState(L"P2HdW_Idle", 115, 115);
		m_wpAnimationComponent.lock()->AddState(L"P2HdW_FireGun", 116, 117);
		m_wpAnimationComponent.lock()->AddState(L"P2HdW_FireMissile", 118, 119);
	}

	// 플레이어를 불러옵니다.
	m_wpPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));

	// 사운드 컴포넌트를 설정합니다.
	m_wpSoundComponent.lock()->SetSoundComponentInfo(m_wpPlayer.lock()->GetCurCamera(), EDistanceModel::Linear, 1.0f, 300.0f, 0.0f, 100.0f);
	
	// 보스 머리의 최대 체력을 설정합니다.
	m_wpOutGameUI = dynamic_pointer_cast<CStage3>(GetLevel().lock())->GetOutGameUI();
	m_wpOutGameUI.lock()->InitBossMonsterInfo(m_fCurHp * 2);

	CCreature::BeginPlay();
}

int32 CWarmechHead::Update(const float& _fDeltaSeconds)
{
	float fDeltaSeconds = _fDeltaSeconds;
	if (m_bIsTimeSlipped)
	{
		fDeltaSeconds /= 50.0f;
	}

	UpdateHeadPosition();
	UpdateHeadPhase(fDeltaSeconds);
	UpdateHeadState(fDeltaSeconds);
	UpdateHeadDirection();
	UpdateHeadAnim();
	return CMonster::Update(fDeltaSeconds);
}

int32 CWarmechHead::LateUpdate(const float& _fDeltaSeconds)
{
	float fDeltaSeconds = _fDeltaSeconds;
	if (m_bIsTimeSlipped)
	{
		fDeltaSeconds /= 50.0f;
	}

	SetBillboard(m_wpAnimationComponent);
	SetBillboard(m_wpEffectComponent);
	return CMonster::LateUpdate(fDeltaSeconds);
}

void CWarmechHead::Render()
{
	CMonster::Render();
}

void CWarmechHead::EndPlay()
{
	CMonster::EndPlay();
}

void CWarmechHead::Release()
{
	CMonster::Release();
}

void CWarmechHead::SetWarmechLeg(std::shared_ptr<CWarmechLeg> _spWarmechLeg)
{
	m_wpWarmechLeg = _spWarmechLeg;
}

void CWarmechHead::UpdateHeadPosition()
{
	SetActorPosition(m_wpWarmechLeg.lock()->GetActorPosition() + FVector3(0.0f, 25.5f, 0.0f));
}

void CWarmechHead::UpdateHeadPhase(float _fDeltaSeconds)
{
	switch (m_eCurWarmechHeadPhase)
	{
	case EWarmechPhase::READY:
		break;

	case EWarmechPhase::PHASE_0:
		if (m_fCurHp <= 1200.0f)
		{
			SetMonsterPhase((int32)EWarmechPhase::PHASE_1);
			SetMonsterState((int32)EWarmechHeadState::RESERVE);
			m_ePostWarmechHeadState = EWarmechHeadState::FIRE_PARABOLA_BOMB;
			m_fReserveDeltaSeconds = 3.0f;
			m_bIsCalled = false;
		}
		break;

	case EWarmechPhase::PHASE_1:
		if (m_fCurHp <= 1.0f)
		{
			SetMonsterPhase((int32)EWarmechPhase::DEAD);
			SetMonsterState((int32)EWarmechHeadState::RESERVE);
			m_ePostWarmechHeadState = EWarmechHeadState::SELF_DESTRUCT;
			m_fReserveDeltaSeconds = 0.5f;
			m_bIsCalled = false;
		}
		break;

	case EWarmechPhase::DEAD:
		m_fCurHp = 1.0f;
		break;
	}
}

void CWarmechHead::UpdateHeadState(float _fDeltaSeconds)
{
	switch (m_eCurWarmechHeadState)
	{
	case EWarmechHeadState::IDLE:
		break;

	case EWarmechHeadState::RESERVE:
		Reserve(_fDeltaSeconds);
		break;

	case EWarmechHeadState::FIRE_STRAIGHT_GUN:
		FireGun(EFireType::STRAIGHT, _fDeltaSeconds);
		break;

	case EWarmechHeadState::FIRE_STRAIGHT_MISSILE:
		FireMissile(EFireType::STRAIGHT, _fDeltaSeconds);
		break;

	case EWarmechHeadState::FIRE_PARABOLA_BOMB:
		FireBomb(EFireType::PARABOLA, _fDeltaSeconds);
		break;

	case EWarmechHeadState::SPAWN_MONSTER:
		SpawnMonster(_fDeltaSeconds);
		break;

	case EWarmechHeadState::SELF_DESTRUCT:
		SelfDestruct(_fDeltaSeconds);
		break;

	case EWarmechHeadState::DEAD:
		Dead(_fDeltaSeconds);
		break;
	}
}

void CWarmechHead::UpdateHeadAnim()
{
	switch (m_eCurWarmechHeadState)
	{
	case EWarmechHeadState::IDLE:
	case EWarmechHeadState::RESERVE:
	case EWarmechHeadState::SPAWN_MONSTER:
		SetMonsterAnim((int32)EWarmechHeadAnimType::IDLE);
		break;

	case EWarmechHeadState::SELF_DESTRUCT:
		SetMonsterAnim((int32)EWarmechHeadAnimType::IDLE);
		break;

	case EWarmechHeadState::FIRE_STRAIGHT_GUN:
		SetMonsterAnim((int32)EWarmechHeadAnimType::FIRE_GUN);
		break;

	case EWarmechHeadState::FIRE_STRAIGHT_MISSILE:
	case EWarmechHeadState::FIRE_PARABOLA_BOMB:
		SetMonsterAnim((int32)EWarmechHeadAnimType::FIRE_MISSILE);
		break;
	}
}

void CWarmechHead::UpdateHeadDirection()
{
	// 페이즈를 업데이트합니다.
	if (m_ePrevWarmechHeadPhase == m_eCurWarmechHeadPhase) { return; }

	switch (m_eCurWarmechHeadPhase)
	{
	case EWarmechPhase::READY: break;
	case EWarmechPhase::PHASE_0: UpdateHeadDirectionByPhase(0); break;
	case EWarmechPhase::DEAD:
	case EWarmechPhase::PHASE_1: UpdateHeadDirectionByPhase(1); break;
	}
}

void CWarmechHead::UpdateHeadDirectionByPhase(uint32 _iPhaseIndex)
{
	const wstring& wstrPhaseIndex = L"P" + to_wstring(_iPhaseIndex);

	// 애니메이션을 업데이트합니다.
	switch (m_eCurWarmechHeadAnimType)
	{
	case EWarmechHeadAnimType::IDLE:		m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"HdS_Idle");		break;
	case EWarmechHeadAnimType::FIRE_GUN:	m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"HdS_FireGun");	break;
	case EWarmechHeadAnimType::FIRE_MISSILE:
	case EWarmechHeadAnimType::FIRE_BOMB:	m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"HdS_FireMissile");break;
	default: break;
	}
}

int32 CWarmechHead::GetRandomInteger(int32 _iMin, int32 _iMax)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int32> distribution(_iMin, _iMax);
	return distribution(gen);
}

float CWarmechHead::GetRandomFloat(float _fMin, float _fMax)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> distribution(_fMin, _fMax);
	return distribution(gen);
}

void CWarmechHead::Reserve(float _fDeltaSeconds)
{
	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= m_fReserveDeltaSeconds)
	{
		m_fReserveDeltaSeconds = 3.0f;
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)m_ePostWarmechHeadState);
	}
}

void CWarmechHead::FireGun(EFireType _eFireType, float _fDeltaSeconds)
{
	// 보스에서 플레이어로 향하는 방향 벡터를 구합니다.
	FVector3 vDir = m_wpPlayer.lock()->GetActorPosition() - GetActorPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	FVector3 vUp = { 0.0f, 1.0f, 0.0f };
	FVector3 vBulletPos;
	D3DXVec3Cross(&vBulletPos, &vDir, &vUp);

	switch (_eFireType)
	{
	case EFireType::STRAIGHT:
	{
		m_fSumGunFireInterval += _fDeltaSeconds;
		if (m_fSumGunFireInterval >= m_fGunFireInterval)
		{
			shared_ptr<CWarmechBullet> spBossBullet = GetLevel().lock()->CreateActor<CWarmechBullet>(L"BossBullet" + to_wstring(s_iGunBulletCounter++), L"Projectile", L"Actor");
			spBossBullet->SetActorPosition(GetActorPosition() + 20.0f * vBulletPos);
			spBossBullet->SetTarget(m_wpPlayer.lock());
			spBossBullet->SetDamage(m_fGunDamage);
			spBossBullet->SetSpeed(m_fGunSpeed);

			if (m_bIsTimeSlipped) { spBossBullet->SetIsTimeSlipped(true); }
			spBossBullet->Initialize();
			spBossBullet->BeginPlay();

			m_wpSoundComponent.lock()->PlaySoundByDistance("mech_mgun", ESoundType::FIRE);
			m_fSumGunFireInterval = 0.0f;
			++m_iSumGunBullets;
		}

		// 발사한 투사체의 개수가 발사해야할 개수보다 많은 경우
		if (m_iSumGunBullets >= m_iGunBullets)
		{
			m_fSumGunFireInterval = 0.0f;
			m_iSumGunBullets = 0;

			if (++m_iFireGunCounter >= 3)
			{
				SetMonsterState((int32)EWarmechHeadState::RESERVE);
				m_ePostWarmechHeadState = EWarmechHeadState::SPAWN_MONSTER;
				m_fReserveDeltaSeconds = 2.0f;
				m_iFireGunCounter = 0;
			}
			else
			{
				SetMonsterState((int32)EWarmechHeadState::RESERVE);
				m_ePostWarmechHeadState = EWarmechHeadState::FIRE_STRAIGHT_GUN;
				m_fReserveDeltaSeconds = 3.0f;
			}
		}
	}
	break;

	case EFireType::ROUND:
		break;
	}
}

void CWarmechHead::FireBomb(EFireType _eFireType, float _fDeltaSeconds)
{
	// 보스에서 플레이어로 향하는 방향 벡터를 구합니다.
	FVector3 vDir = m_wpPlayer.lock()->GetActorPosition() - GetActorPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	FVector3 vUp = { 0.0f, 1.0f, 0.0f };

	FVector3 vBombPos;
	D3DXVec3Cross(&vBombPos, &vDir, &vUp);

	switch (_eFireType)
	{
	case EFireType::STRAIGHT:
		break;

	case EFireType::PARABOLA:
	{
		m_fSumBombFireInterval += _fDeltaSeconds;
		if (m_fSumBombFireInterval >= m_fBombFireInterval)
		{
			FVector3 vDir = m_wpPlayer.lock()->GetActorPosition() - GetActorPosition();
			D3DXVec3Normalize(&vDir, &vDir);

			// 머리의 현재 위치에서 폭탄을 생성합니다.
			shared_ptr<CWarmechBomb> spBossBomb = GetLevel().lock()->CreateActor<CWarmechBomb>(L"BossBomb" + to_wstring(s_iBombCounter++), L"Projectile", L"Actor");
			spBossBomb->SetActorPosition(GetActorPosition() - 20.0f * vBombPos);
			spBossBomb->SetTarget(m_wpPlayer.lock());
			spBossBomb->SetDamage(m_fBombDamage);
			spBossBomb->SetSpeed(m_fBombSpeed);
			spBossBomb->SetDirection(vDir);
			if (m_bIsTimeSlipped)
				spBossBomb->SetIsTimeSlipped(true);
			spBossBomb->Initialize();
			spBossBomb->BeginPlay();

			m_wpSoundComponent.lock()->PlaySoundByDistance("mech_grenadelaunch", ESoundType::FIRE);
			m_fSumBombFireInterval = 0.0f;
			++m_iSumBombs;
		}

		// 발사한 투사체의 개수가 발사해야할 개수보다 많은 경우
		if (m_iSumBombs >= m_iBombs)
		{
			m_fSumBombFireInterval = 0.0f;
			m_iSumBombs = 0;

			if (++m_iFireBombCounter >= 3)
			{
				SetMonsterState((int32)EWarmechHeadState::RESERVE);
				m_ePostWarmechHeadState = EWarmechHeadState::SPAWN_MONSTER;
				m_fReserveDeltaSeconds = 2.0f;
				m_iFireBombCounter = 0;
			}
			else
			{
				SetMonsterState((int32)EWarmechHeadState::RESERVE);
				m_ePostWarmechHeadState = EWarmechHeadState::FIRE_PARABOLA_BOMB;
				m_fReserveDeltaSeconds = 3.0f;
			}
		}
	}
	break;

	case EFireType::ROUND:
		break;
	}
}

void CWarmechHead::FireMissile(EFireType _eFireType, float _fDeltaSeconds)
{
	switch (_eFireType)
	{
	case EFireType::STRAIGHT:
		break;

	case EFireType::ROUND:
		break;
	}
}

void CWarmechHead::SpawnMonster(float _fDeltaSeconds)
{
	switch (m_eCurWarmechHeadPhase)
	{
	case EWarmechPhase::PHASE_1:
	{
		for (uint32 iNumMonster = 0; iNumMonster < m_iNumMonsters; ++iNumMonster)
		{
			float fWidthOffset = GetRandomFloat(-1.0f, 1.0f);
			float fHeightOffset = GetRandomFloat(-1.0f, 1.0f);

			shared_ptr<CMechsect> spMechsect = GetLevel().lock()->CreateActor<CMechsect>(L"Mechsect" + to_wstring(s_iMonsterCounter++), L"Monster", L"Actor");
			FVector3 vPosition = FVector3(m_fWidth / 2 * fWidthOffset, 50.0f, m_fHeight / 2 * fHeightOffset);
			spMechsect->SetActorPosition(vPosition);
			spMechsect->SetActorScale({ 16.0f, 16.0f, 16.0f });

			if (m_bIsTimeSlipped)
			{
				spMechsect->SetIsTimeSlipped(true);
			}
			spMechsect->Initialize();
			spMechsect->BeginPlay();
		}

		SetMonsterState((int32)EWarmechHeadState::RESERVE);
		m_ePostWarmechHeadState = EWarmechHeadState::FIRE_PARABOLA_BOMB;
		m_fReserveDeltaSeconds = 3.0f;
	}
	break;

	case EWarmechPhase::PHASE_0:
	{
		for (uint32 iNumMonster = 0; iNumMonster < m_iNumMonsters; ++iNumMonster)
		{
			float fWidthOffset = GetRandomFloat(-1.0f, 1.0f);
			float fHeightOffset = GetRandomFloat(-1.0f, 1.0f);

			shared_ptr<CDeacon> spDeacon = GetLevel().lock()->CreateActor<CDeacon>(L"Deacon" + to_wstring(s_iMonsterCounter++), L"Monster", L"Actor");
			FVector3 vPosition = FVector3(m_fWidth / 2 * fWidthOffset, 20.0f, m_fHeight / 2 * fHeightOffset);
			spDeacon->SetActorPosition(vPosition);
			spDeacon->SetActorScale({ 20.0f, 20.0f, 20.0f });

			if (m_bIsTimeSlipped)
			{
				spDeacon->SetIsTimeSlipped(true);
			}
			spDeacon->Initialize();
			spDeacon->BeginPlay();
		}

		SetMonsterState((int32)EWarmechHeadState::RESERVE);
		m_ePostWarmechHeadState = EWarmechHeadState::FIRE_STRAIGHT_GUN;
		m_fReserveDeltaSeconds = 3.0f;
	}
	break;
	}
}

void CWarmechHead::SelfDestruct(float _fDeltaSeconds)
{
	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= 0.5f)
	{
		// Z 파이팅이 발생하지 않도록 합니다.
		float fOffsetX = GetRandomFloat(-0.2f, 0.2f);
		float fOffsetY = GetRandomFloat(-0.2f, 0.1f);
		float fOffsetZ = GetRandomFloat(-0.2f, 0.2f);
		float fOffsetS = GetRandomFloat(0.2f, 0.3f);

		m_wpEffectComponent.lock()->SetComponentLocalPosition({ fOffsetX, fOffsetY, fOffsetZ });
		m_wpEffectComponent.lock()->SetComponentScale({ fOffsetS, fOffsetS, fOffsetS });

		m_wpEffectComponent.lock()->SetIsAnimate(true);
		m_wpEffectComponent.lock()->SetIsRender(true);
		m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
		m_wpEffectComponent.lock()->SetFrame(0, 0, m_wpEffectComponent.lock()->GetFileEndIndex());
		m_wpEffectComponent.lock()->SetCurrentState(L"Explode");

		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_gun_explosion", ESoundType::FIRE);

		m_fSumDeltaSeconds = 0.0f;
	}
}

void CWarmechHead::Dead(float _fDeltaSeconds)
{

}

/********************
	Component
********************/
void CWarmechHead::InitializeEffectComponent()
{
	// 이펙트 컴포넌트
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	m_wpEffectComponent.lock()->SetComponentScale({ 4.0f, 4.0f, 4.0f });
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"Explosion0_0", 0, 63, L"Idle", EAnimationType::DESIGNATED_TIME, 1.0f);
	m_wpEffectComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpEffectComponent.lock()->AddState(L"Explode", 31, 63);
	m_wpEffectComponent.lock()->SetIsAnimate(false);
	m_wpEffectComponent.lock()->SetIsRender(false);
	m_wpEffectComponent.lock()->SetAnimationCount(0);
	m_wpEffectComponent.lock()->SetFrame(0, 0, 0);
	SetRootComponent(m_wpEffectComponent.lock());
}

void CWarmechHead::InitializeSoundComponent()
{
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
}

void CWarmechHead::AnimationSetting()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"HeadAnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Warmech0_0", 0, 119, L"P0HdS_Idle", EAnimationType::LOOP, 0.5f);
	SetRootComponent(m_wpAnimationComponent);
}

void CWarmechHead::ColliderSetting()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"HeadCubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetComponentScale({ 0.3f, 0.3f, 0.3f });
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CWarmechHead::ParticleSetting()
{
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetIsRemove(true);							// 파티클 라이프타임이 끝나면 삭제시킬 것인지
	m_wpParticleComponent.lock()->SetIsActive(false);							// 파티클 활성화
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Fragment0_0", 0, 0);	// 파티클 텍스처 정보
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::ERUPTION, 32); // 파티클 타입, 개수
	m_wpParticleComponent.lock()->SetParticleSize(1.0f);						// 파티클 크기
	m_wpParticleComponent.lock()->SetParticleLifeTime(1.0f);					// 파티클 라이프타임
	m_wpParticleComponent.lock()->SetParticleSpeed(1.0f);						// 파티클 진행 속도
	m_wpParticleComponent.lock()->SetParticleAcceleration(0.2f);				// 파티클 진행 가속도
	m_wpParticleComponent.lock()->SetParticleCreateTime(0.2f);					// (0 ~ 매개변수)까지 시간 중에서 랜덤하게 생성됨
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeXZ(1.0f);				// x,z 좌표 퍼짐 정도
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeY(0.5f);				// y 좌표 퍼짐 정도
}

void CWarmechHead::SetMonsterState(int32 _iMonsterState)
{
	// 현재 상태와 같은 경우
	if (m_eCurWarmechHeadState == (EWarmechHeadState)_iMonsterState) { return; }

	// 현재 상태를 갱신합니다.
	m_ePrevWarmechHeadState = m_eCurWarmechHeadState;
	m_eCurWarmechHeadState = (EWarmechHeadState)_iMonsterState;
}

int32 CWarmechHead::GetMonsterState() const
{
	return (int32)m_eCurWarmechHeadState;
}

void CWarmechHead::SetMonsterPhase(int32 _iMonsterPhase)
{
	// 현재 페이즈와 같은 페이즈인 경우
	if (m_eCurWarmechHeadPhase == (EWarmechPhase)_iMonsterPhase) { return; }

	// 현재 페이즈를 갱신합니다.
	m_ePrevWarmechHeadPhase = m_eCurWarmechHeadPhase;
	m_eCurWarmechHeadPhase = (EWarmechPhase)_iMonsterPhase;
}

int32 CWarmechHead::GetMonsterPhase() const
{
	return (int32)m_eCurWarmechHeadPhase;
}

void CWarmechHead::SetMonsterAnim(int32 _iMonsterAnim)
{
	if (m_eCurWarmechHeadAnimType == (EWarmechHeadAnimType)_iMonsterAnim) { return; }

	m_ePrevWarmechHeadAnimType = m_eCurWarmechHeadAnimType;
	m_eCurWarmechHeadAnimType = (EWarmechHeadAnimType)_iMonsterAnim;
}

int32 CWarmechHead::GetMonsterAnim() const
{
	return (int32)m_eCurWarmechHeadAnimType;
}

void CWarmechHead::GetDamaged(const float& _fDamage)
{

	m_fCurHp -= _fDamage;

	if (m_fCurHp <= 1.0f)
	{
		m_fCurHp = 1.0f;
		return;
	}
	m_wpOutGameUI.lock()->ActivateBossHpBar();
	m_wpOutGameUI.lock()->SetBossMonsterHpBar(_fDamage);

	// [ 사운드 ]
	m_wpSoundComponent.lock()->PlaySoundByDistance("mech_hit2", ESoundType::DAMAGE);

	// [ 파티클 ]
	// 1. 피격 UV좌표를 가져온다.
	FVector3 vHittedPos = m_wpCubeColliderComponent.lock()->GetRayHittedPos();

	// 2. 해당 좌표에서 액터의 중점 좌표를 빼서 방향 벡터를 구한다.
	FVector3 vHittedDir = vHittedPos - GetActorWorldPosition();

	// D3DXVec3Normalize(&vHittedDir, &vHittedDir); -> 정규화를 해줘야하나?
	// 액터 스케일값으로 나눠줄까?
	vHittedDir.x /= m_vScale.x;
	vHittedDir.y /= m_vScale.y;
	vHittedDir.z /= m_vScale.z;

	// 3. 파티클 컴포넌트의 SetOrigin을 호출해서, 해당 방향벡터를 넣어준다.
	m_wpParticleComponent.lock()->SetParticleOrigin(vHittedDir);

	// 4. 파티클을 생성한다.
	m_wpParticleComponent.lock()->SetIsActive(true);
	m_wpParticleComponent.lock()->AddParticle();
}

int32 CWarmechHead::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	m_bIsCollided = true;
	return 0;
}

void CWarmechHead::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{

}

void CWarmechHead::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	m_bIsCollided = false;
}
