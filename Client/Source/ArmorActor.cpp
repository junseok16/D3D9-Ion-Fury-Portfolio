#include "pch.h"
#include "ArmorActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CArmorActor::Initialize()
{
	m_eRecoveryType = ERecoveryType::ARMOR;

	if (iCapaType == 0)
	{
		m_fRecNum = 50.f;
	}
	else if (iCapaType == 1)
	{
		m_fRecNum = 100.f;
	}
	else if (iCapaType == 2)
	{
		m_fRecNum = 200.f;
	}

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"Armor_", 0, 2);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CRecoveryActor::Initialize();
}

void CArmorActor::BeginPlay()
{
	switch (iCapaType)
	{
	case 0:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);
		break;

	case 1:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		break;

	case 2:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(2);
		break;
	}


	CRecoveryActor::BeginPlay();
}

int32 CArmorActor::Update(const float& _fDeltaSeconds)
{
	return CRecoveryActor::Update(_fDeltaSeconds);
}

int32 CArmorActor::LateUpdate(const float& _fDeltaSeconds)
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

void CArmorActor::Render()
{
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CRecoveryActor::Render();

	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CArmorActor::EndPlay()
{
	CRecoveryActor::EndPlay();
}

void CArmorActor::Release()
{
	CRecoveryActor::Release();
}

int32 CArmorActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->ColRecoveryItem(m_eRecoveryType, m_fRecNum);
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_Armor", 100.f, ESoundType::ITEM);
	m_bIsDead = true;

	return 0;
}

void CArmorActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CArmorActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{

}
