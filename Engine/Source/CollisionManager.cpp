// default
#include "pch.h"
#include "CollisionManager.h"

// Managers
#include "TimerManager.h"
#include "DeviceManager.h"

// Actors
#include "Creature.h"

// Components
#include "PhysicsComponent.h"
#include "PrimitiveComponent.h"
#include "ColliderComponent.h"
#include "RectColliderComponent.h"
#include "CubeColliderComponent.h"
#include "SphereColliderComponent.h"
using namespace std;

IMPLEMENT_SINGLETON(CCollisionManager)

HRESULT CCollisionManager::Initialize()
{
	return S_OK;
}

int32 CCollisionManager::Update()
{
	vector<shared_ptr<CColliderComponent>>& vecColliderComponents = m_vecColliderComponents;

	size_t iSize = vecColliderComponents.size();
	for (uint32 outerLoopIndex = 0; outerLoopIndex < iSize; ++outerLoopIndex)
	{
		for (uint32 innerLoopIndex = outerLoopIndex + 1; innerLoopIndex < iSize; ++innerLoopIndex)
		{
			shared_ptr<CColliderComponent> spSrc = vecColliderComponents[innerLoopIndex];
			shared_ptr<CColliderComponent> spDst = vecColliderComponents[outerLoopIndex];

#pragma region 충돌 연산 최적화

			// 1. 두 육면체의 최대 반지름 길이를 구합니다.
			FVector3 vSrcToVertex0 = spSrc->GetComponentWorldPosition() - spSrc->GetVertexWorldPos(0);
			FVector3 vDstToVertex0 = spDst->GetComponentWorldPosition() - spDst->GetVertexWorldPos(0);

			float fSrcRadius = D3DXVec3Length(&vSrcToVertex0);
			float fDstRadius = D3DXVec3Length(&vDstToVertex0);

			// 2. 만약 최대 반지름 길이의 합보다 두 육면체 사이의 거리가 길다면 false를 반환합니다.
			FVector3 vSrcToDst = spSrc->GetComponentWorldPosition() - spDst->GetComponentWorldPosition();

			if (fSrcRadius + fDstRadius < D3DXVec3Length(&vSrcToDst))
				continue;

#pragma endregion

			// 두 콜라이더가 충돌한 경우
			if (spSrc->IsCollided(spDst) == true)
			{
				// 이전에 충돌하지 않고 방금 충돌한 경우
				std::unordered_set<std::shared_ptr<CColliderComponent>>& usetColliderComponents = spSrc->GetColliderComponents();

				if (usetColliderComponents.find(spDst) == usetColliderComponents.end())
				{
					// CollisionEnter의 결과를 받아오는 변수 iEnterResult
					//int32 iSrcEnterResult;
					//int32 iDstEnterResult;

					// 결과가 2(신 체인지)가 나오면 바로 함수를 빠져나갑니다.
					if (spSrc->GetOwnerActor().lock()->OnCollisionEnter(spSrc, spDst) == -2) { return -2; }
					if (spDst->GetOwnerActor().lock()->OnCollisionEnter(spDst, spSrc) == -2) { return -2; }

					/*
					if (-2 == iSrcEnterResult || -2 == iDstEnterResult)
						return -2;
					*/
					usetColliderComponents.insert(spSrc);
					usetColliderComponents.insert(spDst);
				}
				// 이전에 이미 충돌한 경우
				else
				{
					spSrc->GetOwnerActor().lock()->OnCollisionStay(spSrc, spDst);
					spDst->GetOwnerActor().lock()->OnCollisionStay(spDst, spSrc);
				}
			}
			// 두 콜라이더가 충돌하지 않은 경우
			else
			{
				// 이전에 충돌했다가 방금 충돌하지 않은 경우
				unordered_set<shared_ptr<CColliderComponent>>& usetColliderComponents = spSrc->GetColliderComponents();

				if (usetColliderComponents.find(spDst) != usetColliderComponents.end())
				{
					spSrc->GetOwnerActor().lock()->OnCollisionExit(spSrc, spDst);
					spDst->GetOwnerActor().lock()->OnCollisionExit(spDst, spSrc);

					usetColliderComponents.erase(spSrc);
					usetColliderComponents.erase(spDst);
				}
			}
		}
	}

	return 0;
}

void CCollisionManager::Release()
{
	for (auto& spColliderComponent : m_vecColliderComponents)
	{
		spColliderComponent.reset();
	}

	m_vecColliderComponents.clear();

	for (auto& spPrimitiveComponents : m_vecPrimitiveComponents)
	{
		spPrimitiveComponents.reset();
	}

	m_vecPrimitiveComponents.clear();
	m_upInstance.reset();
}

void CCollisionManager::AddColliderComponent(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	CHECK(!_wpColliderComponent.expired());
	m_vecColliderComponents.push_back(_wpColliderComponent.lock());
}

void CCollisionManager::RemoveColliderComponent(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	CHECK(!_wpColliderComponent.expired());
	for (auto iter = m_vecColliderComponents.begin(); iter != m_vecColliderComponents.end(); ++iter)
	{
		if (*iter == _wpColliderComponent.lock())
		{
			(*iter).reset();
			m_vecColliderComponents.erase(iter);
			break;
		}
	}
	// m_vecColliderComponents.erase(remove(m_vecColliderComponents.begin(), m_vecColliderComponents.end(), _wpColliderComponent.lock()), m_vecColliderComponents.end());
}

void CCollisionManager::AddPrimitiveComponent(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent)
{
	CHECK(!_wpPrimitiveComponent.expired());
	m_vecPrimitiveComponents.push_back(_wpPrimitiveComponent.lock());
}

void CCollisionManager::RemovePrimitiveComponent(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent)
{
	CHECK(!_wpPrimitiveComponent.expired());
	for (auto iter = m_vecPrimitiveComponents.begin(); iter != m_vecPrimitiveComponents.end(); ++iter)
	{
		if (*iter == _wpPrimitiveComponent.lock())
		{
			(*iter).reset();
			m_vecPrimitiveComponents.erase(iter);
			break;
		}
	}
	// m_vecPrimitiveComponents.erase(remove(m_vecPrimitiveComponents.begin(), m_vecPrimitiveComponents.end(), _wpPrimitiveComponent.lock()), m_vecPrimitiveComponents.end());
}

bool CCollisionManager::IntersectRectToRect(std::weak_ptr<CRectColliderComponent> _pSrc, std::weak_ptr<CRectColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectRectToCube(std::weak_ptr<CRectColliderComponent> _pSrc, std::weak_ptr<CCubeColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectRectToSphere(std::weak_ptr<CRectColliderComponent> _pSrc, std::weak_ptr<CSphereColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectCubeToRect(std::weak_ptr<CCubeColliderComponent> _pSrc, std::weak_ptr<CRectColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectCubeToCube(std::weak_ptr<CCubeColliderComponent> _pSrc, std::weak_ptr<CCubeColliderComponent> _pDst)
{
	/* 콜라이더 간의 거리가 너무 멀면 연산에서 제외합니다. -> Update쪽으로 옮겼습니다.
	 1. 두 육면체의 최대 반지름 길이를 구한다.
	 FVector3 vSrcToVertex0 = _pSrc.lock()->GetComponentWorldPosition() - _pSrc.lock()->GetVertexWorldPos(0);
	 FVector3 vDstToVertex0 = _pDst.lock()->GetComponentWorldPosition() - _pDst.lock()->GetVertexWorldPos(0);

	float fSrcRadius = D3DXVec3Length(&vSrcToVertex0);
	float fDstRadius = D3DXVec3Length(&vDstToVertex0);

	 2. 만약 최대 반지름 길이의 합보다 두 육면체 사이의 거리가 길다면 false를 반환한다.
	FVector3 vSrcToDst = _pSrc.lock()->GetComponentWorldPosition() - _pDst.lock()->GetComponentWorldPosition();

	float fSrcToDst = D3DXVec3Length(&vSrcToDst);

	if (fSrcRadius + fDstRadius < fSrcToDst)
		return false;*/

	// 두 육면체의 정점의 월드좌표를 가져옴
	// 이 정점의 월드 좌표는 액터의 월드 좌표이다.
	std::vector<FVector3> vecSrc = _pSrc.lock()->GetVecVertexWorldPos();
	std::vector<FVector3> vecDst = _pDst.lock()->GetVecVertexWorldPos();

	// 예외처리
	// CHECK(vecSrc.empty());
	// CHECK(vecDst.empty());

	// 두 육면체의 세 축 벡터를 구함
	FVector3 vSrcAxis[3] = { vecSrc[1] - vecSrc[0], vecSrc[3] - vecSrc[0], vecSrc[4] - vecSrc[0] };
	FVector3 vDstAxis[3] = { vecDst[1] - vecDst[0], vecDst[3] - vecDst[0], vecDst[4] - vecDst[0] };

	// 각 축 모서리의 절반 길이
	float fSrcEdgeHalfLength[3] = { D3DXVec3Length(&vSrcAxis[0]) / 2.f, D3DXVec3Length(&vSrcAxis[1]) / 2.f , D3DXVec3Length(&vSrcAxis[2]) / 2.f };
	float fDstEdgeHalfLength[3] = { D3DXVec3Length(&vDstAxis[0]) / 2.f, D3DXVec3Length(&vDstAxis[1]) / 2.f , D3DXVec3Length(&vDstAxis[2]) / 2.f };

	// 모두 정규화 해준다
	for (int32 i = 0; i < 3; ++i)
		D3DXVec3Normalize(&vSrcAxis[i], &vSrcAxis[i]);

	for (int32 i = 0; i < 3; ++i)
		D3DXVec3Normalize(&vDstAxis[i], &vDstAxis[i]);

	// 검산용으로 쓰일 분리축 임시변수
	FVector3 vTempSA;

	// 두 육면체의 중심간 차이 벡터
	FVector3 vCenterInterval = _pSrc.lock()->GetComponentWorldPosition() - _pDst.lock()->GetComponentWorldPosition();

	// 중심간 거리, Src육면체 분리축 반지름, Dst육면체 분리축 반지름
	float fRadius0, fRadius1, fRadius2;

	for (int32 i = 0; i < 3; ++i)
	{
		vTempSA = vSrcAxis[i];

		fRadius0 = fabs(D3DXVec3Dot(&vTempSA, &vCenterInterval));

		fRadius1 = fabs(fSrcEdgeHalfLength[0] * D3DXVec3Dot(&vTempSA, &vSrcAxis[0])) +
					fabs(fSrcEdgeHalfLength[1] * D3DXVec3Dot(&vTempSA, &vSrcAxis[1])) +
					fabs(fSrcEdgeHalfLength[2] * D3DXVec3Dot(&vTempSA, &vSrcAxis[2]));

		fRadius2 = fabs(fDstEdgeHalfLength[0] * D3DXVec3Dot(&vTempSA, &vDstAxis[0])) +
					fabs(fDstEdgeHalfLength[1] * D3DXVec3Dot(&vTempSA, &vDstAxis[1])) +
					fabs(fDstEdgeHalfLength[2] * D3DXVec3Dot(&vTempSA, &vDstAxis[2]));

		if (fRadius0 > fRadius1 + fRadius2) { return false; }
	}

	for (int32 i = 0; i < 3; ++i)
	{
		vTempSA = vDstAxis[i];

		fRadius0 = fabs(D3DXVec3Dot(&vTempSA, &vCenterInterval));

		fRadius1 = fabs(fSrcEdgeHalfLength[0] * D3DXVec3Dot(&vTempSA, &vSrcAxis[0])) +
					fabs(fSrcEdgeHalfLength[1] * D3DXVec3Dot(&vTempSA, &vSrcAxis[1])) +
					fabs(fSrcEdgeHalfLength[2] * D3DXVec3Dot(&vTempSA, &vSrcAxis[2]));

		fRadius2 = fabs(fDstEdgeHalfLength[0] * D3DXVec3Dot(&vTempSA, &vDstAxis[0])) +
					fabs(fDstEdgeHalfLength[1] * D3DXVec3Dot(&vTempSA, &vDstAxis[1])) +
					fabs(fDstEdgeHalfLength[2] * D3DXVec3Dot(&vTempSA, &vDstAxis[2]));

		if (fRadius0 > fRadius1 + fRadius2) { return false; }
	}

	return true;
}

bool CCollisionManager::IntersectCubeToSphere(std::weak_ptr<CCubeColliderComponent> _pSrc, std::weak_ptr<CSphereColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectSphereToRect(std::weak_ptr<CSphereColliderComponent> _pSrc, std::weak_ptr<CRectColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectSphereToCube(std::weak_ptr<CSphereColliderComponent> _pSrc, std::weak_ptr<CCubeColliderComponent> _pDst)
{
	return false;
}

bool CCollisionManager::IntersectSphereToSphere(std::weak_ptr<CSphereColliderComponent> _pSrc, std::weak_ptr<CSphereColliderComponent> _pDst)
{
	return false;
}

// 10.28 - 박동연 제작 -
// 광선과 충돌한 Actor를 반환합니다.
std::shared_ptr<CActor> CCollisionManager::IntersectRayToActor(FVector3 _vPos, POINT _tPoint)
{
	// 1. 광선 발사 주체의 위치를 매개변수로 받아온다.
	// POINT pt = { _lPointX , _lPointY };
	// ScreenToClient(hWnd, &pt);

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	CDeviceManager::GetInstance()->GetDirect3DDevice9()->GetViewport(&ViewPort);

	// 2. 뷰포트 -> 투영
	FVector3	vMouse;

	vMouse.x = (float)_tPoint.x / ((float)ViewPort.Width * 0.5f) - 1.f;
	vMouse.y = (float)_tPoint.y / -((float)ViewPort.Height * 0.5f) + 1.f;
	vMouse.z = 0.f;

	// 3. 투영 -> 뷰 스페이스
	FMatrix matProj;
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, 0, &matProj);
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);

	// 4. 뷰 스페이스 -> 월드
	FMatrix	matView;
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matView);

	// [ 월드에서의 마우스 - 월드에서의 광선 출발점 ]
	// FVector3	vRayPos, vRayDir;

	// vRayPos = _wpActor.lock()->GetActorPosition();
	// vRayDir = _wpActor.lock()->GetForwardVector();

	// [ 마우스 월드 좌표 - 카메라 월드 좌표 ]
	FVector3 vRayPos(_vPos), vRayDir;
	vRayDir = vMouse - vRayPos;

	D3DXVec3Normalize(&vRayDir, &vRayDir);

	// 5. Ray충돌 체크
	std::vector<std::shared_ptr<CPrimitiveComponent>> vecPrimitive = CCollisionManager::GetInstance()->GetVecPrimitiveComponent();

	float fShortestDist = 1000.0f;
	std::shared_ptr<CActor> spShortestActor;

	for (size_t i = 0; i < vecPrimitive.size(); i++)
	{
		for (int32 j = 0; j < vecPrimitive[i]->GetNumTriangles(); ++j)
		{
			int32 iIndex_0 = (int32)(vecPrimitive[i]->GetVertexIndices(j)).x;
			int32 iIndex_1 = (int32)(vecPrimitive[i]->GetVertexIndices(j)).y;
			int32 iIndex_2 = (int32)(vecPrimitive[i]->GetVertexIndices(j)).z;

			float fU(0.0f), fV(0.0f), fDist(0.0f);

			if (D3DXIntersectTri(&vecPrimitive[i]->GetVertexWorldPos(iIndex_0),
				&vecPrimitive[i]->GetVertexWorldPos(iIndex_1),
				&vecPrimitive[i]->GetVertexWorldPos(iIndex_2),
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				if (fDist < fShortestDist)
				{
					fShortestDist = fDist;
					spShortestActor = vecPrimitive[i].get()->GetOwnerActor().lock();
				}
			}
		}
	}

	if (fShortestDist == 1000.0f || spShortestActor == nullptr)
	{
		return nullptr;
	}
	else
	{
		return spShortestActor;
	}
}

std::shared_ptr<CActor> CCollisionManager::IntersectRayToCollider(FVector3 _vPos, FVector3 _vDir, std::shared_ptr<CActor> _spSrc)
{
	float fU = 0.0f, fV = 0.0f, fDist = 0.0f;
	FVector3 vRayPos = _vPos, vRayDir = _vDir;
	D3DXVec3Normalize(&vRayDir, &vRayDir);

	const std::vector<std::shared_ptr<CColliderComponent>>& vecColliderComponents = CCollisionManager::GetInstance()->GetVecColliderComponent();

	float fShortestDist = 1000.0f;
	std::shared_ptr<CActor> spShortestActor;

	for (size_t i = 0; i < vecColliderComponents.size(); i++)
	{
		for (int32 j = 0; j < vecColliderComponents[i]->GetNumTriangles(); ++j)
		{
			int32 iIndex_0 = (int32)(vecColliderComponents[i]->GetVertexIndices(j)).x;
			int32 iIndex_1 = (int32)(vecColliderComponents[i]->GetVertexIndices(j)).y;
			int32 iIndex_2 = (int32)(vecColliderComponents[i]->GetVertexIndices(j)).z;

			if (D3DXIntersectTri
			(
				&vecColliderComponents[i]->GetVertexWorldPos(iIndex_0),
				&vecColliderComponents[i]->GetVertexWorldPos(iIndex_1),
				&vecColliderComponents[i]->GetVertexWorldPos(iIndex_2),
				&vRayPos, &vRayDir, &fU, &fV, &fDist)
			)
			{
				/*
				* 몬스터도 플레이어를 시각적으로 감지했는지 광선을 발사하여 확인하기 때문에
				* 자기 자신이 감지된 경우, 무시하는 코드로 변경해야 합니다.
				*/
				// 자기 자신이 갖고 있는 콜라이더 컴포넌트인 경우, 건너뜁니다.
				if (_spSrc == vecColliderComponents[i]->GetOwnerActor().lock()) { continue; }

				if (fDist < fShortestDist)
				{
					fShortestDist = fDist;

					spShortestActor = vecColliderComponents[i].get()->GetOwnerActor().lock();

					// 11.19 광선에 맞은 위치를 액터의 콜라이더에 전해줍니다, 응용하면 관통샷도 될듯 - 동연 -
					FVector3 vRayHittedPos = vRayPos + vRayDir * fDist;
					vecColliderComponents[i]->SetRayHittedPos(vRayHittedPos);
				}
			}
		}
	}

	if (fShortestDist == 1000.0f || spShortestActor == nullptr)
	{
		return nullptr;
	}
	else
	{
		return spShortestActor;
	}
}

// 10.28 - 박동연 제작 -
// 충돌 대상을 밀어내는 함수(Src가 플레이어라는 가정하에 작성)
void CCollisionManager::BlockCubeToCube(std::weak_ptr<CCubeColliderComponent> _pSrc, std::weak_ptr<CCubeColliderComponent> _pDst, float _fRatio)
{
#pragma region 예외처리
	if (EColliderType::CUBE != _pDst.lock()->GetColliderType())
		return;
	if (EColliderType::CUBE != _pSrc.lock()->GetColliderType())
		return;

	CHECK(!_pSrc.lock()->GetOwnerActor().expired());
	CHECK(!_pDst.lock()->GetOwnerActor().expired());
#pragma endregion 예외처리

#pragma region 액터, 액터의 포지션

	std::shared_ptr<CActor> wpSrcActor = (_pSrc.lock()->GetOwnerActor().lock());
	std::shared_ptr<CActor> wpDstActor = (_pDst.lock()->GetOwnerActor().lock());

	FVector3 vSrcPosition	= wpSrcActor->GetActorPosition();
	FVector3 vDstPosition	= wpDstActor->GetActorPosition();

	float fTimeDelta = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

#pragma endregion

#pragma region 충돌체의 중심 -> 플레이어 중심 광선충돌

	// 1. 충돌 시, 충돌 방향벡터 vPushDir(Src - Dst)을 구한다.
	FVector3 vPushDir = vSrcPosition - vDstPosition;
	D3DXVec3Normalize(&vPushDir, &vPushDir);

	// 2. Dst의 중점에서 충돌 방향 벡터 방향으로 Ray를 쏴서 true를 반환하는 삼각형을 찾는다.
	FVector3 vTriPos[3] = {};
	FVector3 vNormal;
	FVector3 vNormalRemoveY = { 0.0f, 0.0f, 0.0f };
	D3DXPLANE tTriPlane;

	// float fRadian = 0.5f * D3DX_PI;

	for (int32 i = 0; i < _pDst.lock()->GetNumTriangles(); ++i)
	{
		int32 iIndex_0 = (int32)(_pDst.lock()->GetVertexIndices(i)).x;
		int32 iIndex_1 = (int32)(_pDst.lock()->GetVertexIndices(i)).y;
		int32 iIndex_2 = (int32)(_pDst.lock()->GetVertexIndices(i)).z;

		float fU(0.0f), fV(0.0f), fDist(0.0f);

		if (D3DXIntersectTri(&_pDst.lock()->GetVertexWorldPos(iIndex_0),
			&_pDst.lock()->GetVertexWorldPos(iIndex_1),
			&_pDst.lock()->GetVertexWorldPos(iIndex_2),
			&vDstPosition, &vPushDir, &fU, &fV, &fDist))
		{
			// 3. 삼각형이 찾아졌다면 삼각형의 법선벡터를 구해서 (법선벡터 - y)와 내적하여 각도를 도출한다.
			vTriPos[0] = _pDst.lock()->GetVertexWorldPos(iIndex_0);
			vTriPos[1] = _pDst.lock()->GetVertexWorldPos(iIndex_1);
			vTriPos[2] = _pDst.lock()->GetVertexWorldPos(iIndex_2);
			
			D3DXPlaneFromPoints(&tTriPlane, &vTriPos[0], &vTriPos[1], &vTriPos[2]);

			vNormal = { tTriPlane.a, tTriPlane.b, tTriPlane.c };
			vNormalRemoveY = vNormal;
			vNormalRemoveY.y -= vNormalRemoveY.y;

			D3DXVec3Normalize(&vNormal, &vNormal);
			D3DXVec3Normalize(&vNormalRemoveY, &vNormalRemoveY);

			//float fTempRadian = D3DXVec3Dot(&vNormal, &vNormalRemoveY);
			//if (fTempRadian < fRadian)
			//	fRadian = fTempRadian;
		}
	}

#pragma endregion

#pragma region 밀어냄

	// 4. 평면의 방정식에 플레이어의 x, z를 대입해서 도출된 y값까지 플레이어를 상승시킨다.

	float fPlaneX = -5001.f; // 쓰레기값을 판단하는 방법이 없어서 예외처리용으로 나올 수 없는 값인 상수를 넣어줬습니다.
	float fPlaneY = -5001.f;
	float fPlaneZ = -5001.f;
	fPlaneY = -(tTriPlane.a * vSrcPosition.x + tTriPlane.c * vSrcPosition.z + tTriPlane.d) / tTriPlane.b;
	fPlaneZ = -(tTriPlane.a * vSrcPosition.x + tTriPlane.b * vSrcPosition.y + tTriPlane.d) / tTriPlane.c;
	fPlaneX = -(tTriPlane.b * vSrcPosition.y + tTriPlane.c * vSrcPosition.z + tTriPlane.d) / tTriPlane.a;

	// 지형
	if (ECollisionLayerType::GROUND == _pDst.lock()->GetCollisionLayerType())
	{
		if (5000.0f < fabs(fPlaneY))
			return;

		// 플레이어의 중점이 평면보다 상단에 존재할 시 지형위로 올려준다.
		if (fPlaneY < vSrcPosition.y)
		{
			float fSrcScaleY = 0.5f * wpSrcActor->GetActorScale().y * _pSrc.lock()->GetComponentScale().y;

			wpSrcActor->SetActorPosition({ vSrcPosition.x , fPlaneY + (fSrcScaleY) , vSrcPosition.z });
		}
	}

	// 벽
	if (ECollisionLayerType::WALL == _pDst.lock()->GetCollisionLayerType())
	{
		if (5000.0f < fabs(fPlaneZ) && 5000.0f < fabs(fPlaneX))
			return;

		wpSrcActor->SetActorPosition(wpSrcActor->GetActorPosition() + vNormalRemoveY * _fRatio * fTimeDelta);
	}

#pragma endregion
}

void CCollisionManager::BlockSphereToSphere(std::weak_ptr<CSphereColliderComponent> _pSrc, std::weak_ptr<CSphereColliderComponent> _pDst, float _fRatio)
{
	return;
}
