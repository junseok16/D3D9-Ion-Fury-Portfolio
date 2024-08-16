#include "pch.h"
#include "Monster.h"

// Manager
#include "RenderManager.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "InputManager.h"

// Framework
#include "Level.h"
#include "PlayerActor.h"
#include "WeaponActor.h"

// Component
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "CubeColliderComponent.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
using namespace std;

void CMonster::Initialize()
{
	//InitSkullUI();
	CCreature::Initialize();
}

void CMonster::BeginPlay()
{
	//BeginPlaySkullUI();

	CCreature::BeginPlay();
}

int32 CMonster::Update(const float& _fDeltaSeconds)
{
	if (m_bIsTimeSlipped)
	{
		m_fAttackTerm += _fDeltaSeconds / 50.0f;
	}
	else
	{
		m_fAttackTerm += _fDeltaSeconds;
	}

	return CCreature::Update(_fDeltaSeconds);
}

int32 CMonster::LateUpdate(const float& _fDeltaSeconds)
{
	if (DeadCheck(_fDeltaSeconds)) { return -1; }

	return CCreature::LateUpdate(_fDeltaSeconds);
}

void CMonster::Render()
{
	CCreature::Render();
}

void CMonster::EndPlay()
{
	CCreature::EndPlay();
}

void CMonster::Release()
{
	CCreature::Release();
}

void CMonster::SetBillboard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent)
{
	// 뷰 행렬
	FMatrix matView;
	matView = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetCurCamera().lock()->GetPersViewMatrix();

	// 뷰 행렬에서 빌보드 행렬 만들기
	FMatrix matBill;
	D3DXMatrixIdentity(&matBill);
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 월드 행렬
	FMatrix matWorld;
	matWorld = _wpPrimitiveComponent.lock()->GetWorldMatrix();

	// 크기 변환 벡터
	FVector3 vScale = _wpPrimitiveComponent.lock()->GetComponentScale();

	// 크기 변환의 역행렬
	FMatrix matScaleInverse;
	D3DXMatrixScaling(&matScaleInverse, vScale.x, vScale.y, vScale.z);
	D3DXMatrixInverse(&matScaleInverse, 0, &matScaleInverse);

	// 월드행렬에 크기 변환의 역행렬 곱하기
	::D3DXMatrixMultiply(&matWorld, &matScaleInverse, &matWorld);

	// 빌보드 행렬 곱하기
	::D3DXMatrixMultiply(&matWorld, &matBill, &matWorld);

	// 다시 크기 변환 곱하기
	FMatrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	::D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);

	_wpPrimitiveComponent.lock()->SetWorldMatrix(matWorld);
}

void CMonster::SetMonsterState(int32 _eMonsterState)
{
	m_eCurMonsterState = (EMonsterState)_eMonsterState;
}

void CMonster::SetMonsterPhase(int32 _eMonsterPhase)
{
	return;
}

int32 CMonster::GetMonsterState() const
{
	return (int32)m_eCurMonsterState;
}

int32 CMonster::GetMonsterPhase() const
{
	return 0;
}

void CMonster::SetMonsterAnim(int32 _eMonsterAnim)
{
	return;
}

int32 CMonster::GetMonsterAnim() const
{
	return 0;
}

void CMonster::UpdateMonsterPhase() { return; }

void CMonster::UpdateMonsterState() { return; }

void CMonster::UpdateMonsterDirection() { return; }

int32 CMonster::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (EColliderType::CUBE == _wpSrcCollider.lock()->GetColliderType()
		&& EColliderType::CUBE == _wpDstCollider.lock()->GetColliderType())
	{
		if (ECollisionLayerType::GROUND == _wpDstCollider.lock()->GetCollisionLayerType())
		{
			CCollisionManager::BlockCubeToCube
			(
				dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
				dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
				m_wpPhysicsComponent.lock()->GetGravityValue()
			);
		}

		if (ECollisionLayerType::WALL == _wpDstCollider.lock()->GetCollisionLayerType())
		{
			CCollisionManager::BlockCubeToCube
			(
				dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
				dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
				m_fSpeed
			);
		}
	}

	// m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
	m_bIsCollided = true;

	return 0;
}

void CMonster::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);

	//// 큐브 충돌
	//if (EColliderType::CUBE == _wpSrcCollider.lock()->GetColliderType()
	//	&& EColliderType::CUBE == _wpDstCollider.lock()->GetColliderType())
	//{
	//	if (ECollisionLayerType::GROUND == _wpDstCollider.lock()->GetCollisionLayerType())
	//	{
	//		CCollisionManager::BlockCubeToCube
	//		(
	//			dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
	//			dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
	//			m_wpPhysicsComponent.lock()->GetGravityValue()
	//		);
	//	}

	//	if (ECollisionLayerType::WALL == _wpDstCollider.lock()->GetCollisionLayerType())
	//	{
	//		CCollisionManager::BlockCubeToCube
	//		(
	//			dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
	//			dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
	//			m_fSpeed
	//		);
	//	}
	//}
}

void CMonster::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	// 큐브 충돌
	/*if (EColliderType::CUBE == _wpSrcCollider.lock()->GetColliderType()
		&& EColliderType::CUBE == _wpDstCollider.lock()->GetColliderType())
	{
		if (ECollisionLayerType::GROUND == _wpDstCollider.lock()->GetCollisionLayerType())
		{
			CCollisionManager::BlockCubeToCube
			(
				dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
				dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
				m_wpPhysicsComponent.lock()->GetGravityValue()
			);
		}

		if (ECollisionLayerType::WALL == _wpDstCollider.lock()->GetCollisionLayerType())
		{
			CCollisionManager::BlockCubeToCube
			(
				dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
				dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
				m_fSpeed
			);
		}
	}*/

	m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
	m_bIsCollided = false;
}

void CMonster::InitSkullUI()
{
	// 동준 추가
	m_wpMonsterSkullComponent = CreateActorComponent<CAnimationComponent>(L"Monster_Skull_UIComponent");
	m_wpMonsterSkullComponent.lock()->SettingAnimationInfo(L"Monster_Skull_UI_", 0, 1, L"Monster_Skull_UI_1", EAnimationType::DESIGNATED_TIME, 0.f);
	SetRootComponent(m_wpMonsterSkullComponent);
	//m_wpMonsterSkullComponent.lock()->GetOwnerActor().lock()->SetActorPosition({ 0.f, 50.f, 0.f });
	m_wpMonsterSkullComponent.lock()->SetComponentScale({ 0.1f, 0.1f, 0.1f });
	m_wpMonsterSkullComponent.lock()->SetComponentLocalPosition({ 0.f, 0.4f, 0.f });
	//m_wpMonsterSkullComponent.lock()->SetIsAnimate(false);
	//m_wpMonsterSkullComponent.lock()->SetIsRender(false);
	m_wpMonsterSkullComponent.lock()->SetCurFrame(0);
	///////////////////////////////////////////
}

void CMonster::BeginPlaySkullUI()
{
	// 동준 추가입니다 
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	
	m_wpMonsterSkullComponent.lock()->AddState(L"Monster_Skull_UI_1", 0, 1);
	//
}
	
void CMonster::UpdateSkullUI(std::weak_ptr<CAnimationComponent> _wpMonseterActor)
{
	FVector3 fv = m_wpPlayerActor.lock()->GetActorWorldPosition() - _wpMonseterActor.lock()->GetOwnerActor().lock()->GetActorWorldPosition();
	float fDis = D3DXVec3Length(&fv);

	if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::RIGHT_BUTTON) 
		&& m_wpPlayerActor.lock()->GetCurrentWeapon().lock()->GetWeaponType() == EWeaponType::LOVERBOY 
		/*&& fDis <= 100.f*/)
	{
		m_wpMonsterSkullComponent.lock()->SetCurFrame(1);
	}
	else 
	{
		m_wpMonsterSkullComponent.lock()->SetCurFrame(0);
	}

}

int32 CMonster::DeadCheck(const float& _fDeltaSeconds)
{
	if (L"Dead" == m_wpAnimationComponent.lock()->GetCurrentState())
	{
		if (!m_bIsColliderDeleted)
		{
			CCollisionManager::GetInstance()->RemoveColliderComponent(m_wpCubeColliderComponent);
			m_bIsColliderDeleted = true;
		}

		if (!m_bIsTimeSlipped)
		{
			m_fDeadTime += _fDeltaSeconds;
		}
		else
		{
			m_fDeadTime += _fDeltaSeconds / 50.0f;
		}

		if (m_fDeadTime >= 0.5f)
		{
			CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
			GetLevel().lock()->RemoveActor(GetActorName());
			return 1;
		}
	}
	return 0;
}