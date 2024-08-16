#include "pch.h"
#include "Actor.h"
#include "SceneComponent.h"
#include "DeviceManager.h"
#include "RenderManager.h"

#include "Level.h"

#include "PrimitiveComponent.h"

void CActor::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();

	// ȸ�� ����� �ʱ�ȭ�մϴ�.
	::D3DXMatrixIdentity(&m_matMouseRotate);

	for (auto& pair : m_umapActorComponents)
	{
		pair.second->Initialize();
	}
}

void CActor::BeginPlay()
{
	// ����ƽ ������ Ʈ�������� �ʱ�ȭ�մϴ�.
	UpdateActorTransform();

	for (auto& pair : m_umapActorComponents)
	{
		pair.second->BeginPlay();
	}
}

int32 CActor::Update(const float& _fDeltaSeconds)
{
	if (m_eMobility == EMobilityType::DYNAMIC)
	{
		// ���̳��� ������ Ʈ�������� ������Ʈ�մϴ�.
		UpdateActorTransform();
	}
	
	// ������ ���� ���� �����մϴ�.
	UpdateActorDepthZ();

	// ������Ʈ�� ������Ʈ�մϴ�.
	for (auto& pair : m_umapActorComponents)
	{
		int32 iResult = 0;

		if (m_bIsTimeSlipped)
		{
			int32 iResult = pair.second->Update(_fDeltaSeconds / 50.0f);
		}
		else
		{
			int32 iResult = pair.second->Update(_fDeltaSeconds);
		}
		
		if (iResult != 0) { return -1; }
	}

	CRenderManager::GetInstance()->InsertActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
	return 0;
}

int32 CActor::LateUpdate(const float& _fDeltaSeconds)
{
	for (auto& pair : m_umapActorComponents)
	{
		int32 iResult = 0;

		if (m_bIsTimeSlipped)
		{
			int32 iResult = pair.second->LateUpdate(_fDeltaSeconds / 50.0f);
		}
		else
		{
			int32 iResult = pair.second->LateUpdate(_fDeltaSeconds);
		}
		
		if (iResult != 0) { return -1; }
	}
	return 0;
}

void CActor::Render()
{
	for (auto& pair : m_umapActorComponents)
	{
		pair.second->Render();
	}
}

void CActor::EndPlay()
{
	for (auto& pair : m_umapActorComponents)
	{
		pair.second->EndPlay();
	}
}

void CActor::Release()
{
	for (auto& pair : m_umapActorComponents)
	{
		pair.second->Release();
		pair.second.reset();
	}
}

std::shared_ptr<CActorComponent> CActor::FindActorComponent(const std::wstring& _wstrActorComponent)
{
	if (m_umapActorComponents.find(_wstrActorComponent) == m_umapActorComponents.end()) { return nullptr; }
	return m_umapActorComponents[_wstrActorComponent];	
}

void CActor::UpdateActorTransform()
{
	// ���� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
	::D3DXMatrixIdentity(&m_matWorld);

	// ���� ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
	::D3DXMatrixIdentity(&m_matLocal);

	// ȸ�� ��ȯ ����� ���� ��ķ� �ʱ�ȭ�մϴ�.
	// ::D3DXMatrixIdentity(&m_matRotate);

	// ũ�� ��ȯ ���
	FMatrix matScale;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	// ȸ�� ��ȯ ���
	FMatrix matRotate[3];
	D3DXMatrixRotationX(&matRotate[0], D3DXToRadian(m_vRotate.x));
	D3DXMatrixRotationY(&matRotate[1], D3DXToRadian(m_vRotate.y));
	D3DXMatrixRotationZ(&matRotate[2], D3DXToRadian(m_vRotate.z));
	
	// �̵� ��ȯ ���
	FMatrix matTranslate;
	D3DXMatrixTranslation(&matTranslate, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);

	// ���� ��Ŀ� ũ�� ��ȯ ����� ���մϴ�.
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matScale);

	// ���� ��Ŀ� ȸ�� ��ȯ ����� ���մϴ�.
	// D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matRotate);

	// x�� ȸ�� ���
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[0]);

	// y�� ȸ�� ���
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[1]);

	// z�� ȸ�� ���
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[2]);

	// ��Ÿ ȸ�� ���
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matMouseRotate);

	// ���� ��Ŀ� �̵� ��ȯ ����� ���մϴ�.
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matTranslate);

	// ������ ���� ��ǥ�� �����մϴ�.
	m_matWorld = m_matLocal;

	m_vWorldPosition = { m_matWorld._41, m_matWorld._42, m_matWorld._43 };
}

void CActor::UpdateActorDepthZ()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	// �� ����� ���մϴ�.
	FMatrix matCameraWorld;
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_pD3DDevice9->GetTransform(D3DTS_VIEW, &matCameraWorld);
	D3DXMatrixInverse(&matCameraWorld, 0, &matCameraWorld);

	// ī�޶� ��ġ�� ���մϴ�.
	FVector3 vCameraPosition{ matCameraWorld._41, matCameraWorld._42, matCameraWorld._43 };

	// ������ ��ġ�� ���մϴ�.
	FVector3 vLengthVector = vCameraPosition - GetActorWorldPosition();

	// ���� ���� �����մϴ�.
	m_fDepthZ = D3DXVec3Length(&vLengthVector);
}

int32 CActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return;
}

void CActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return;
}

void CActor::SetRootComponent(std::weak_ptr<CSceneComponent> _wpSceneComponent)
{
	CHECK(!_wpSceneComponent.expired())
	m_wpRootComponent = _wpSceneComponent;
	_wpSceneComponent.lock()->SetIsRootComponent(true);
}

FVector3 CActor::GetForwardVector() const
{
	return { m_matWorld.m[2][0], m_matWorld.m[2][1], m_matWorld.m[2][2] };
}

FVector3 CActor::GetUpVector() const
{
	return { m_matWorld.m[1][0], m_matWorld.m[1][1],m_matWorld.m[1][2] };
}

FVector3 CActor::GetRightVector() const
{
	return { m_matWorld.m[0][0], m_matWorld.m[0][1],m_matWorld.m[0][2] };
}

