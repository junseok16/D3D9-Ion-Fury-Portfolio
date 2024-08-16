// Default
#include "pch.h"
#include "WarmechLeg.h"
#include "WarmechHead.h"

// Manager
#include "CollisionManager.h"
#include "InputManager.h"

// Component
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"
#include "PhysicsComponent.h"
#include "EffectComponent.h"
#include "ParticleComponent.h"
#include "RectangleMeshComponent.h"
#include "CameraComponent.h"
#include "SoundComponent.h"

// Framework
#include "World.h"
#include "Level.h"

// Client
#include "PlayerActor.h"
#include "WarmechSmash.h"
#include "WarmechCharge.h"
#include "OutGameUI.h"
#include "Stage3.h"
using namespace std;

void CWarmechLeg::Initialize()
{
	// ������Ʈ�� �ʱ�ȭ�մϴ�.
	AnimationSetting();
	ColliderSetting();
	PhysicsSetting();
	ParticleSetting();

	// InitializeParticleComponent();
	InitializeEffectComponent();
	InitializeSoundComponent();

	SetRenderType(ERenderType::ALPHA_BLEND);
	SetMobility(EMobilityType::DYNAMIC);
	CMonster::Initialize();
}

void CWarmechLeg::BeginPlay()
{
	// ������ ��ġ�� �����մϴ�.
	SetActorPosition({ 0.0f, 300.0f, 20.0f });
	
	// ���� �ٸ� ü���� �����մϴ�.
	m_fCurHp = 2400.0f;

	// �ٸ� �ִϸ��̼��� ���ε��մϴ�.
	{
		// �ٸ� ������0 �ִϸ��̼�
		m_wpAnimationComponent.lock()->AddState(L"P0LgE_Idle", 0, 0);
		m_wpAnimationComponent.lock()->AddState(L"P0LgE_Walk", 1, 6);

		m_wpAnimationComponent.lock()->AddState(L"P0LgN_Idle", 7, 7);
		m_wpAnimationComponent.lock()->AddState(L"P0LgN_Walk", 8, 13);

		m_wpAnimationComponent.lock()->AddState(L"P0LgNE_Idle", 14, 14);
		m_wpAnimationComponent.lock()->AddState(L"P0LgNE_Walk", 15, 20);

		m_wpAnimationComponent.lock()->AddState(L"P0LgNW_Idle", 21, 21);
		m_wpAnimationComponent.lock()->AddState(L"P0LgNW_Walk", 22, 27);

		m_wpAnimationComponent.lock()->AddState(L"P0LgS_Idle", 28, 28);
		m_wpAnimationComponent.lock()->AddState(L"P0LgS_Walk", 29, 34);

		m_wpAnimationComponent.lock()->AddState(L"P0LgSE_Idle", 35, 35);
		m_wpAnimationComponent.lock()->AddState(L"P0LgSE_Walk", 36, 41);

		m_wpAnimationComponent.lock()->AddState(L"P0LgSW_Idle", 42, 42);
		m_wpAnimationComponent.lock()->AddState(L"P0LgSW_Walk", 43, 48);

		m_wpAnimationComponent.lock()->AddState(L"P0LgW_Idle", 49, 49);
		m_wpAnimationComponent.lock()->AddState(L"P0LgW_Walk", 50, 55);

		// �ٸ� ������1 �ִϸ��̼�
		m_wpAnimationComponent.lock()->AddState(L"P1LgE_Idle", 56, 56);
		m_wpAnimationComponent.lock()->AddState(L"P1LgE_Walk", 57, 62);

		m_wpAnimationComponent.lock()->AddState(L"P1LgN_Idle", 63, 63);
		m_wpAnimationComponent.lock()->AddState(L"P1LgN_Walk", 64, 69);

		m_wpAnimationComponent.lock()->AddState(L"P1LgNE_Idle", 70, 70);
		m_wpAnimationComponent.lock()->AddState(L"P1LgNE_Walk", 71, 76);

		m_wpAnimationComponent.lock()->AddState(L"P1LgNW_Idle", 77, 77);
		m_wpAnimationComponent.lock()->AddState(L"P1LgNW_Walk", 78, 83);

		m_wpAnimationComponent.lock()->AddState(L"P1LgS_Idle", 84, 84);
		m_wpAnimationComponent.lock()->AddState(L"P1LgS_Walk", 85, 90);

		m_wpAnimationComponent.lock()->AddState(L"P1LgSE_Idle", 91, 91);
		m_wpAnimationComponent.lock()->AddState(L"P1LgSE_Walk", 92, 97);

		m_wpAnimationComponent.lock()->AddState(L"P1LgSW_Idle", 98, 98);
		m_wpAnimationComponent.lock()->AddState(L"P1LgSW_Walk", 99, 104);

		m_wpAnimationComponent.lock()->AddState(L"P1LgW_Idle", 105, 105);
		m_wpAnimationComponent.lock()->AddState(L"P1LgW_Walk", 106, 111);
	}
	
	// �÷��̾ �ҷ��ɴϴ�.
	m_wpPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));

	// ���� ������Ʈ�� �����մϴ�.
	m_wpSoundComponent.lock()->SetSoundComponentInfo(m_wpPlayer.lock()->GetCurCamera(), EDistanceModel::Linear, 1.0f, 300.0f, 0.0f, 100.0f);

	// ������ �ִ� ü���� �����մϴ�.
	m_wpOutGameUI = dynamic_pointer_cast<CStage3>(GetLevel().lock())->GetOutGameUI();
	m_wpOutGameUI.lock()->InitBossMonsterInfo(m_fCurHp * 2);

	CMonster::BeginPlay();
}

int32 CWarmechLeg::Update(const float& _fDeltaSeconds)
{
	float fDeltaSeconds = _fDeltaSeconds;
	if (m_bIsTimeSlipped)
	{
		fDeltaSeconds /= 50.0f;
	}

	UpdateLegPhase(fDeltaSeconds);
	UpdateLegState(fDeltaSeconds);
	UpdateLegDirection();
	UpdateLegAnim(fDeltaSeconds);
	
	UpdateSkillPosition(fDeltaSeconds);
	return CMonster::Update(fDeltaSeconds);
}

int32 CWarmechLeg::LateUpdate(const float& _fDeltaSeconds)
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

void CWarmechLeg::Render()
{
	CMonster::Render();
}

void CWarmechLeg::EndPlay()
{
	CMonster::EndPlay();
}

void CWarmechLeg::Release()
{
	CMonster::Release();
}

void CWarmechLeg::UpdateLegPhase(float _fDeltaSeconds)
{
	switch (m_eCurWarmechLegPhase)
	{
	case EWarmechPhase::READY:
		break;

	case EWarmechPhase::PHASE_0:
		if (m_fCurHp <= 1600.0f)
		{
			SetMonsterPhase((int32)EWarmechPhase::PHASE_1);
			SetMonsterState((int32)EWarmechLegState::JUMP_TO_CENTER);
			m_fSumDeltaSeconds = 0.0f;
			m_bIsCalled = false;
		}
		break;

	case EWarmechPhase::PHASE_1:
		if (m_fCurHp <= 800.0f)
		{
			SetMonsterPhase((int32)EWarmechPhase::PHASE_2);
			SetMonsterState((int32)EWarmechLegState::JUMP_TO_CENTER);
			m_fSumDeltaSeconds = 0.0f;
			m_bIsCalled = false;
		}
		break;

	case EWarmechPhase::PHASE_2:
		if (m_fCurHp <= 1.0f)
		{
			m_fCurHp = 1.0f;
			SetMonsterPhase((int32)EWarmechPhase::DEAD);
			SetMonsterState((int32)EWarmechLegState::JUMP_TO_CENTER);
			m_fSumDeltaSeconds = 0.0f;
			m_bIsCalled = false;
		}
		break;

	case EWarmechPhase::DEAD:
		m_fCurHp = 1.0f;
		break;
	}
}

void CWarmechLeg::UpdateLegState(float _fDeltaSeconds)
{
	switch (m_eCurWarmechLegState)
	{
	case EWarmechLegState::IDLE:
		break;

	case EWarmechLegState::RESERVE:
		Reserve(_fDeltaSeconds);
		break;

	case EWarmechLegState::SMASH:
		Smash(_fDeltaSeconds);
		break;

	case EWarmechLegState::SELF_DESTRUCT:
		SelfDestruct(_fDeltaSeconds);
		break;

	case EWarmechLegState::JUMP_TO_CENTER:
		JumpToCenter(_fDeltaSeconds);
		break;

	case EWarmechLegState::MOVE_TO_CENTER:
		MoveToCenter(_fDeltaSeconds);
		break;

	case EWarmechLegState::MOVE_TO_RANDOM:
		MoveToRandom(_fDeltaSeconds);
		break;

	case EWarmechLegState::MOVE_TO_PLAYER:
		MoveToPlayer(_fDeltaSeconds);
		break;

	case EWarmechLegState::MOVE_TO_SELF_DESTRUCT:
		MoveToSelfDestruct(_fDeltaSeconds);
		break;

	case EWarmechLegState::READY_TO_CHARGE:
		ReadyToRush(_fDeltaSeconds);
		break;

	case EWarmechLegState::CHARGE_TO_PLAYER:
		RushToPlayer(_fDeltaSeconds);
		break;

	case EWarmechLegState::BREAK_SAFE_FLOOR:
		BreakSafeFloor(_fDeltaSeconds);
		break;

	case EWarmechLegState::DEAD:
		Dead(_fDeltaSeconds);
		break;
	}
}

void CWarmechLeg::UpdateLegAnim(float _fDeltaSeconds)
{
	switch (m_eCurWarmechLegState)
	{
	case EWarmechLegState::IDLE:
	case EWarmechLegState::RESERVE:
	case EWarmechLegState::JUMP_TO_CENTER:
	case EWarmechLegState::SMASH:
	case EWarmechLegState::READY_TO_CHARGE:
	case EWarmechLegState::SELF_DESTRUCT:
	case EWarmechLegState::BREAK_SAFE_FLOOR:
		SetMonsterAnim((int32)EWarmechLegAnimType::IDLE);
		break;

	case EWarmechLegState::MOVE_TO_CENTER:
	case EWarmechLegState::MOVE_TO_RANDOM:
	case EWarmechLegState::MOVE_TO_PLAYER:
	case EWarmechLegState::MOVE_TO_SELF_DESTRUCT:
		SetMonsterAnim((int32)EWarmechLegAnimType::WALK);
		break;

	case EWarmechLegState::CHARGE_TO_PLAYER:
		SetMonsterAnim((int32)EWarmechLegAnimType::RUN);
		break;
	}
}

void CWarmechLeg::UpdateLegDirection()
{
	if (m_ePrevWarmechLegPhase == m_eCurWarmechLegPhase) { return; }

	switch (m_eCurWarmechLegPhase)
	{
	case EWarmechPhase::READY:
	case EWarmechPhase::PHASE_0: UpdateLegDirectionByPhase(0); break;
	case EWarmechPhase::PHASE_1: UpdateLegDirectionByPhase(1); break;
	case EWarmechPhase::PHASE_2: UpdateLegDirectionByPhase(1); break;
	case EWarmechPhase::DEAD:	 UpdateLegDirectionByPhase(1); break;
	}
}

void CWarmechLeg::UpdateLegDirectionByPhase(uint32 _iPhaseIndex)
{
	const wstring& wstrPhaseIndex = L"P" + to_wstring(_iPhaseIndex);

	FVector3 vPlayerPos = m_wpPlayer.lock()->GetActorWorldPosition();	vPlayerPos.y = 0.0f;
	FVector3 vLegPos = GetActorWorldPosition();							vLegPos.y = 0.0f;
	m_vDst.y = 0.0f;
	FVector3 vLegDir = m_vDst - vLegPos;								vLegDir.y = 0.0f;

	// �ٸ����� �÷��̾�� ���ϴ� ���� ���͸� ���մϴ�.
	FVector3 vLegToPlayer = vPlayerPos - vLegPos;
	D3DXVec3Normalize(&vLegDir, &vLegDir);
	D3DXVec3Normalize(&vLegToPlayer, &vLegToPlayer);

	float fRadian = acos(D3DXVec3Dot(&vLegDir, &vLegToPlayer)) * (180.0f / D3DX_PI);

	FVector3 vCross;
	D3DXVec3Cross(&vCross, &vLegDir, &vLegToPlayer);
	if (vCross.y < 0) { fRadian = 360.0f - fRadian; }

	// �ִϸ��̼��� ������Ʈ�մϴ�.
	switch (m_eCurWarmechLegAnimType)
	{
	case EWarmechLegAnimType::IDLE:
	{
		if ((0.0f <= fRadian && fRadian < 22.5f) || (342.5f <= fRadian && fRadian < 360.0f)) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgS_Idle"); }
		else if (22.5f <= fRadian && fRadian < 67.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgSE_Idle"); }
		else if (67.5f <= fRadian && fRadian < 112.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgE_Idle"); }
		else if (112.5f <= fRadian && fRadian < 157.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgNE_Idle"); }
		else if (157.5f <= fRadian && fRadian < 202.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgN_Idle"); }
		else if (202.5f <= fRadian && fRadian < 247.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgNW_Idle"); }
		else if (247.5f <= fRadian && fRadian < 292.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgW_Idle"); }
		else if (292.5f <= fRadian && fRadian < 342.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgSW_Idle"); }
	}
	break;

	case EWarmechLegAnimType::WALK:
	case EWarmechLegAnimType::RUN:
	{
		if ((0.0f <= fRadian && fRadian < 22.5f) || (342.5f <= fRadian && fRadian < 360.0f)) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgS_Walk"); }
		else if (22.5f <= fRadian && fRadian < 67.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgSE_Walk"); }
		else if (67.5f <= fRadian && fRadian < 112.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgE_Walk"); }
		else if (112.5f <= fRadian && fRadian < 157.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgNE_Walk"); }
		else if (157.5f <= fRadian && fRadian < 202.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgN_Walk"); }
		else if (202.5f <= fRadian && fRadian < 247.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgNW_Walk"); }
		else if (247.5f <= fRadian && fRadian < 292.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgW_Walk"); }
		else if (292.5f <= fRadian && fRadian < 342.5f) { m_wpAnimationComponent.lock()->SetCurrentState(wstrPhaseIndex + L"LgSW_Walk"); }
	}
	break;
	}
}

void CWarmechLeg::UpdateSkillPosition(float _fDeltaSeconds)
{
	if (m_eCurWarmechLegState == EWarmechLegState::SMASH)
	{
		m_wpSmash.lock()->SetActorPosition(GetActorPosition() - FVector3(0.0f, 14.0f, 0.0f));
		m_bIsSmashed = true;
	}
	else
	{
		if (m_bIsSmashed)
		{
			m_fSmashSize -= 1000* _fDeltaSeconds;

			if (m_fSmashSize <= 1.0f)
			{
				m_wpSmash.lock()->SetActorPosition({ 0.0f, 100.0f, 0.0f });
				m_fSmashSize = 100.0f;
				m_bIsSmashed = false;
			}
			m_wpSmash.lock()->SetActorScale({ m_fSmashSize, 1.0f, m_fSmashSize });
		}
	}
}

int32 CWarmechLeg::GetRandomInteger(int32 _iMin, int32 _iMax)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int32> distribution(_iMin, _iMax);
	return distribution(gen);
}

float CWarmechLeg::GetRandomFloat(float _fMin, float _fMax)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> distribution(_fMin, _fMax);
	return distribution(gen);
}

void CWarmechLeg::Reserve(float _fDeltaSeconds)
{
	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= m_fReserveDeltaSeconds)
	{
		m_fReserveDeltaSeconds = 3.0f;
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)m_ePostWarmechLegState);
	}
}

void CWarmechLeg::JumpToCenter(float _fDeltaSeconds)
{
	m_vDst = m_wpPlayer.lock()->GetActorPosition();

	// ���������� �����մϴ�.
	if (!m_bIsCalled)
	{
		FVector3 vPos = GetActorPosition();
		m_fY = vPos.y;
		vPos.y = 0.0f;

		FVector3 vDir = FVector3(0.0f, 0.0f, 0.0f) - vPos;

		D3DXVec3Normalize(&vDir, &vDir);
		m_vJumpDir = vDir + 15.0f * FVector3(0.0f, 1.0f, 0.0f);
		m_vJumpDir *= 5;
		m_bIsCalled = true;
	}

	m_vTranslate += m_vJumpDir * _fDeltaSeconds;
	m_vJumpDir += FVector3(0, -78.4f, 0) * _fDeltaSeconds;

	// ������ �ٴڿ� ������ ���
	if (m_vTranslate.y <= m_fY)
	{
		m_vTranslate.y = m_fY;
		SetMonsterState((int32)EWarmechLegState::SMASH);
		m_bIsCalled = false;
	}
}

void CWarmechLeg::MoveToCenter(float _fDeltaSeconds)
{
	m_vDst = { 0.0f, 0.0f, 0.0f };

	// ���������� �̵��մϴ�.
	FVector3 vPos = GetActorPosition();
	vPos.y = 0.0f;

	FVector3 vDir = m_vDst - vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_vTranslate += vDir * m_fSpeed * _fDeltaSeconds;

	// �Ÿ��� 3 ������ ���, ���¸� �����մϴ�.
	FVector3 vDist = m_vDst - vPos;
	float fDist = D3DXVec3Length(&vDist);

	m_fSumMoveDeltaSeconds += _fDeltaSeconds;
	if (m_fSumMoveDeltaSeconds >= 0.5f)
	{
		uint32 iRandomIndex = GetRandomInteger(1, 2);
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_step" + to_string(iRandomIndex), ESoundType::MOVE);
		m_fSumMoveDeltaSeconds = 0.0f;
	}

	if (fDist <= 3.0f)
	{
		SetMonsterState((int32)EWarmechLegState::MOVE_TO_RANDOM);
		m_fSumMoveDeltaSeconds = 0.0f;
		m_bIsCalled = false;
	}
}

void CWarmechLeg::MoveToRandom(float _fDeltaSeconds)
{
	// ���ο� �������� �����մϴ�.
	if (!m_bIsCalled)
	{
		float fRandomWidth = GetRandomFloat(-1.0f, 1.0f);
		float fRandomHeight = GetRandomFloat(-1.0f, 1.0f);
		m_vDst = FVector3(m_fWidth * 0.5f * fRandomWidth, 0.0f, m_fHeight * 0.5f * fRandomHeight);
		m_bIsCalled = true;
	}

	// ���������� �̵��մϴ�.
	FVector3 vPos = GetActorPosition();
	vPos.y = 0.0f;

	FVector3 vDir = m_vDst - vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_vTranslate += vDir * m_fSpeed * 2 * _fDeltaSeconds;

	// �Ÿ��� 3 ������ ���, ���¸� �����մϴ�.
	FVector3 vDist = m_vDst - vPos;
	float fDist = D3DXVec3Length(&vDist);

	m_fSumMoveDeltaSeconds += _fDeltaSeconds;
	if (m_fSumMoveDeltaSeconds >= 0.5f)
	{
		uint32 iRandomIndex = GetRandomInteger(1, 2);
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_step" + to_string(iRandomIndex), ESoundType::MOVE);
		m_fSumMoveDeltaSeconds = 0.0f;
	}

	if (fDist <= 3.0f)
	{
		SetMonsterState((int32)EWarmechLegState::RESERVE);
		m_ePostWarmechLegState = EWarmechLegState::MOVE_TO_RANDOM;
		m_fReserveDeltaSeconds = 1.0f;
		m_bIsCalled = false;
		m_fSumMoveDeltaSeconds = 0.0f;
	}
}

void CWarmechLeg::MoveToPlayer(float _fDeltaSeconds)
{
	FVector3 vDst = m_wpPlayer.lock()->GetActorWorldPosition();
	m_vDst = vDst;
	vDst.y = 0.0f;

	// ���������� �̵��մϴ�.
	FVector3 vPos = GetActorPosition();
	vPos.y = 0.0f;

	FVector3 vDir = vDst - vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_vTranslate += vDir * m_fSpeed / 2 * _fDeltaSeconds;

	m_fSumMoveDeltaSeconds += _fDeltaSeconds;
	if (m_fSumMoveDeltaSeconds >= 0.5f)
	{
		uint32 iRandomIndex = GetRandomInteger(1, 2);
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_step" + to_string(iRandomIndex), ESoundType::MOVE);
		m_fSumMoveDeltaSeconds = 0.0f;
	}
}

void CWarmechLeg::MoveToSelfDestruct(float _fDeltaSeconds)
{
	m_vDst = { 0.0f, 0.0f, 0.0f };

	// ���������� �̵��մϴ�.
	FVector3 vPos = GetActorPosition();
	vPos.y = 0.0f;

	FVector3 vDist = m_vDst - vPos;
	float fDist = D3DXVec3Length(&vDist);

	FVector3 vDir = m_vDst - vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_vTranslate += vDir * m_fSpeed * _fDeltaSeconds;

	m_fSumMoveDeltaSeconds += _fDeltaSeconds;
	if (m_fSumMoveDeltaSeconds >= 0.5f)
	{
		uint32 iRandomIndex = GetRandomInteger(1, 2);
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_step" + to_string(iRandomIndex), ESoundType::MOVE);
		m_fSumMoveDeltaSeconds = 0.0f;
	}

	// �Ÿ��� 3 ������ ���, ���¸� �����մϴ�.
	if (fDist <= 3.0f)
	{
		SetMonsterState((int32)EWarmechLegState::SELF_DESTRUCT);
		m_bIsCalled = false;
		m_fSumDeltaSeconds = 0.0f;
		m_fSumMoveDeltaSeconds = 0.0f;
	}

	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= 0.5f)
	{
		// Z �������� �߻����� �ʵ��� �մϴ�.
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

void CWarmechLeg::ReadyToRush(float _fDeltaSeconds)
{
	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds < 2.0f)
	{
		m_vDst = m_wpPlayer.lock()->GetActorWorldPosition();
	}
	else
	{
		SetMonsterState((int32)EWarmechLegState::CHARGE_TO_PLAYER);
		m_fSumDeltaSeconds = 0.0f;
	}
}

void CWarmechLeg::RushToPlayer(float _fDeltaSeconds)
{
	// ���������� �̵��մϴ�.
	FVector3 vPos = GetActorPosition();
	vPos.y = 0.0f;

	FVector3 vDir = m_vDst - vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_vTranslate += vDir * 8 * m_fSpeed * _fDeltaSeconds;

	// �Ÿ��� 3 ������ ���, ���¸� �����մϴ�.
	FVector3 vDist = m_vDst - vPos;
	float fDist = D3DXVec3Length(&vDist);

	if (fDist <= 3.0f)
	{
		SetMonsterState((int32)EWarmechLegState::RESERVE);
		m_ePostWarmechLegState = EWarmechLegState::READY_TO_CHARGE;
		m_fReserveDeltaSeconds = 1.0f;
		m_fSumDeltaSeconds = 0.0f;
		m_bIsCalled = false;
	}
}

void CWarmechLeg::Smash(float _fDeltaSeconds)
{
	// ����ĸ� �����մϴ�.
	if (!m_bIsCalled)
	{
		m_wpPlayer.lock()->GetCurCamera().lock()->SetCameraMove(true);
		m_bIsCalled = true;
		FVector3 vDist = m_wpPlayer.lock()->GetActorPosition() - GetActorPosition();
		float fDist = D3DXVec3Length(&vDist);

		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_smash", ESoundType::SMASH);

		if (fDist <= 50.0f && m_wpPlayer.lock()->GetIsOnAir() == false)
		{
			m_wpPlayer.lock()->GetDamaged(m_fSmashDamage);
		}
	}

	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= 2.0f)
	{
		switch (m_eCurWarmechLegPhase)
		{
		case EWarmechPhase::PHASE_0:
			m_wpWarmechHead.lock()->SetMonsterState((int32)EWarmechHeadState::FIRE_STRAIGHT_GUN);
			SetMonsterState((int32)EWarmechLegState::MOVE_TO_RANDOM);
			break;

		case EWarmechPhase::PHASE_1:
			SetMonsterState((int32)EWarmechLegState::MOVE_TO_PLAYER);
			break;

		case EWarmechPhase::PHASE_2:
			SetMonsterState((int32)EWarmechLegState::READY_TO_CHARGE);
			break;

		case EWarmechPhase::DEAD:
			SetMonsterState((int32)EWarmechLegState::MOVE_TO_SELF_DESTRUCT);
			break;
		}
		m_wpPlayer.lock()->GetCurCamera().lock()->SetCameraMove(false);
		m_fSumDeltaSeconds = 0.0f;
		m_bIsCalled = false;
	}
}

void CWarmechLeg::SelfDestruct(float _fDeltaSeconds)
{
	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= 0.5f)
	{
		// Z �������� �߻����� �ʵ��� �մϴ�.
		float fOffsetX = GetRandomFloat(-0.2f, 0.2f);
		float fOffsetY = GetRandomFloat(-0.2f, 0.1f);
		float fOffsetZ = GetRandomFloat(-0.2f, 0.2f);
		float fOffsetS = GetRandomFloat(0.2f, 0.3f);
		
		m_wpEffectComponent.lock()->SetComponentLocalPosition({ fOffsetX, fOffsetY, fOffsetZ });
		m_wpEffectComponent.lock()->SetComponentScale({ fOffsetS, fOffsetS, fOffsetS });
		
		m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
		m_wpEffectComponent.lock()->SetFrame(0, 0, m_wpEffectComponent.lock()->GetFileEndIndex());
		m_wpEffectComponent.lock()->SetCurrentState(L"Explode");

		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_gun_explosion", ESoundType::FIRE);

		m_fSumDeltaSeconds = 0.0f;
	}

	// �Ӹ��� ������� �� ���� ������ �μ��ϴ�.
	if (m_wpWarmechHead.lock()->GetMonsterPhase() == (int32)EWarmechPhase::DEAD)
	{
		SetMonsterState((int32)EWarmechLegState::BREAK_SAFE_FLOOR);
		m_fSumDeltaSeconds = 0.0f;
		m_bIsCalled = false;
	}
}

void CWarmechLeg::BreakSafeFloor(float _fDeltaSeconds)
{
	if (!m_bIsCalled)
	{
		m_bIsCalled = true;
		m_wpPlayer.lock()->GetCurCamera().lock()->SetCameraMove(true);
	}

	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= 3.0f)
	{
		m_wpPlayer.lock()->GetCurCamera().lock()->SetCameraMove(false);

		SetMonsterState((int32)EWarmechLegState::DEAD);
		m_wpWarmechHead.lock()->SetMonsterState((int32)EWarmechHeadState::DEAD);
		m_fSumDeltaSeconds = 0.0f;
		m_bIsCalled = false;
	}
}

void CWarmechLeg::Dead(float _fDeltaSeconds)
{
	if (!m_bIsCalled)
	{
		float fOffsetX = GetRandomFloat(-0.2f, 0.2f);
		float fOffsetY = GetRandomFloat(-0.2f, 0.1f);
		float fOffsetZ = GetRandomFloat(-0.2f, 0.2f);

		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_gun_explosion", ESoundType::FIRE);

		m_wpEffectComponent.lock()->SetComponentLocalPosition({ fOffsetX, fOffsetY, fOffsetZ });
		m_wpEffectComponent.lock()->SetComponentScale({ 1.0f, 1.0f, 1.0f });
		m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
		m_wpEffectComponent.lock()->SetFrame(0, 0, m_wpEffectComponent.lock()->GetFileEndIndex());
		m_wpEffectComponent.lock()->SetCurrentState(L"Explode");

		m_wpWarmechHead.lock()->m_wpEffectComponent.lock()->SetComponentLocalPosition({ fOffsetX, fOffsetY, fOffsetZ });
		m_wpWarmechHead.lock()->m_wpEffectComponent.lock()->SetComponentScale({ 1.0f, 1.0f, 1.0f });
		m_wpWarmechHead.lock()->m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
		m_wpWarmechHead.lock()->m_wpEffectComponent.lock()->SetFrame(0, 0, m_wpWarmechHead.lock()->m_wpEffectComponent.lock()->GetFileEndIndex());
		m_wpWarmechHead.lock()->m_wpEffectComponent.lock()->SetCurrentState(L"Explode");

		m_wpAnimationComponent.lock()->SetIsRender(false);
		m_wpWarmechHead.lock()->m_wpAnimationComponent.lock()->SetIsRender(false);
		m_bIsCalled = true;
	}
}

/********************
	Component Initialize
********************/
void CWarmechLeg::InitializeEffectComponent()
{
	// ����Ʈ ������Ʈ
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	m_wpEffectComponent.lock()->SetComponentScale({ 0.2f, 0.2f, 0.2f });
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"Explosion0_0", 0, 63, L"Idle", EAnimationType::DESIGNATED_TIME, 2.0f);
	m_wpEffectComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpEffectComponent.lock()->AddState(L"Explode", 32, 63);
	m_wpEffectComponent.lock()->SetIsAnimate(false);
	m_wpEffectComponent.lock()->SetIsRender(false);
	m_wpEffectComponent.lock()->SetAnimationCount(0);
	m_wpEffectComponent.lock()->SetFrame(0, 0, 0);
	SetRootComponent(m_wpEffectComponent.lock());
}

void CWarmechLeg::InitializeSoundComponent()
{
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
}

void CWarmechLeg::AnimationSetting()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"LegAnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Warmech1_0", 0, 111, L"P1LgS_Idle", EAnimationType::LOOP, 0.3f);
	SetRootComponent(m_wpAnimationComponent);
}

void CWarmechLeg::ColliderSetting()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"LegCubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->SetComponentScale({ 0.2f, 0.4f, 0.2f });
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CWarmechLeg::PhysicsSetting()
{
	m_wpPhysicsComponent = CreateActorComponent<CPhysicsComponent>(L"PhysicsComponent");
	m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
}

void CWarmechLeg::ParticleSetting()
{
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetIsRemove(true);							// ��ƼŬ ������Ÿ���� ������ ������ų ������
	m_wpParticleComponent.lock()->SetIsActive(false);							// ��ƼŬ Ȱ��ȭ
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Fragment0_0", 0, 0);	// ��ƼŬ �ؽ�ó ����
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::ERUPTION, 32); // ��ƼŬ Ÿ��, ����
	m_wpParticleComponent.lock()->SetParticleSize(1.0f);						// ��ƼŬ ũ��
	m_wpParticleComponent.lock()->SetParticleLifeTime(1.0f);					// ��ƼŬ ������Ÿ��
	m_wpParticleComponent.lock()->SetParticleSpeed(1.0f);						// ��ƼŬ ���� �ӵ�
	m_wpParticleComponent.lock()->SetParticleAcceleration(0.2f);				// ��ƼŬ ���� ���ӵ�
	m_wpParticleComponent.lock()->SetParticleCreateTime(0.2f);					// (0 ~ �Ű�����)���� �ð� �߿��� �����ϰ� ������
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeXZ(1.0f);				// x,z ��ǥ ���� ����
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeY(0.5f);				// y ��ǥ ���� ����
}

/********************
	Getter/Setter
********************/
void CWarmechLeg::SetMonsterState(int32 _iMonsterState)
{
	// ���� ���¿� ���� ���
	if (m_eCurWarmechLegState == (EWarmechLegState)_iMonsterState) { return; }

	// ���� ���¸� �����մϴ�.
	m_ePrevWarmechLegState = m_eCurWarmechLegState;
	m_eCurWarmechLegState = (EWarmechLegState)_iMonsterState;
}

int32 CWarmechLeg::GetMonsterState() const
{
	return (int32)m_eCurWarmechLegState;
}

void CWarmechLeg::SetMonsterPhase(int32 _iMonsterPhase)
{
	// ���� ������� ���� �������� ���
	if (m_eCurWarmechLegPhase == (EWarmechPhase)_iMonsterPhase) { return; }

	// ���� ����� �����մϴ�.
	m_ePrevWarmechLegPhase = m_eCurWarmechLegPhase;
	m_eCurWarmechLegPhase = (EWarmechPhase)_iMonsterPhase;
}

int32 CWarmechLeg::GetMonsterPhase() const
{
	return (int32)m_eCurWarmechLegPhase;
}

void CWarmechLeg::SetMonsterAnim(int32 _iMonsterAnim)
{
	if (m_eCurWarmechLegAnimType == (EWarmechLegAnimType)_iMonsterAnim) { return; }

	m_ePrevWarmechLegAnimType = m_eCurWarmechLegAnimType;
	m_eCurWarmechLegAnimType = (EWarmechLegAnimType)_iMonsterAnim;
}

int32 CWarmechLeg::GetMonsterAnim() const
{
	return (int32)m_eCurWarmechLegAnimType;
}

void CWarmechLeg::GetDamaged(const float& _fDamage)
{
	m_fCurHp -= _fDamage;

	if (m_fCurHp <= 1.0f)
	{
		m_fCurHp = 1.0f;
		return;
	}
	m_wpOutGameUI.lock()->ActivateBossHpBar();
	m_wpOutGameUI.lock()->SetBossMonsterHpBar(_fDamage);
	m_wpSoundComponent.lock()->PlaySoundByDistance("mech_hit1", ESoundType::DAMAGE);

	// [ ��ƼŬ ]
	// 1. �ǰ� UV��ǥ�� �����´�.
	FVector3 vHittedPos = m_wpCubeColliderComponent.lock()->GetRayHittedPos();

	// 2. �ش� ��ǥ���� ������ ���� ��ǥ�� ���� ���� ���͸� ���Ѵ�.
	FVector3 vHittedDir = vHittedPos - GetActorWorldPosition();

	// D3DXVec3Normalize(&vHittedDir, &vHittedDir); -> ����ȭ�� ������ϳ�?
	// ���� �����ϰ����� �����ٱ�?
	vHittedDir.x /= m_vScale.x;
	vHittedDir.y /= m_vScale.y;
	vHittedDir.z /= m_vScale.z;

	// 3. ��ƼŬ ������Ʈ�� SetOrigin�� ȣ���ؼ�, �ش� ���⺤�͸� �־��ش�.
	m_wpParticleComponent.lock()->SetParticleOrigin(vHittedDir);

	// 4. ��ƼŬ�� �����Ѵ�.
	m_wpParticleComponent.lock()->SetIsActive(true);
	m_wpParticleComponent.lock()->AddParticle();
}

void CWarmechLeg::SetWarmechHead(std::shared_ptr<CWarmechHead> _spWarmechHead)
{
	m_wpWarmechHead = _spWarmechHead;
}

int32 CWarmechLeg::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (!m_bIsTriggered)
	{
		SetMonsterState((int32)EWarmechLegState::SMASH);
		m_bIsTriggered = true;
	}

	m_bIsCollided = true;
	m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
	return 0;
}

void CWarmechLeg::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	CMonster::OnCollisionStay(_wpSrcCollider, _wpDstCollider);
}

void CWarmechLeg::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	m_bIsCollided = false;
}
