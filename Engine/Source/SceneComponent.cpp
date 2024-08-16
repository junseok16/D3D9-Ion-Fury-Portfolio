#include "pch.h"
#include "SceneComponent.h"

#include "Actor.h"
using namespace std;

void CSceneComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CSceneComponent::BeginPlay()
{
	// ����ƽ ���Ͱ� ���� �ִ� ������Ʈ�� Ʈ�������� �ʱ�ȭ�մϴ�.
	UpdateSceneComponentTransform();
	CActorComponent::BeginPlay();
}

int32 CSceneComponent::Update(const float& _fDeltaSeconds)
{
	// ���̳��� ���Ͱ� ���� �ִ� ������Ʈ�� Ʈ�������� ������Ʈ�մϴ�.
	if (GetOwnerActor().lock()->GetMobility() == EMobilityType::DYNAMIC)
	{
		UpdateSceneComponentTransform();
	}

	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CSceneComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CSceneComponent::Render()
{
	CActorComponent::Render();
}

void CSceneComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CSceneComponent::Release()
{
	CActorComponent::Release();
}

void CSceneComponent::UpdateSceneComponentTransform()
{
	// ���� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
	::D3DXMatrixIdentity(&m_matWorld);

	// ���� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
	::D3DXMatrixIdentity(&m_matLocal);

	// �θ� ������Ʈ�� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
	::D3DXMatrixIdentity(&m_matOwnerWorld);

	// ũ�� ��ȯ ���
	FMatrix matScale;
	::D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	// ȸ�� ��ȯ ���
	FMatrix matRotate[3];
	::D3DXMatrixRotationX(&matRotate[0], D3DXToRadian(m_vRotate.x));
	::D3DXMatrixRotationY(&matRotate[1], D3DXToRadian(m_vRotate.y));
	::D3DXMatrixRotationZ(&matRotate[2], D3DXToRadian(m_vRotate.z));

	// �̵� ��ȯ ���
	FMatrix matTranslate;
	::D3DXMatrixTranslation(&matTranslate, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);

	// ���� ��Ŀ� ũ�� ��ȯ ����� ���մϴ�.
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matScale);

	// ���� ��Ŀ� ȸ�� ��ȯ ����� ���մϴ�.
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[0]);
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[1]);
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[2]);

	// ���� ��Ŀ� �̵� ��ȯ ����� ���մϴ�.
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matTranslate);

	// ������ ���� Ȥ�� ������Ʈ�� ���� ���
	switch (m_bIsRootComponent)
	{
	case true:
		CHECK(!GetOwnerActor().expired());
		m_matOwnerWorld = GetOwnerActor().lock()->GetWorldMatrix();
		break;

	case false:
		CHECK(!GetOwnerComponent().expired());
		m_matOwnerWorld = dynamic_pointer_cast<CSceneComponent>(GetOwnerComponent().lock())->GetWorldMatrix();
		break;
	}
	
	//  ���� ũ�� * ȸ�� * �̵� * �θ� ũ�� * ȸ�� * �̵�
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matOwnerWorld);

	// ������Ʈ�� ���� ����� �����մϴ�.
	m_matWorld = m_matLocal;

	// ������Ʈ�� ���� ��ǥ�� �����մϴ�.
	m_vWorldPosition = { m_matWorld._41, m_matWorld._42, m_matWorld._43 };
}
