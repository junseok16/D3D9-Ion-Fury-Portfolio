#pragma once

class CActor;
class CColliderComponent;
class CPrimitiveComponent;
class CRectColliderComponent;
class CCubeColliderComponent;
class CSphereColliderComponent;

class CCollisionManager final
{
	DECLARE_SINGLETON(CCollisionManager)

public:
	HRESULT Initialize();
	int32 Update();
	void Release();

public:
	void AddColliderComponent(std::weak_ptr<CColliderComponent> _wpColliderComponent);
	void RemoveColliderComponent(std::weak_ptr<CColliderComponent> _wpColliderComponent);

public:
	void AddPrimitiveComponent(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent);
	void RemovePrimitiveComponent(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent);

public:
	static bool IntersectRectToRect		(std::weak_ptr<CRectColliderComponent>	_pSrc, std::weak_ptr<CRectColliderComponent>	_pDst);
	static bool IntersectRectToCube		(std::weak_ptr<CRectColliderComponent>	_pSrc, std::weak_ptr<CCubeColliderComponent>	_pDst);
	static bool IntersectRectToSphere	(std::weak_ptr<CRectColliderComponent>	_pSrc, std::weak_ptr<CSphereColliderComponent>	_pDst);

	static bool IntersectCubeToRect		(std::weak_ptr<CCubeColliderComponent>	_pSrc, std::weak_ptr<CRectColliderComponent>	_pDst);
	static bool IntersectCubeToCube		(std::weak_ptr<CCubeColliderComponent>	_pSrc, std::weak_ptr<CCubeColliderComponent>	_pDst);
	static bool IntersectCubeToSphere	(std::weak_ptr<CCubeColliderComponent>	_pSrc, std::weak_ptr<CSphereColliderComponent>	_pDst);

	static bool IntersectSphereToRect	(std::weak_ptr<CSphereColliderComponent>_pSrc, std::weak_ptr<CRectColliderComponent>	_pDst);
	static bool IntersectSphereToCube	(std::weak_ptr<CSphereColliderComponent>_pSrc, std::weak_ptr<CCubeColliderComponent>	_pDst);
	static bool IntersectSphereToSphere	(std::weak_ptr<CSphereColliderComponent>_pSrc, std::weak_ptr<CSphereColliderComponent>	_pDst);

public:
	// 10.28 - �ڵ��� ���� -
	// IntersectRayToActor(���� �߻� ��üActor, ������ ���� x��ǥ, ������ ���� y��ǥ)
	// ������ �浹�� Actor�� ��ȯ�մϴ�.
	static std::shared_ptr<CActor> IntersectRayToActor(FVector3 _vPos, POINT _tPoint);
	static std::shared_ptr<CActor> IntersectRayToCollider(FVector3 _vPos, FVector3 _vDir, std::shared_ptr<CActor> _spSrc);

public:
	static void BlockCubeToCube			(std::weak_ptr<CCubeColliderComponent>	_pSrc, std::weak_ptr<CCubeColliderComponent>	_pDst, float _fRatio);
	
	static void BlockSphereToSphere		(std::weak_ptr<CSphereColliderComponent>_pSrc, std::weak_ptr<CSphereColliderComponent>	_pDst, float _fRatio);

public:
	// 10.24 ���� �浹�� ���� �߰� - �ڵ��� -
	std::vector<std::shared_ptr<CColliderComponent>>& GetVecColliderComponent() { return m_vecColliderComponents; }

	std::vector<std::shared_ptr<CPrimitiveComponent>>& GetVecPrimitiveComponent() { return m_vecPrimitiveComponents; }

private:
	// ��� Collider ������Ʈ��
	std::vector<std::shared_ptr<CColliderComponent>> m_vecColliderComponents;

	// 10.28 ��� Primitive ������Ʈ��, �����Ϳ����� ��ŷ�� ���� �߰�
	std::vector<std::shared_ptr<CPrimitiveComponent>> m_vecPrimitiveComponents;
};
