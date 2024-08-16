#include "pch.h"
#include "SphereActor.h"
#include "RectangleMeshComponent.h"
#include "SphereColliderComponent.h"

#include "CollisionManager.h"
using namespace std;

void CSphereActor::Initialize()
{
	// 사각형 컴포넌트
	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	m_wpRectangleMeshComponent.lock()->SetIsRootComponent(true);
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"../Resource/Texture/Player", 0, 0);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.0f, 10.0f, 10.0f });

	// 콜라이더 컴포넌트
	m_wpSphereColliderComponent = CreateActorComponent<CSphereColliderComponent>(L"SphereColliderComponent");
	m_wpSphereColliderComponent.lock()->SetSphereColliderInfo(1.0f, 30, 30);

	m_wpSphereColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PLAYER);
	m_wpSphereColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpSphereColliderComponent.lock());

	CActor::Initialize();
}

void CSphereActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CSphereActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CSphereActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CSphereActor::Render()
{
	CActor::Render();
}

void CSphereActor::EndPlay()
{
	CActor::EndPlay();
}

void CSphereActor::Release()
{
	CActor::Release();
}

void CSphereActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	int a = 0;
}
