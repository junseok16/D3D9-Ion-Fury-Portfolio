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
//	// ���� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
//	::D3DXMatrixIdentity(&m_matWorld);
//
//	// ���� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
//	::D3DXMatrixIdentity(&m_matLocal);
//
//	// ȸ�� ��ȯ ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
//	// ::D3DXMatrixIdentity(&m_matRotate);
//
//	// ũ�� ��ȯ ���
//	FMatrix matScale;
//	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
//
//	// ȸ�� ��ȯ ���
//	FMatrix matRotate[3];
//	D3DXMatrixRotationX(&matRotate[0], D3DXToRadian(m_vRotate.x));
//	D3DXMatrixRotationY(&matRotate[1], D3DXToRadian(m_vRotate.y));
//	D3DXMatrixRotationZ(&matRotate[2], D3DXToRadian(m_vRotate.z));
//	/*
//	// x�� ȸ�� ���
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[0]);
//
//	// y�� ȸ�� ���
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[1]);
//
//	// z�� ȸ�� ���
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[2]);
//
//	// ��Ÿ ȸ�� ���
//	D3DXMatrixMultiply(&m_matRotate, &m_matRotate, &matRotate[2]);
//	*/
//	// �̵� ��ȯ ���
//	FMatrix matTranslate;
//	D3DXMatrixTranslation(&matTranslate, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);
//
//	// ���� ��Ŀ� ũ�� ��ȯ ����� ���մϴ�.
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matScale);
//
//	// ���� ��Ŀ� ȸ�� ��ȯ ����� ���մϴ�.
//	// D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matRotate);
//
//	// x�� ȸ�� ���
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[0]);
//
//	// y�� ȸ�� ���
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[1]);
//
//	// z�� ȸ�� ���
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[2]);
//
//	// ��Ÿ ȸ�� ���
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matMouseRotate);
//
//	// ���� ��Ŀ� �̵� ��ȯ ����� ���մϴ�.
//	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matTranslate);
//
//	/*FMatrix matOwnerWorld;
//	matOwnerWorld = GetOwnerActor().lock()->GetWorldMatrix();
//
//	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matOwnerWorld);*/
//
//	// ������ ���� ��ǥ�� �����մϴ�.
//	m_matWorld = m_matLocal;
//}

void CWeaponActor::UpdateFSM()
{
	std::shared_ptr<CAnimationComponent> wpAnimation = m_wpAnimationComponent.lock();

	if (0 < wpAnimation->GetCurrentAnimationCount() && (L"Attack1" == wpAnimation->GetCurrentState()	// ���ð� ���ε�� �����̴��� ���̵�� �ʱ�ȭ
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
	
	iBulletTotal = m_iBulletHolding + m_iBulletLoaded;			// �� ź������
	iDifference = m_iMagazine - m_iBulletLoaded;				// ������ ź�� źâ �ִ�ġ�� ����
																
	if (m_iBulletLoaded != m_iMagazine && m_iBulletHolding > 0)	// ������ ź�� �ִ밡 �ƴ϶�� & �������� 0���� ũ�ٸ�
	{
		// ���¸� �������� �ٲٰ� �ִϸ��̼� ��� �ǰ� �Ŀ� ������ ���Ѿ���, �ִϸ��̼��� ��µǴ� ������ ������ Ű �����ؾ���
		if (iBulletTotal >= m_iMagazine)						// ������ + �������� źâ���� ũ�ų� ������, ���̸�ŭ ���������� ���� ������ ���ض�
		{
			// ���� �������� �ٲٱ�
			// �ִϸ��̼� ���, ������ ���� ���� �ٸ��� ������ �ִϸ��̼� ���߷���?
			// ����� ������ idle�� �ʱ�ȭ
			m_iBulletLoaded += iDifference;
			m_iBulletHolding -= iDifference;										
		}
		else if (iBulletTotal < m_iMagazine)					// ������ + �������� źâ �ִ뷮���� ������, ��������ŭ�� ���ϰ� 0���� ������
		{
			// ���� �������� �ٲٱ�
			// �ִϸ��̼� ���
			// ����� ������
			m_iBulletLoaded += m_iBulletHolding;
			m_iBulletHolding = 0;
		}
	}
}
