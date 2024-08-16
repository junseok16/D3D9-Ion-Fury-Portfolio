#include "pch.h"
#include "CardKeyActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CCardKeyActor::Initialize()
{
	m_eRecoveryType = ERecoveryType::CARDKEY;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"Item_UI_", 0, 5);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 8.f, 10.f });
	//m_wpRectangleMeshComponent.lock()->SetTextureIndex(4);
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CRecoveryActor::Initialize();
}

void CCardKeyActor::BeginPlay()
{
	switch (iCapaType)
	{
	case 0:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		break;
	
	case 1:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		break;
	}


	CRecoveryActor::BeginPlay();
}

int32 CCardKeyActor::Update(const float& _fDeltaSeconds)
{
	return CRecoveryActor::Update(_fDeltaSeconds);
}

int32 CCardKeyActor::LateUpdate(const float& _fDeltaSeconds)
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

void CCardKeyActor::Render()
{
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CRecoveryActor::Render();

	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CCardKeyActor::EndPlay()
{
	CRecoveryActor::EndPlay();
}

void CCardKeyActor::Release()
{
	CRecoveryActor::Release();
}

int32 CCardKeyActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->ColCardKeyItem(m_eRecoveryType);
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_CardKey", 100.f, ESoundType::ITEM);
	m_bIsDead = true;

	return 0;
}

void CCardKeyActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CCardKeyActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{

}
