#include "pch.h"
#include "ArmorPieceActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CArmorPieceActor::Initialize()
{
	m_eRecoveryType = ERecoveryType::ARMORPIECE;

	m_fRecNum = 1.f;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"ArmorPiece_", 0, 0);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 6.0f, 6.0f, 6.0f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CRecoveryActor::Initialize();
}

void CArmorPieceActor::BeginPlay()
{
	CRecoveryActor::BeginPlay();
}

int32 CArmorPieceActor::Update(const float& _fDeltaSeconds)
{
	return CRecoveryActor::Update(_fDeltaSeconds);
}

int32 CArmorPieceActor::LateUpdate(const float& _fDeltaSeconds)
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

void CArmorPieceActor::Render()
{
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CRecoveryActor::Render();

	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CArmorPieceActor::EndPlay()
{
	CRecoveryActor::EndPlay();
}

void CArmorPieceActor::Release()
{
	CRecoveryActor::Release();
}

int32 CArmorPieceActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if(dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetCurArmor() < dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetMaxArmor())
	{
		dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->ColRecoveryItem(m_eRecoveryType, m_fRecNum);
		m_wpSoundComponent.lock()->PlayPlayerSound("Get_Item", 100.f, ESoundType::ITEM);
		m_bIsDead = true;
	}

	return 0;
}

void CArmorPieceActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CArmorPieceActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}
