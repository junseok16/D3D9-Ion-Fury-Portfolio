// Default
#include "pch.h"
#include "Deacon.h"

// Manager
#include "RenderManager.h"
#include "CollisionManager.h"

// Component
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"
#include "PhysicsComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

// Behavior Tree
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "SensorComponent.h"
#include "ParticleComponent.h"

#include "BTCompositeNode.h"
#include "BTTaskNode.h"
#include "BTBlackBoardDecorator.h"
#include "WaitTask.h"
#include "MoveTask.h"
#include "IdleMoveTask.h"
#include "WaitFlyingTask.h"
#include "RepositionTask.h"
#include "SetStateTask.h"
#include "AttackTask.h"

#include "Level.h"
#include "PlayerActor.h"
using namespace std;

void CDeacon::Initialize()
{
	AnimationSetting();
	ColliderSetting();
	PhysicsSetting();
	ParticleSetting();
	SoundSetting();

	InitializeAIComponent();
	InitializeSensorComponent();
	InitSkullUI();
	m_wpMonsterSkullComponent.lock()->SetComponentLocalPosition({ 0.f, 0.6f, 0.f });
	
	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CCreature::Initialize(); 
}

void CDeacon::BeginPlay()
{
	m_fCurHp = 50.0f;

	AnimationStateSetting();
	AnimationSpeedSetting();

	std::weak_ptr<CActor> m_wpPlayer = GetLevel().lock()->FindActor(L"Player");
	m_wpSensorComponent.lock()->BindSeeingEnterDelegate(L"Player", m_wpPlayer.lock(), dynamic_pointer_cast<CDeacon>(shared_from_this()), &CDeacon::OnSeeingEnterDelegate);
	m_wpSensorComponent.lock()->BindSeeingExitDelegate(L"Player", m_wpPlayer.lock(), dynamic_pointer_cast<CDeacon>(shared_from_this()), &CDeacon::OnSeeingExitDelegate);

	m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 10.0f, 200.0f, 10.0f, 100.0f);

	BeginPlaySkullUI();
	m_wpBehaviorTreeComponent.lock()->StartBehaviorTree();
	SetMonsterState((int32)EMonsterState::IDLE);
	CMonster::BeginPlay();
}

int32 CDeacon::Update(const float& _fDeltaSeconds)
{
	std::weak_ptr<CActor> m_wpPlayer = GetLevel().lock()->FindActor(L"Player");
	m_wpBlackBoardComponent.lock()->SetValueAsFVector3(L"Player", m_wpPlayer.lock()->GetActorWorldPosition());

	// 몬스터의 상태를 업데이트합니다.
	UpdateMonsterState();

	// 몬스터에 방향에 따라 애니메이션을 업데이트합니다.
	UpdateMonsterDirection();
	UpdateSkullUI(m_wpMonsterSkullComponent);

	return CMonster::Update(_fDeltaSeconds);
}

int32 CDeacon::LateUpdate(const float& _fDeltaSeconds)
{
	// 몬스터에 빌보드를 적용합니다.
	CMonster::SetBillboard(m_wpAnimationComponent);
	CMonster::SetBillboard(m_wpEffectComponent);
	CMonster::SetBillboard(m_wpMonsterSkullComponent);

	return CMonster::LateUpdate(_fDeltaSeconds);
}

void CDeacon::Render()
{
	CMonster::Render();
}

void CDeacon::EndPlay()
{
	CMonster::EndPlay();
}

void CDeacon::Release()
{
	CMonster::Release();
}

int32 CDeacon::GetMonsterState() const
{
	return (int32)m_eCurMonsterState;
}

void CDeacon::SetMonsterState(int32 _iMonsterState)
{
	// 현재 상태와 같은 경우
	if (m_eCurMonsterState == (EMonsterState)_iMonsterState) { return; }

	// 사망 상태인 경우
	if (m_eCurMonsterState == EMonsterState::DEAD) { return; }

	// 블랙보드 컴포넌트를 갱신합니다.
	m_wpBlackBoardComponent.lock()->SetValueAsInt(L"MonsterState", _iMonsterState);

	// 현재 상태를 갱신합니다.
	m_ePrevMonsterState = m_eCurMonsterState;
	m_eCurMonsterState = (EMonsterState)_iMonsterState;
}

void CDeacon::UpdateMonsterState()
{
	if (m_ePrevMonsterState == m_eCurMonsterState) { return; }

	switch (m_eCurMonsterState)
	{
	case EMonsterState::IDLE:

		m_ePrevMonsterState = m_eCurMonsterState;
		break;

	case EMonsterState::CHASE:

		m_ePrevMonsterState = m_eCurMonsterState;
		break;

	case EMonsterState::ATTACK:

		m_ePrevMonsterState = m_eCurMonsterState;
		break;

	case EMonsterState::DEAD:
		// 사망 애니메이션을 출력합니다.
		m_wpAnimationComponent.lock()->SetCurrentState(L"Dead");
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::DESIGNATED_TIME);
		m_wpAnimationComponent.lock()->SetAnimationCount(0);
		m_wpBehaviorTreeComponent.lock()->StopBehaviorTree();

		m_ePrevMonsterState = m_eCurMonsterState;
		break;
	}
}

void CDeacon::UpdateMonsterDirection()
{
	// 플레이어 위치
	FVector3 vPlayerPos = m_wpBlackBoardComponent.lock()->GetValueAsFVector3(L"Player");
	vPlayerPos.y -= vPlayerPos.y;

	// 몬스터 위치
	FVector3 vMonsterPos = GetActorWorldPosition();
	vMonsterPos.y -= vMonsterPos.y;

	// 몬스터 진행 방향
	FVector3 vMonsterDir = m_wpBlackBoardComponent.lock()->GetValueAsFVector3(L"MonsterDirection");
	vMonsterDir.y -= vMonsterDir.y;

	// [ 몬스터 -> 플레이어 ] 벡터
	FVector3 vMonsterToPlayer = vPlayerPos - vMonsterPos;
	D3DXVec3Normalize(&vMonsterDir, &vMonsterDir);
	D3DXVec3Normalize(&vMonsterToPlayer, &vMonsterToPlayer);

	float fRadian = acos(D3DXVec3Dot(&vMonsterDir, &vMonsterToPlayer)) * (180.0f / D3DX_PI);

	FVector3 vCross;
	D3DXVec3Cross(&vCross, &vMonsterDir, &vMonsterToPlayer);

	if (vCross.y < 0)
		fRadian = 360.0f - fRadian;

	shared_ptr<CAnimationComponent> wpAnim = m_wpAnimationComponent.lock();

	switch (m_eCurMonsterState)
	{
	case EMonsterState::IDLE:
	{
		if ((0.0f <= fRadian && fRadian < 45.0f) || (315.0f <= fRadian && fRadian < 360.0f))
			wpAnim->SetCurrentState(L"SouthIdle");
		else if (45.0f <= fRadian && fRadian < 135.0f)
			wpAnim->SetCurrentState(L"EastIdle");
		else if (135.0f <= fRadian && fRadian < 225.0f)
			wpAnim->SetCurrentState(L"NorthIdle");
		else if (225.0f <= fRadian && fRadian < 315.0f)
			wpAnim->SetCurrentState(L"WestIdle");

		break;
	}

	case EMonsterState::WALK:
	{
		if ((0.0f <= fRadian && fRadian < 45.0f) || (315.0f <= fRadian && fRadian < 360.0f))
			wpAnim->SetCurrentState(L"SouthWalk");
		else if (45.0f <= fRadian && fRadian < 135.0f)
			wpAnim->SetCurrentState(L"EastWalk");
		else if (135.0f <= fRadian && fRadian < 225.0f)
			wpAnim->SetCurrentState(L"NorthWalk");
		else if (225.0f <= fRadian && fRadian < 315.0f)
			wpAnim->SetCurrentState(L"WestWalk");

		break;
	}

	case EMonsterState::CHASE:
	{
		if ((0.0f <= fRadian && fRadian < 45.0f) || (315.0f <= fRadian && fRadian < 360.0f))
			wpAnim->SetCurrentState(L"SouthWalk");
		else if (45.0f <= fRadian && fRadian < 135.0f)
			wpAnim->SetCurrentState(L"EastWalk");
		else if (135.0f <= fRadian && fRadian < 225.0f)
			wpAnim->SetCurrentState(L"NorthWalk");
		else if (225.0f <= fRadian && fRadian < 315.0f)
			wpAnim->SetCurrentState(L"WestWalk");

		break;
	}

	case EMonsterState::ATTACK:
	{
		// 공격 중이라면 무조건 플레이어를 쳐다봅니다.
		wpAnim->SetCurrentState(L"SouthAttack");
		break;
	}

	case EMonsterState::DEAD:
		wpAnim->SetCurrentState(L"Dead");

		break;
	}
}

void CDeacon::AnimationSetting()
{
	// 애니메이션 컴포넌트
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Deacon0_0_", 0, 51, L"NorthIdle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpAnimationComponent.lock());

	// 이펙트 컴포넌트
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"Explosion0_0", 0, 31, L"Idle", EAnimationType::DESIGNATED_TIME, 1.5f);
	m_wpEffectComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpEffectComponent.lock()->AddState(L"Action", 0, 31);
	m_wpEffectComponent.lock()->SetIsAnimate(false);
	m_wpEffectComponent.lock()->SetIsRender(false);
	m_wpEffectComponent.lock()->SetAnimationCount(0);
	m_wpEffectComponent.lock()->SetFrame(0, 0, 0);
	SetRootComponent(m_wpEffectComponent);
}

void CDeacon::AnimationStateSetting()
{
	// 애니메이션 상태
	m_wpAnimationComponent.lock()->AddState(L"Dead", 0, 7);
	m_wpAnimationComponent.lock()->FrameMapping(L"Dead", 7);
	m_wpAnimationComponent.lock()->BindFrame(L"Dead", dynamic_pointer_cast<CDeacon>(shared_from_this()), &CDeacon::PlayDeathSound);

	m_wpAnimationComponent.lock()->AddState(L"EastAttack", 8, 11);
	m_wpAnimationComponent.lock()->AddState(L"EastIdle", 12, 12);
	m_wpAnimationComponent.lock()->AddState(L"EastWalk", 13, 13);
	m_wpAnimationComponent.lock()->AddState(L"EastShock", 17, 18);

	m_wpAnimationComponent.lock()->AddState(L"NorthAttack", 19, 22);
	m_wpAnimationComponent.lock()->AddState(L"NorthIdle", 23, 23);
	m_wpAnimationComponent.lock()->AddState(L"NorthWalk", 24, 24);
	m_wpAnimationComponent.lock()->AddState(L"NorthShock", 28, 29);

	m_wpAnimationComponent.lock()->AddState(L"SouthAttack", 30, 33);
	m_wpAnimationComponent.lock()->AddState(L"SouthIdle", 34, 34);
	m_wpAnimationComponent.lock()->AddState(L"SouthWalk", 35, 35);
	m_wpAnimationComponent.lock()->AddState(L"SouthShock", 39, 40);

	m_wpAnimationComponent.lock()->AddState(L"WestAttack", 41, 44);
	m_wpAnimationComponent.lock()->AddState(L"WestIdle", 45, 45);
	m_wpAnimationComponent.lock()->AddState(L"WestWalk", 46, 46);
	m_wpAnimationComponent.lock()->AddState(L"WestShock", 50, 51);
}

void CDeacon::AnimationSpeedSetting()
{
	// 애니메이션 속도 조절
	m_wpAnimationComponent.lock()->SetFrameTime(L"NorthAttack", 19, 22, 0.5f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"SouthAttack", 30, 33, 0.5f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"WestAttack", 41, 44, 0.5f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"EastAttack", 8, 11, 0.5f);
}

void CDeacon::ColliderSetting()
{
	// 큐브 콜라이더 컴포넌트
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	m_wpCubeColliderComponent.lock()->SetComponentScale({ 0.5f, 0.7f, 0.5f });
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CDeacon::PhysicsSetting()
{
	m_wpPhysicsComponent = CreateActorComponent<CPhysicsComponent>(L"PhysicsComponent");

	// 디콘은 중력의 영향을 받지 않습니다.
	m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
}

void CDeacon::ParticleSetting()
{
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetIsRemove(true);
	m_wpParticleComponent.lock()->SetIsActive(false);
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Spark0_", 0, 0);
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::ERUPTION, 16);
	m_wpParticleComponent.lock()->SetParticleSize(1.0f);
	m_wpParticleComponent.lock()->SetParticleLifeTime(1.0f);
	m_wpParticleComponent.lock()->SetParticleSpeed(1.0f);
	m_wpParticleComponent.lock()->SetParticleAcceleration(0.2f);
	m_wpParticleComponent.lock()->SetParticleCreateTime(0.2f);
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeXZ(1.0f);
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeY(0.5f);
}

void CDeacon::SoundSetting()
{
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
}

void CDeacon::GetDamaged(const float& _fDamage)
{
#pragma region 사운드

	if (!m_bIsTimeSlipped)
	{
		switch (m_eDeaconHittedSound)
		{
		case EDeaconHittedSound::NUM_1:
		{
			m_wpSoundComponent.lock()->PlaySoundByDistance("Deacon_Hitted1", ESoundType::DAMAGE);
			m_eDeaconHittedSound = EDeaconHittedSound::NUM_2;
			break;
		}
		case EDeaconHittedSound::NUM_2:
		{
			m_wpSoundComponent.lock()->PlaySoundByDistance("Deacon_Hitted2", ESoundType::DAMAGE);
			m_eDeaconHittedSound = EDeaconHittedSound::NUM_1;
			break;
		}
		}
	}

#pragma endregion 사운드

#pragma region 파티클

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

#pragma endregion 파티클

#pragma region 데미지

	if (m_fCurHp > _fDamage)
	{
		m_fCurHp -= _fDamage;
		return;
	}

#pragma region 이펙트

	m_wpEffectComponent.lock()->SetIsAnimate(true);
	m_wpEffectComponent.lock()->SetIsRender(true);
	int32 iEndIndex = m_wpEffectComponent.lock()->GetFileEndIndex();
	m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
	m_wpEffectComponent.lock()->SetFrame(0, 0, iEndIndex);
	m_wpEffectComponent.lock()->SetCurrentState(L"Action");
	SetMonsterState((int32)EMonsterState::CHASE);

#pragma endregion 이펙트

	m_fCurHp = 0.0f;
	SetMonsterState((int32)EMonsterState::DEAD);

#pragma endregion 데미지

}

void CDeacon::PlayDeathSound()
{
	m_wpSoundComponent.lock()->PlaySoundByDistance("Deacon_Dead", ESoundType::DAMAGE);
}

void CDeacon::OnSeeingEnterDelegate()
{
	SetMonsterState((int32)EMonsterState::CHASE);
}

void CDeacon::OnSeeingExitDelegate()
{
	SetMonsterState((int32)EMonsterState::IDLE);
}

void CDeacon::InitializeAIComponent()
{
	// 블랙보드 컴포넌트
	m_wpBlackBoardComponent = CreateActorComponent<CBlackBoardComponent>(L"BlackBoardComponent");
	m_wpBlackBoardComponent.lock()->SetValueAsFVector3(L"Spawn", GetActorPosition()); // 동연
	m_wpBlackBoardComponent.lock()->SetValueAsFVector3(L"Start", GetActorPosition()); // 동연
	m_wpBlackBoardComponent.lock()->SetValueAsFVector3(L"Finish", { 0.0f, 0.0f, 5.0f });
	m_wpBlackBoardComponent.lock()->SetValueAsFloat(L"WaitSeconds", 2.0f);
	m_wpBlackBoardComponent.lock()->SetValueAsFloat(L"AttackTerm", 1.0f);
	m_wpBlackBoardComponent.lock()->SetValueAsFloat(L"Damage", 6.0f);
	m_wpBlackBoardComponent.lock()->SetValueAsInt(L"MonsterState", (int32)EMonsterState::IDLE);

	// 비헤이비어 컴포넌트
	m_wpBehaviorTreeComponent = CreateActorComponent<CBehaviorTreeComponent>(L"BehaviorTreeComponent");
	m_wpBehaviorTreeComponent.lock()->SetBlackBoardComponent(m_wpBlackBoardComponent.lock());

	// 설렉터 컴포지트를 만듭니다.
	shared_ptr<CSelector> spBTSelectorNode = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSelector>(EBTNodeType::COMPOSITE);
	m_wpBehaviorTreeComponent.lock()->AddBTNodeToRoot(spBTSelectorNode);

	/********************
		DEAD 시퀀스
	********************/
	// DEAD 시퀀스
	shared_ptr<CSequence> spBTSequenceNodeA = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSequence>(EBTNodeType::COMPOSITE);
	spBTSelectorNode->AddBTNodeToComposite(spBTSequenceNodeA);

	// DEAD 데코레이터
	shared_ptr<CBTBlackBoardDecorator> spBTBlackBoardDecoratorA = spBTSequenceNodeA->CreateBTDecorator<CBTBlackBoardDecorator>();
	spBTBlackBoardDecoratorA->SetDecoratorByInt(L"MonsterState", EDecoratorQuery::IS_EQUAL_TO, (int32)EMonsterState::DEAD);


	/********************
		 CHASE, ATTACK 설렉터
	********************/
	// CHASE, ATTACK 설렉터
	shared_ptr<CSelector> spBTSelectorNodeB = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSelector>(EBTNodeType::COMPOSITE);
	spBTSelectorNode->AddBTNodeToComposite(spBTSelectorNodeB);

	// CHASE, ATTACK 데코레이터
	shared_ptr<CBTBlackBoardDecorator> spBTBlackBoardDecoratorB = spBTSelectorNodeB->CreateBTDecorator<CBTBlackBoardDecorator>();
	spBTBlackBoardDecoratorB->SetDecoratorByInt(L"MonsterState", EDecoratorQuery::IS_NOT_EQUAL_TO, (int32)EMonsterState::IDLE);

	/********************
		 CHASE 시퀀스
	********************/
	// CHASE 시퀀스
	shared_ptr<CSequence> spBTSequenceNodeB1 = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSequence>(EBTNodeType::COMPOSITE);
	spBTSelectorNodeB->AddBTNodeToComposite(spBTSequenceNodeB1);

	// CHASE 데코레이터
	shared_ptr<CBTBlackBoardDecorator> spBTBlackBoardDecoratorB1 = spBTSequenceNodeB1->CreateBTDecorator<CBTBlackBoardDecorator>();
	spBTBlackBoardDecoratorB1->SetDecoratorByInt(L"MonsterState", EDecoratorQuery::IS_EQUAL_TO, (int32)EMonsterState::CHASE);

	// MOVE 태스크
	shared_ptr<CMoveTask> spMoveTaskB1 = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CMoveTask>(EBTNodeType::TASK);
	spBTSequenceNodeB1->AddBTNodeToComposite(spMoveTaskB1);
	spMoveTaskB1->MoveTo(L"Player");
	spMoveTaskB1->SetRadius(35.0f);

	// SET STATE 태스크
	shared_ptr<CSetStateTask> spSetStateTaskB1 = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSetStateTask>(EBTNodeType::TASK);
	spBTSequenceNodeB1->AddBTNodeToComposite(spSetStateTaskB1);
	spSetStateTaskB1->SetState((int32)EMonsterState::ATTACK);

	/********************
		 ATTACK 시퀀스
	********************/
	// ATTACK 시퀀스
	shared_ptr<CSequence> spBTSequenceNodeB2 = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSequence>(EBTNodeType::COMPOSITE);
	spBTSelectorNodeB->AddBTNodeToComposite(spBTSequenceNodeB2);

	// ATTACK 데코레이터
	shared_ptr<CBTBlackBoardDecorator> spBTBlackBoardDecoratorB2 = spBTSequenceNodeB2->CreateBTDecorator<CBTBlackBoardDecorator>();
	spBTBlackBoardDecoratorB2->SetDecoratorByInt(L"MonsterState", EDecoratorQuery::IS_EQUAL_TO, (int32)EMonsterState::ATTACK);

	// ATTACK 태스크 - 박동연 -
	shared_ptr<CAttackTask> spAttackTaskA1 = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CAttackTask>(EBTNodeType::TASK);
	spBTSequenceNodeB2->AddBTNodeToComposite(spAttackTaskA1);

	// SET STATE 태스크
	shared_ptr<CSetStateTask> spSetStateTaskB2 = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSetStateTask>(EBTNodeType::TASK);
	spBTSequenceNodeB2->AddBTNodeToComposite(spSetStateTaskB2);
	spSetStateTaskB2->SetState((int32)EMonsterState::CHASE);


	/********************
		 IDLE 시퀀스
	`********************/
	// IDLE 시퀀스
	shared_ptr<CSequence> spBTSequenceNodeC = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CSequence>(EBTNodeType::COMPOSITE);
	spBTSelectorNode->AddBTNodeToComposite(spBTSequenceNodeC);

	// IDLE 데코레이터
	shared_ptr<CBTBlackBoardDecorator> spBTBlackBoardDecoratorC = spBTSequenceNodeC->CreateBTDecorator<CBTBlackBoardDecorator>();
	spBTBlackBoardDecoratorC->SetDecoratorByInt(L"MonsterState", EDecoratorQuery::IS_LESS_THAN, (int32)EMonsterState::CHASE);

	// WaitFlying 태스크
	shared_ptr<CWaitFlyingTask> spWaitFlyingTask = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CWaitFlyingTask>(EBTNodeType::TASK);
	spBTSequenceNodeC->AddBTNodeToComposite(spWaitFlyingTask);
	spWaitFlyingTask->SetWaitTime(3.0f);
	spWaitFlyingTask->FlyingTo(L"Finish");

	// REPOSITION 태스크
	shared_ptr<CRepositionTask> spRepositionTask = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CRepositionTask>(EBTNodeType::TASK);
	spBTSequenceNodeC->AddBTNodeToComposite(spRepositionTask);

	// IdleMOVE 태스크
	shared_ptr<CIdleMoveTask> spIdleMoveTask = m_wpBehaviorTreeComponent.lock()->CreateBTNode<CIdleMoveTask>(EBTNodeType::TASK);
	spBTSequenceNodeC->AddBTNodeToComposite(spIdleMoveTask);
	spIdleMoveTask->SetRadius(1.0f);
	spIdleMoveTask->MoveTo(L"Finish");
}

void CDeacon::InitializeSensorComponent()
{
	m_wpSensorComponent = CreateActorComponent<CSensorComponent>(L"SensorComponent");
	m_wpSensorComponent.lock()->SetSeeingRadius(200.0f);

	// 피관찰자 이름, 피관찰자 액터의 포인터, 관찰자 액터의 포인터, 관찰자 액터의 함수
	// std::weak_ptr<CPlayerActor> wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	// m_wpSensorComponent.lock()->BindSeeingEnterDelegate<CDeacon, CPlayerActor>(GetActorName(), wpPlayerActor.lock(), dynamic_pointer_cast<CDeacon>(shared_from_this()), &CDeacon::OnSeeingEnterDelegate);
	// m_wpSensorComponent.lock()->BindSeeingExitDelegate<CDeacon, CPlayerActor>(GetActorName(), wpPlayerActor.lock(), dynamic_pointer_cast<CDeacon>(shared_from_this()), &CDeacon::OnSeeingExitDelegate);
}