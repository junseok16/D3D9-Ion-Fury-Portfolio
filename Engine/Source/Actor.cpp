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

	// 회전 행렬을 초기화합니다.
	::D3DXMatrixIdentity(&m_matMouseRotate);

	for (auto& pair : m_umapActorComponents)
	{
		pair.second->Initialize();
	}
}

void CActor::BeginPlay()
{
	// 스태틱 액터의 트랜스폼을 초기화합니다.
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
		// 다이나믹 액터의 트랜스폼을 업데이트합니다.
		UpdateActorTransform();
	}
	
	// 액터의 깊이 값을 갱신합니다.
	UpdateActorDepthZ();

	// 컴포넌트를 업데이트합니다.
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
	// 월드 행렬을 단위 행렬로 초기화합니다.
	::D3DXMatrixIdentity(&m_matWorld);

	// 로컬 행렬을 단위 행렬로 초기화합니다.
	::D3DXMatrixIdentity(&m_matLocal);

	// 회전 변환 행렬을 단위 행렬로 초기화합니다.
	// ::D3DXMatrixIdentity(&m_matRotate);

	// 크기 변환 행렬
	FMatrix matScale;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	// 회전 변환 행렬
	FMatrix matRotate[3];
	D3DXMatrixRotationX(&matRotate[0], D3DXToRadian(m_vRotate.x));
	D3DXMatrixRotationY(&matRotate[1], D3DXToRadian(m_vRotate.y));
	D3DXMatrixRotationZ(&matRotate[2], D3DXToRadian(m_vRotate.z));
	
	// 이동 변환 행렬
	FMatrix matTranslate;
	D3DXMatrixTranslation(&matTranslate, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);

	// 로컬 행렬에 크기 변환 행렬을 곱합니다.
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matScale);

	// 로컬 행렬에 회전 변환 행렬을 곱합니다.
	// D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matRotate);

	// x축 회전 행렬
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[0]);

	// y축 회전 행렬
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[1]);

	// z축 회전 행렬
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[2]);

	// 기타 회전 행렬
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matMouseRotate);

	// 로컬 행렬에 이동 변환 행렬을 곱합니다.
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matTranslate);

	// 액터의 월드 좌표를 갱신합니다.
	m_matWorld = m_matLocal;

	m_vWorldPosition = { m_matWorld._41, m_matWorld._42, m_matWorld._43 };
}

void CActor::UpdateActorDepthZ()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	// 뷰 행렬을 구합니다.
	FMatrix matCameraWorld;
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_pD3DDevice9->GetTransform(D3DTS_VIEW, &matCameraWorld);
	D3DXMatrixInverse(&matCameraWorld, 0, &matCameraWorld);

	// 카메라 위치를 구합니다.
	FVector3 vCameraPosition{ matCameraWorld._41, matCameraWorld._42, matCameraWorld._43 };

	// 액터의 위치를 구합니다.
	FVector3 vLengthVector = vCameraPosition - GetActorWorldPosition();

	// 깊이 값을 갱신합니다.
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

