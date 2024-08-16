#include "pch.h"
#include "SyringeActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CSyringeActor::Initialize()
{
	m_eItemType = EItemType::RECOVERY;
	m_eRecoveryType = ERecoveryType::SYRINGE;
	m_fRecNum = 5.f;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"Syringe_", 0, 0);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CRecoveryActor::Initialize();
}

void CSyringeActor::BeginPlay()
{
	CRecoveryActor::BeginPlay();
}

int32 CSyringeActor::Update(const float& _fDeltaSeconds)
{
	return CRecoveryActor::Update(_fDeltaSeconds);
}

int32 CSyringeActor::LateUpdate(const float& _fDeltaSeconds)
{
	if (m_bIsDead)
	{
		CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
		GetLevel().lock()->RemoveActor(GetActorName());
		return -1;
	}

	SetBillboard(m_wpRectangleMeshComponent);

	return CRecoveryActor::LateUpdate(_fDeltaSeconds);
}

void CSyringeActor::Render()
{
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CRecoveryActor::Render();

	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CSyringeActor::EndPlay()
{
	CRecoveryActor::EndPlay();
}

void CSyringeActor::Release()
{
	CRecoveryActor::Release();
}

int32 CSyringeActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->ColRecoveryItem(m_eRecoveryType, m_fRecNum);
	dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->SetSpeed(70.f);
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_Item", 100.f, ESoundType::ITEM);
	m_bIsDead = true;

	return 0;
}

void CSyringeActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CSyringeActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{

}
