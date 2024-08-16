// Default
#include "pch.h"
#include "SceneChangerActor.h"

// Manager
#include "CollisionManager.h"
#include "GameManager.h"

// Framework
#include "Level.h"
#include "World.h"

// Client
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"

// Actor
#include "PlayerActor.h"
#include "LoverboyActor.h"
#include "PenetratorActor.h"
#include "DisperserActor.h"
#include "ChainGunActor.h"

// Component
#include "CubeColliderComponent.h"
using namespace std;

void CSceneChangerActor::Initialize()
{
	// 큐브 콜라이더 컴포넌트
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::INTERACTION);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	SetRootComponent(m_wpCubeColliderComponent);

	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
	CCubeColliderActor::Initialize();
}

void CSceneChangerActor::BeginPlay()
{
	CCubeColliderActor::BeginPlay();
}

int32 CSceneChangerActor::Update(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CSceneChangerActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CSceneChangerActor::Render()
{
	CCubeColliderActor::Render();
}

void CSceneChangerActor::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CSceneChangerActor::Release()
{
	CCubeColliderActor::Release();
}

int32 CSceneChangerActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	shared_ptr<CPlayerActor> spPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	shared_ptr<CLoverboyActor> spLoverboyActor = dynamic_pointer_cast<CLoverboyActor>(GetLevel().lock()->FindActor(L"Loverboy"));
	shared_ptr<CDisperserActor> spDisperserActor = dynamic_pointer_cast<CDisperserActor>(GetLevel().lock()->FindActor(L"Disperser"));
	shared_ptr<CPenetratorActor> spPenetratorActor = dynamic_pointer_cast<CPenetratorActor>(GetLevel().lock()->FindActor(L"Penetrator"));
	shared_ptr<CChainGunActor> spChainGunActor = dynamic_pointer_cast<CChainGunActor>(GetLevel().lock()->FindActor(L"ChainGun"));
	
	NonDestroyData tNonDestroyData;
	
	// 보유한 탄 수, 장전된 발 수
	tNonDestroyData.prLoverboy = { spLoverboyActor->GetBulletHolding(), spLoverboyActor->GetBulletLoaded() };
	tNonDestroyData.prPenetrator = { spPenetratorActor->GetBulletHolding(), spPenetratorActor->GetBulletLoaded() };
	tNonDestroyData.prDisperser = { spDisperserActor->GetBulletHolding(), spDisperserActor->GetBulletLoaded() };
	tNonDestroyData.prChainGun = { spChainGunActor->GetBulletHolding(), spChainGunActor->GetBulletLoaded() };

	// 플레이어
	tNonDestroyData.fCurHp = spPlayer->GetCurHp();
	tNonDestroyData.fCurArmor = spPlayer->GetCurArmor();
	tNonDestroyData.fMaxArmor = spPlayer->GetMaxArmor();

	// 스킬
	tNonDestroyData.bBlinkEnable = spPlayer->IsBlickEnable();
	tNonDestroyData.bRecallEnable = spPlayer->IsRecallEnable();
	tNonDestroyData.bSandevistanEnable = spPlayer->IsSandevistanEnable();

	// 무기
	tNonDestroyData.bPenetratorEnable = spPlayer->IsPenetratorEnable();
	tNonDestroyData.bDisperserEnable = spPlayer->IsDisperserEnable();
	tNonDestroyData.bChainGunEnable = spPlayer->IsChainGunEnable();

	CGameManager::GetInstance()->SetNonDestroyData(tNonDestroyData);

	if (L"SceneChangerToStage2" == m_wstrActorName)
	{
		GetLevel().lock()->GetWorld().lock()->CreateLevel<CStage2>(L"Stage2");
		GetLevel().lock()->GetWorld().lock()->ChangeLevelTo(L"Stage2");
		GetLevel().lock()->GetWorld().lock()->RemoveLevel(L"Stage1");
		return -2;
	}

	if (L"SceneChangerToStage3" == m_wstrActorName)
	{
		GetLevel().lock()->GetWorld().lock()->CreateLevel<CStage3>(L"Stage3");
		GetLevel().lock()->GetWorld().lock()->ChangeLevelTo(L"Stage3");
		GetLevel().lock()->GetWorld().lock()->RemoveLevel(L"Stage2");
		return -2;
	}

	if (L"SceneChangerToStage4" == m_wstrActorName)
	{
		GetLevel().lock()->GetWorld().lock()->CreateLevel<CStage4>(L"Stage4");
		GetLevel().lock()->GetWorld().lock()->ChangeLevelTo(L"Stage4");
		GetLevel().lock()->GetWorld().lock()->RemoveLevel(L"Stage3");
		return -2;
	}
	return 0;
}
