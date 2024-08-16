#include "pch.h"
#include "ColliderComponent.h"
#include "CollisionManager.h"
using namespace std;

void CColliderComponent::Initialize()
{
	CPrimitiveComponent::Initialize();
	CreateVertices();
	CreateIndices();
}

void CColliderComponent::BeginPlay()
{
	CPrimitiveComponent::BeginPlay();
}

int32 CColliderComponent::Update(const float& _fDeltaSeconds)
{
	return CPrimitiveComponent::Update(_fDeltaSeconds);
}

int32 CColliderComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CPrimitiveComponent::LateUpdate(_fDeltaSeconds);
}

void CColliderComponent::Render()
{
	CPrimitiveComponent::Render();
}

void CColliderComponent::EndPlay()
{
	CPrimitiveComponent::EndPlay();
}

void CColliderComponent::Release()
{
	if (m_pMesh) m_pMesh->Release();

	// TODO: ������ �Ҹ��ڸ� ȣ���ұ��?
	m_usetColliderComponents.clear();


	/*
	*  �ݸ��� �Ŵ������� �� �ݶ��̴� ������Ʈ�� �����մϴ�.
	*/
	CCollisionManager::GetInstance()->RemoveColliderComponent(dynamic_pointer_cast<CColliderComponent>(shared_from_this()));
	CPrimitiveComponent::Release();
}

void CColliderComponent::CreateVertices()
{
	switch (m_eColliderType)
	{
	case EColliderType::RECT:
	{
		ColorVertex* pVertex = nullptr;
		ENSURE(m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0));

		for (int32 nth = 0; nth < m_iNumVertices; ++nth)
		{
			pVertex[nth].position = m_vecColorVertices[nth].position;
			pVertex[nth].color = m_vecColorVertices[nth].color;

			m_vecVertexPos.push_back(pVertex[nth].position);
		}
		ENSURE(m_pVertexBuffer->Unlock());
		m_vecColorVertices.clear();
	}
		break;

	case EColliderType::CUBE:
	{
		ColorVertex* pVertex = nullptr;
		ENSURE(m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0));

		for (int32 nth = 0; nth < m_iNumVertices; ++nth)
		{
			pVertex[nth].position = m_vecColorVertices[nth].position;
			pVertex[nth].color = m_vecColorVertices[nth].color;

			m_vecVertexPos.push_back(pVertex[nth].position);
		}
		ENSURE(m_pVertexBuffer->Unlock());
		m_vecColorVertices.clear();
	}
		break;

	case EColliderType::SPHERE:
		break;

	case EColliderType::ENUM_END:
		CHECKF(false, TEXT("Collider type isn't designated."))
		break;
	}
}

void CColliderComponent::CreateIndices()
{
	switch (m_eColliderType)
	{
	case EColliderType::RECT:
	{
		ColorIndex* pIndex = nullptr;
		ENSURE(m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0));

		for (int32 nth = 0; nth < m_iNumTriangles; ++nth)
		{
			pIndex[nth]._0 = m_vecColorIndices[nth]._0;
			pIndex[nth]._1 = m_vecColorIndices[nth]._1;
			pIndex[nth]._2 = m_vecColorIndices[nth]._2;

			m_vecVertexIndices.push_back({ (float)pIndex[nth]._0 , (float)pIndex[nth]._1 , (float)pIndex[nth]._2 });
		}

		ENSURE(m_pIndexBuffer->Unlock());
		m_vecColorIndices.clear();
	}
	break;

	case EColliderType::CUBE:
	{
		ColorIndex* pIndex = nullptr;
		ENSURE(m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0));

		for (int32 nth = 0; nth < m_iNumTriangles; ++nth)
		{
			pIndex[nth]._0 = m_vecColorIndices[nth]._0;
			pIndex[nth]._1 = m_vecColorIndices[nth]._1;
			pIndex[nth]._2 = m_vecColorIndices[nth]._2;

			m_vecVertexIndices.push_back({ (float)pIndex[nth]._0 , (float)pIndex[nth]._1 , (float)pIndex[nth]._2 });
		}

		ENSURE(m_pIndexBuffer->Unlock());
		m_vecColorIndices.clear();
	}
		break;

	case EColliderType::SPHERE:

		break;

	case EColliderType::ENUM_END:
		CHECKF(false, TEXT("Collider type isn't designated."));
		break;
	}
}

bool CColliderComponent::IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	return false;
}

bool CColliderComponent::IsCollisionLayerOverlapped(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	// �ݸ��� ���̾� Ÿ���� �ҷ��ɴϴ�.
	uint8 iCollisionLayerType = (uint8)_wpColliderComponent.lock()->GetCollisionLayerType();

	// �ݸ��� ���̾ ���� �浹�ϵ��� ������ ���, ���� ��ȯ�մϴ�.
	if (m_iCollisionLayer & (1 << iCollisionLayerType))
	{
		return true;
	}

	return false;
}

void CColliderComponent::AddCollisionLayer(ECollisionLayerType _eCollisionLayerType)
{
	m_iCollisionLayer |= (1 << (uint32)_eCollisionLayerType);
}

void CColliderComponent::RemoveCollisionLayer(ECollisionLayerType _eCollisionLayerType)
{
	m_iCollisionLayer &= ~(1 << (uint32)_eCollisionLayerType);
}