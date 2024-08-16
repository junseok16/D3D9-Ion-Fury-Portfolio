// Default
#include "pch.h"
#include "Skinjob.h"

// Framework
#include "Level.h"

// Component
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"

// Manager
#include "TimerManager.h"
#include "CollisionManager.h"
#include "InputManager.h"

// Client
#include "FloatingBox.h"
#include "ThrowingBox.h"
#include "LaserEmitter.h"
#include "FlameEmitter.h"
using namespace std;

void CSkinjob::Initialize()
{
	InitializeAnimationCompnent();
	InitializeColliderComponent();
	InitializeParticleComponent();

	// TODO: 알파 테스트로 변경해야 합니다.
	SetRenderType(ERenderType::NON_ALPHA);
	SetMobility(EMobilityType::DYNAMIC);
	CMonster::Initialize();
}

void CSkinjob::BeginPlay()
{
	// 보스 다리 체력을 설정합니다.
	m_fCurHp = 1'000.0f;

	// 플레이어를 불러옵니다.
	m_wpPlayer = GetLevel().lock()->FindActor(L"Player");

	// 3 x 3 발판을 불러옵니다.
	for (int32 iIndex = 0; iIndex < 3; ++iIndex)
	{
		for (int32 jIndex = 0; jIndex < 3; ++jIndex)
		{
			m_wpFloatingBox[iIndex][jIndex] = dynamic_pointer_cast<CFloatingBox>(GetLevel().lock()->FindActor(L"FloatingBox" + to_wstring(iIndex) + to_wstring(jIndex)));
		}
	}

	// 던지는 박스를 불러옵니다.
	for (int32 iIndex = 0; iIndex < 6; ++iIndex)
	{
		m_wpThrowingBox[iIndex] = dynamic_pointer_cast<CThrowingBox>(GetLevel().lock()->FindActor(L"ThrowingBox" + to_wstring(iIndex)));
	}

	// 애니메이션을 바인드합니다.
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 0);

	CMonster::BeginPlay();
}

int32 CSkinjob::Update(const float& _fDeltaSeconds)
{
	UpdateMonsterDirection();
	UpdateMonsterPhase();
	UpdateMonsterState();
	UpdateMonsterAnim();

	if (CInputManager::GetInstance()->IsKeyDown(DIK_P))
	{
		SetMonsterPhase((int32)ESkinjobPhase::PHASE_0);
		SetMonsterState((int32)ESkinjobState::FLOAT_THROWING_BOX);
	}
	if (CInputManager::GetInstance()->IsKeyDown(DIK_O))
	{

	}
	return CMonster::Update(_fDeltaSeconds);
}

int32 CSkinjob::LateUpdate(const float& _fDeltaSeconds)
{
	return CMonster::LateUpdate(_fDeltaSeconds);
}

void CSkinjob::Render()
{
	CMonster::Render();
}

void CSkinjob::EndPlay()
{
	CMonster::EndPlay();
}

void CSkinjob::Release()
{
	CMonster::Release();
}

/********************
	Component Initialize
********************/
void CSkinjob::InitializeAnimationCompnent()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Skinjob0_0", 0, 0, L"Idle", EAnimationType::LOOP, 0.2f);
	SetRootComponent(m_wpAnimationComponent);
}

void CSkinjob::InitializeColliderComponent()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CSkinjob::InitializeParticleComponent()
{
}

void CSkinjob::UpdateMonsterPhase()
{
	switch (m_eCurSkinjobPhase)
	{
	case ESkinjobPhase::READY:
		break;

	case ESkinjobPhase::TO_PHASE_0:
		break;

	case ESkinjobPhase::PHASE_0:
		break;

	case ESkinjobPhase::TO_PHASE_1:
	{
		for (int32 i = 1; i <= 7; i += 2) { DescendFloatingBox(i); }
		SetMonsterPhase((int32)ESkinjobPhase::PHASE_1);
	}
	break;

	case ESkinjobPhase::PHASE_1:
		break;

	case ESkinjobPhase::TO_PHASE_2:
	{
		for (int32 i = 0; i <= 2; ++i) { DescendFloatingBox(i); }
		for (int32 i = 3; i <= 5; ++i) { AscendFloatingBox(i); }
		for (int32 i = 6; i <= 8; ++i) { DescendFloatingBox(i); }
		SetMonsterPhase((int32)ESkinjobPhase::PHASE_2);
	}
	break;

	case ESkinjobPhase::PHASE_2:
		break;

	case ESkinjobPhase::DEAD:
		break;

	case ESkinjobPhase::ENUM_END:
		break;

	default:
		break;
	}
}

void CSkinjob::UpdateMonsterState()
{
	switch (m_eCurSkinjobState)
	{
	case ESkinjobState::SEPARATE_BOX:
		SeparateBox();
		break;

	case ESkinjobState::EMIT_LASER:
		EmitLaser();
		break;

	case ESkinjobState::NON_EMIT_LASER:
		NonEmitLaser();
		break;

	case ESkinjobState::EMIT_FLAME:
		EmitFlame();
		break;

	case ESkinjobState::NON_EMIT_FLAME:
		NonEmitFlame();
		break;

	case ESkinjobState::PUSH_OBSTACLE:
		break;

	case ESkinjobState::CONBINE_BOX:
		CombineBox();
		break;

	case ESkinjobState::FLOAT_THROWING_BOX:
		FloatRandomBox();
		break;

	case ESkinjobState::THROW_THROWING_BOX:
		ThrowRandomBox();
		break;

	case ESkinjobState::SPAWN_MONSTER:
		break;

	case ESkinjobState::IDLE:
		break;

	case ESkinjobState::BLUE_ENERGY_BALL:
		break;

	case ESkinjobState::RED_ENERGY_BALL:
		break;

	case ESkinjobState::DEAD:
		break;

	case ESkinjobState::ENUM_END:
		break;

	default:
		break;
	}
}

void CSkinjob::UpdateMonsterAnim()
{
	switch (m_eCurSkinjobAnim)
	{
	case ESkinjobAnim::IDLE:
		break;

	case ESkinjobAnim::WALK:
		break;

	case ESkinjobAnim::LOTUS:
		break;

	case ESkinjobAnim::ROAR:
		break;

	case ESkinjobAnim::SHOCK:
		break;

	case ESkinjobAnim::DEAD:
		break;

	case ESkinjobAnim::ENUM_END:
		break;

	default:
		break;
	}
}

void CSkinjob::UpdateMonsterDirection()
{
	//	// 플레이어 위치를 구합니다.
	//	FVector3 vPlayerPos = m_wpPlayer.lock()->GetActorWorldPosition();
	//	vPlayerPos.y -= vPlayerPos.y;
	//	
	//	// 보스 위치를 구합니다.
	//	FVector3 vBossPos = GetActorWorldPosition();
	//	vBossPos.y -= vBossPos.y;
	//	
	//	// 보스가 바라보는 방향을 구합니다.
	//	FVector3 vBossDir = m_wpBlackBoardComponent.lock()->GetValueAsFVector3(L"LegDirection");
	//	vBossDir.y -= vBossDir.y;
	//	D3DXVec3Normalize(&vBossDir, &vBossDir);
	//	
	//	// 보스에서 플레이어로 향하는 방향 벡터를 구합니다.
	//	FVector3 vBossToPlayer = vPlayerPos - vBossPos;
	//	D3DXVec3Normalize(&vBossToPlayer, &vBossToPlayer);
	//	
	//	m_fRadian = acos(D3DXVec3Dot(&vBossDir, &vBossToPlayer)) * (180.0f / D3DX_PI);
	//	
	//	FVector3 vCross;
	//	D3DXVec3Cross(&vCross, &vBossDir, &vBossToPlayer);
	//	if (vCross.y < 0) { m_fRadian = 360.0f - m_fRadian; }
}

void CSkinjob::AscendFloatingBox(int32 _iBoxIndex)
{
	m_wpFloatingBox[_iBoxIndex / 3][_iBoxIndex % 3].lock()->SetFloatingBoxState(EFloatingBoxState::ASCENDING);
}

void CSkinjob::DescendFloatingBox(int32 _iBoxIndex)
{
	m_wpFloatingBox[_iBoxIndex / 3][_iBoxIndex % 3].lock()->SetFloatingBoxState(EFloatingBoxState::DESCENDING);
}

void CSkinjob::SeparateFloatingBox(int32 _iBoxIndex)
{
	m_wpFloatingBox[_iBoxIndex / 3][_iBoxIndex % 3].lock()->SetFloatingBoxState(EFloatingBoxState::SEPARATING);
}

void CSkinjob::CombineFloatingBox(int32 _iBoxIndex)
{
	m_wpFloatingBox[_iBoxIndex / 3][_iBoxIndex % 3].lock()->SetFloatingBoxState(EFloatingBoxState::COMBINING);
}

void CSkinjob::EmitFlame()
{
	random_device rd;
	mt19937 gen(rd());

	switch (m_eCurSkinjobPhase)
	{
	case ESkinjobPhase::PHASE_0:
	{
		if (m_bIsCalled) { break; }
		m_bIsCalled = true;

		vector<int32> vecNumbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		shuffle(vecNumbers.begin(), vecNumbers.end(), gen);

		for (int32 iIndex = 0; iIndex < 7; ++iIndex)
		{
			m_wpFloatingBox[vecNumbers[iIndex] % 3][vecNumbers[iIndex] / 3].lock()->SetFloatingBoxState(EFloatingBoxState::FLAME_ON);
		}
	}
	break;

	case ESkinjobPhase::PHASE_1:
	{
		if (m_bIsCalled) { break; }
		m_bIsCalled = true;

		vector<int32> vecNumbers = { 0, 2, 4, 6, 8 };
		shuffle(vecNumbers.begin(), vecNumbers.end(), gen);

		for (int32 iIndex = 0; iIndex < 3; ++iIndex)
		{
			m_wpFloatingBox[vecNumbers[iIndex] % 3][vecNumbers[iIndex] / 3].lock()->SetFloatingBoxState(EFloatingBoxState::FLAME_ON);
		}
	}
	break;

	case ESkinjobPhase::PHASE_2:
	{
		if (m_bIsCalled) { break; }
		m_bIsCalled = true;

		vector<int32> vecNumbers = { 1, 4, 7 };
		shuffle(vecNumbers.begin(), vecNumbers.end(), gen);

		for (int32 iIndex = 0; iIndex < 2; ++iIndex)
		{
			m_wpFloatingBox[vecNumbers[iIndex] % 3][vecNumbers[iIndex] / 3].lock()->SetFloatingBoxState(EFloatingBoxState::FLAME_ON);
		}
	}
	break;

	default:
		break;
	}

	// 3초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 3.0f)
	{
		// 화염을 분출한 횟수를 1만큼 증가시킵니다.
		++m_iEmitFlameCounter;

		m_bIsCalled = false;
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)ESkinjobState::NON_EMIT_FLAME);
	}
}

void CSkinjob::NonEmitFlame()
{
	for (int32 iIndex = 0; iIndex < 3; ++iIndex)
	{
		for (int32 jIndex = 0; jIndex < 3; ++jIndex)
		{
			m_wpFloatingBox[iIndex][jIndex].lock()->SetFloatingBoxState(EFloatingBoxState::FLAME_OFF);
		}
	}

	// 3초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 3.0f)
	{
		m_fSumDeltaSeconds = 0.0f;

		// 화염을 세 번 분출하고 발판을 결합합니다.
		if (m_iEmitFlameCounter >= 3)
		{
			SetMonsterState((int32)ESkinjobState::CONBINE_BOX);
		}
		else
		{
			SetMonsterState((int32)ESkinjobState::EMIT_FLAME);
		}
	}
}

void CSkinjob::EmitLaser()
{
	random_device rd;
	mt19937 gen(rd());

	switch (m_eCurSkinjobPhase)
	{
	case ESkinjobPhase::PHASE_0:
	{
		if (m_bIsCalled) { break; }
		m_bIsCalled = true;

		vector<int32> vecNumbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		shuffle(vecNumbers.begin(), vecNumbers.end(), gen);

		for (int32 iIndex = 0; iIndex < 7; ++iIndex)
		{
			m_wpFloatingBox[vecNumbers[iIndex] % 3][vecNumbers[iIndex] / 3].lock()->SetFloatingBoxState(EFloatingBoxState::LASER_ON);
		}
	}
	break;

	case ESkinjobPhase::PHASE_1:
	{
		if (m_bIsCalled) { break; }
		m_bIsCalled = true;

		vector<int32> vecNumbers = { 0, 2, 4, 6, 8 };
		shuffle(vecNumbers.begin(), vecNumbers.end(), gen);

		for (int32 iIndex = 0; iIndex < 3; ++iIndex)
		{
			m_wpFloatingBox[vecNumbers[iIndex] % 3][vecNumbers[iIndex] / 3].lock()->SetFloatingBoxState(EFloatingBoxState::LASER_ON);
		}
	}
	break;

	case ESkinjobPhase::PHASE_2:
	{
		if (m_bIsCalled) { break; }
		m_bIsCalled = true;

		vector<int32> vecNumbers = { 1, 4, 7 };
		shuffle(vecNumbers.begin(), vecNumbers.end(), gen);

		for (int32 iIndex = 0; iIndex < 2; ++iIndex)
		{
			m_wpFloatingBox[vecNumbers[iIndex] % 3][vecNumbers[iIndex] / 3].lock()->SetFloatingBoxState(EFloatingBoxState::LASER_ON);
		}
	}
	break;

	default:
		break;
	}

	// 3초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 3.0f)
	{
		// 화염을 분출한 횟수를 1만큼 증가시킵니다.
		++m_iEmitLaserCounter;

		m_bIsCalled = false;
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)ESkinjobState::NON_EMIT_LASER);
	}
}

void CSkinjob::NonEmitLaser()
{
	for (int32 iIndex = 0; iIndex < 3; ++iIndex)
	{
		for (int32 jIndex = 0; jIndex < 3; ++jIndex)
		{
			m_wpFloatingBox[iIndex][jIndex].lock()->SetFloatingBoxState(EFloatingBoxState::LASER_OFF);
		}
	}

	// 3초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 3.0f)
	{
		m_fSumDeltaSeconds = 0.0f;

		// 화염을 세 번 분출하고 발판을 결합합니다.
		if (m_iEmitLaserCounter >= 3)
		{
			SetMonsterState((int32)ESkinjobState::CONBINE_BOX);
		}
		else
		{
			SetMonsterState((int32)ESkinjobState::EMIT_LASER);
		}
	}
}

void CSkinjob::FloatRandomBox()
{
	if (!m_bIsCalled)
	{
		for (int32 iIndex = 0; iIndex < 6; ++iIndex)
		{
			m_wpThrowingBox[iIndex].lock()->SetThrowingBoxState(EThrowingBoxState::FLOAT);
		}
		m_bIsCalled = true;
	}
	
	// 5초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 5.0f)
	{
		m_bIsCalled = false;
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)ESkinjobState::THROW_THROWING_BOX);
	}
}

void CSkinjob::ThrowRandomBox()
{
	for (int32 iIndex = 0; iIndex < 6; ++iIndex)
	{
		m_wpThrowingBox[iIndex].lock()->SetSpeed(GetRandomFloat(10.0f, 20.0f));
		m_wpThrowingBox[iIndex].lock()->SetThrowingBoxState(EThrowingBoxState::THROW);
	}

	// 3초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 3.0f)
	{
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)ESkinjobState::THROW_THROWING_BOX);
	}
}

void CSkinjob::SeparateBox()
{
	if (!m_bIsCalled)
	{
		for (int32 iIndex = 0; iIndex < 3; ++iIndex)
		{
			for (int32 jIndex = 0; jIndex < 3; ++jIndex)
			{
				m_wpFloatingBox[iIndex][jIndex].lock()->SetFloatingBoxState(EFloatingBoxState::SEPARATING);
			}
		}
		m_bIsCalled = true;
	}

	// 5초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 5.0f)
	{
		m_fSumDeltaSeconds = 0.0f;
		// SetMonsterState((int32)ESkinjobState::EMIT_FLAME);
		SetMonsterState((int32)ESkinjobState::EMIT_LASER);
		m_bIsCalled = false;
		/*
		if (GetRandomInteger(0, 1))
		{
		}
		else
		{
			SetMonsterState((int32)ESkinjobState::EMIT_LASER);
		}
		*/
	}
}

void CSkinjob::CombineBox()
{
	if (!m_bIsCalled)
	{
		for (int32 iIndex = 0; iIndex < 3; ++iIndex)
		{
			for (int32 jIndex = 0; jIndex < 3; ++jIndex)
			{
				m_wpFloatingBox[iIndex][jIndex].lock()->SetFloatingBoxState(EFloatingBoxState::COMBINING);
			}
		}
		m_bIsCalled = true;
	}

	// 5초 후에 상태를 변경합니다.
	m_fSumDeltaSeconds += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumDeltaSeconds >= 5.0f)
	{
		m_fSumDeltaSeconds = 0.0f;
		SetMonsterState((int32)ESkinjobState::IDLE);
	}
}

int32 CSkinjob::GetRandomInteger(int32 _iMin, int32 _iMax)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int32> distribution(_iMin, _iMax);
	return distribution(gen);
}

float CSkinjob::GetRandomFloat(float _fMin, float _fMax)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> distribution(_fMin, _fMax);
	return distribution(gen);
}

/********************
	Callbacks
********************/
int32 CSkinjob::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CSkinjob::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CSkinjob::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

/********************
	Getter/Setter
********************/
void CSkinjob::SetMonsterState(int32 _iMonsterState)
{
	// 현재 상태와 같은 경우
	if (m_eCurSkinjobState == (ESkinjobState)_iMonsterState) { return; }

	// 현재 상태를 갱신합니다.
	m_ePrevSkinjobState = m_eCurSkinjobState;
	m_eCurSkinjobState = (ESkinjobState)_iMonsterState;
}

int32 CSkinjob::GetMonsterState() const
{
	return (int32)m_eCurSkinjobState;
}

void CSkinjob::SetMonsterPhase(int32 _iMonsterPhase)
{
	// 현재 페이즈와 같은 페이즈인 경우
	if (m_eCurSkinjobPhase == (ESkinjobPhase)_iMonsterPhase) { return; }

	// 현재 페이즈를 갱신합니다.
	m_ePrevSkinjobPhase = m_eCurSkinjobPhase;
	m_eCurSkinjobPhase = (ESkinjobPhase)_iMonsterPhase;
}

int32 CSkinjob::GetMonsterPhase() const
{
	return (int32)m_eCurSkinjobPhase;
}

void CSkinjob::SetMonsterAnim(int32 _iMonsterAnim)
{
	if (m_eCurSkinjobAnim == (ESkinjobAnim)_iMonsterAnim) { return; }

	m_ePrevSkinjobAnim = m_eCurSkinjobAnim;
	m_eCurSkinjobAnim = (ESkinjobAnim)_iMonsterAnim;
}

int32 CSkinjob::GetMonsterAnim() const
{
	return (int32)m_eCurSkinjobAnim;
}
