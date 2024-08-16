#include "pch.h"
#include "WeaponActor.h"

#include "Level.h"
#include "PlayerActor.h"

#include "AnimationComponent.h"
using namespace std;

void CWeaponActor::Initialize()
{
	SetRenderType(ERenderType::ORTHOGONAL);
	SetOwnerActor(dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player")));
	CActor::Initialize();
}

void CWeaponActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CWeaponActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CWeaponActor::LateUpdate(const float& _fDeltaSeconds)
{
	SynchronizationVector();
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CWeaponActor::Render()
{
	if(m_bEnable)
		CActor::Render();
}

void CWeaponActor::EndPlay()
{
	CActor::EndPlay();
}

void CWeaponActor::Release()
{
	CActor::Release();
}

//void CWeaponActor::UpdateActorTransform()
//{
//	// CHECK(!CActor::GetOwnerActor().expired());
//
//	// 월드 행렬을 단위 행렬로 초기화합니다.
//	::D3DXMatrixIdentity(&m_matWorld);
//
//	// 로컬 행렬을 단위 행렬로 초기화합니다.
//	::D3DXMatrixIdentity(&m_matLocal);
//
//	// 회전 변환 행렬을 단위 행렬로 초기화합니다.
//	// ::D3DXMatrixIdentity(&m_matRotate);
//
//	// 크기 변환 행렬
//	FMatrix matScale;
//	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
//
//	// 회전 변환 행렬
//	FMatrix matRotate[3];
//	D3DXMatrixRotationX(&matRotate[0], D3DXToRadian(m_vRotate.x));
//	D3DXMatrixRotationY(&matRotate[1], D3DXToRadian(m_vRotate.y));
//	D3DXMatrixRotationZ(&matRotate[2], D3DXToRadian(m_vRotate.z));
//	/*
//	// x축 회전 행렬
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[0]);
//
//	// y축 회전 행렬
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[1]);
//
//	// z축 회전 행렬
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[2]);
//
//	// 기타 회전 행렬
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[2]);
//	*/
//	// 이동 변환 행렬
//	FMatrix matTranslate;
//	D3DXMatrixTranslation(&matTranslate, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);
//
//	// 로컬 행렬에 크기 변환 행렬을 곱합니다.
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matScale);
//
//	// 로컬 행렬에 회전 변환 행렬을 곱합니다.
//	// D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matRotate);
//
//	// x축 회전 행렬
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[0]);
//
//	// y축 회전 행렬
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[1]);
//
//	// z축 회전 행렬
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[2]);
//
//	// 기타 회전 행렬
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matMouseRotate);
//
//	// 로컬 행렬에 이동 변환 행렬을 곱합니다.
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matTranslate);
//
//	/*FMatrix matOwnerWorld;
//	matOwnerWorld = GetOwnerActor().lock()->GetWorldMatrix();
//
//	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matOwnerWorld);*/
//
//	// 액터의 월드 좌표를 갱신합니다.
//	m_matWorld = m_matLocal;
//}

void CWeaponActor::UpdateFSM()
{
	std::shared_ptr<CAnimationComponent> wpAnimation = m_wpAnimationComponent.lock();

	if (0 < wpAnimation->GetCurrentAnimationCount() && (L"Attack1" == wpAnimation->GetCurrentState()	// 어택과 리로드는 루프이더라도 아이들로 초기화
														|| L"Attack2" == wpAnimation->GetCurrentState()
														|| L"Reload" == wpAnimation->GetCurrentState()))
	{
		wpAnimation->SetCurrentState(L"Idle");
		wpAnimation->SetAnimationType(EAnimationType::LOOP);
		wpAnimation->SetCurrentAnimationCount(0);
		wpAnimation->SetCurFrame(wpAnimation->GetStateFrame(L"Idle").first);
		wpAnimation->SetIsAnimate(true);
	}
}

void CWeaponActor::SynchronizationVector()
{
	m_matWorld = GetOwnerActor().lock()->GetWorldMatrix();
	FVector3 v = GetForwardVector();
}

void CWeaponActor::SetBulletHolding(int32 iBulletNum)
{
	int32 iBulletTotal;

	iBulletTotal = m_iBulletHolding + m_iBulletLoaded;

	if (iBulletTotal < m_iBulletMaximum)
	{
		if (iBulletNum + iBulletTotal > m_iBulletMaximum)
		{
			m_iBulletHolding += m_iBulletMaximum - iBulletTotal;
		}
		else
		{
			m_iBulletHolding += iBulletNum;
		}
	}
}

void CWeaponActor::Reload()
{
	int32 iBulletTotal, iDifference;
	
	iBulletTotal = m_iBulletHolding + m_iBulletLoaded;			// 총 탄보유량
	iDifference = m_iMagazine - m_iBulletLoaded;				// 장전된 탄과 탄창 최대치의 차이
																
	if (m_iBulletLoaded != m_iMagazine && m_iBulletHolding > 0)	// 장전된 탄이 최대가 아니라면 & 보유량이 0보다 크다면
	{
		// 상태를 장전으로 바꾸고 애니메이션 출력 되고난 후에 재장전 시켜야함, 애니메이션이 출력되는 동안은 재장전 키 무시해야함
		if (iBulletTotal >= m_iMagazine)						// 보유량 + 장전량이 탄창보다 크거나 같을때, 차이만큼 보유량에서 빼고 장전에 더해라
		{
			// 상태 장전으로 바꾸기
			// 애니메이션 재생, 프레임 수가 전부 다른데 장전과 애니메이션 맞추려면?
			// 재생이 끝나면 idle로 초기화
			m_iBulletLoaded += iDifference;
			m_iBulletHolding -= iDifference;										
		}
		else if (iBulletTotal < m_iMagazine)					// 보유량 + 장전량이 탄창 최대량보다 작을때, 보유량만큼만 더하고 0으로 맞춰줌
		{
			// 상태 장전으로 바꾸기
			// 애니메이션 재생
			// 재생이 끝나면
			m_iBulletLoaded += m_iBulletHolding;
			m_iBulletHolding = 0;
		}
	}
}
