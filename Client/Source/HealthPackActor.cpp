#include "pch.h"
#include "HealthPackActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CHealthPackActor::Initialize()
{
	m_eRecoveryType = ERecoveryType::HEALTHPACK;

	if(iCapaType == 0)
	{
		m_fRecNum = 10.f;
	}
	else if (iCapaType == 1)
	{
		m_fRecNum = 25.f;
	}

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"HealthPack_", 0, 1);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CRecoveryActor::Initialize();
}

void CHealthPackActor::BeginPlay()
{
	switch (iCapaType)
	{
	case 0:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);
		break;

	case 1:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		break;
	}

	CRecoveryActor::BeginPlay();
}

int32 CHealthPackActor::Update(const float& _fDeltaSeconds)
{
	return CRecoveryActor::Update(_fDeltaSeconds);
}

int32 CHealthPackActor::LateUpdate(const float& _fDeltaSeconds)
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

void CHealthPackActor::Render()
{
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CRecoveryActor::Render();

	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CHealthPackActor::EndPlay()
{
	CRecoveryActor::EndPlay();
}

void CHealthPackActor::Release()
{
	CRecoveryActor::Release();
}

int32 CHealthPackActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if(dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetCurHp() < dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetMaxHp())
	{
		dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->ColRecoveryItem(m_eRecoveryType, m_fRecNum);
		m_wpSoundComponent.lock()->PlayPlayerSound("Get_Item", 100.f, ESoundType::ITEM);
		m_bIsDead = true;
	}

	return 0;
}

void CHealthPackActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CHealthPackActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{

}
