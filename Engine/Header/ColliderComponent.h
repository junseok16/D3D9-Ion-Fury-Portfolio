#pragma once
#include "PrimitiveComponent.h"

class CColliderComponent : public CPrimitiveComponent
{
public:
	explicit CColliderComponent() = default;
	virtual ~CColliderComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

/********************
	Methods
********************/
private:
	virtual void CreateVertices() override;

	virtual void CreateIndices() override;

public:
	virtual bool IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent);

	virtual bool IsCollisionLayerOverlapped(std::weak_ptr<CColliderComponent> _wpColliderComponent);

	void ResetCollisionLayer() { m_iCollisionLayer = 0x0000'0000; }

	void AddCollisionLayer(ECollisionLayerType _eCollisionLayerType);
	
	void RemoveCollisionLayer(ECollisionLayerType _eCollisionLayerType);

/*******************
	Getter/Setter
*******************/
public:
	void SetCollisionLayer(uint32 _iCollisionLayer) { m_iCollisionLayer = _iCollisionLayer; }
	uint32 GetCollisionLayer() const { return m_iCollisionLayer; }

	void SetCollisionLayerType(ECollisionLayerType _eCollisionLayerType) { m_eCollisionLayerType = _eCollisionLayerType; }
	ECollisionLayerType GetCollisionLayerType() const { return m_eCollisionLayerType; }

	void SetColliderType(EColliderType _eColliderType) { m_eColliderType = _eColliderType; }
	EColliderType GetColliderType() const { return m_eColliderType; }

	void SetRayHittedPos(const FVector3& _vRayHittedPos) { m_vRayHittedPos = _vRayHittedPos; }
	const FVector3& GetRayHittedPos() { return m_vRayHittedPos; }

	std::unordered_set<std::shared_ptr<CColliderComponent>>& GetColliderComponents() { return m_usetColliderComponents; }

/*******************
	Data Members
*******************/
protected:
	// 메시의 컴 포인터
	LPD3DXMESH m_pMesh = nullptr;

	// 컬러 버텍스 좌표
	std::vector<ColorVertex> m_vecColorVertices;

	// 컬러 인덱스 순서
	std::vector<ColorIndex> m_vecColorIndices;

	// 콜라이더 타입(평면, 구, 직육면체)
	EColliderType m_eColliderType = EColliderType::ENUM_END;

	// 콜리전 레이어(이 콜라이더 컴포넌트와 충돌해야 할 다른 콜라이더 컴포넌트들)
	uint32 m_iCollisionLayer = 0x0000'0000;

	// 콜리전 레이어 타입
	ECollisionLayerType m_eCollisionLayerType = ECollisionLayerType::ENUM_END;

	// 이 콜라이더 컴포넌트와 충돌한 다른 콜라이더 컴포넌트들
	std::unordered_set<std::shared_ptr<CColliderComponent>> m_usetColliderComponents;

	// 11.19 (임시) 광선에 충돌했을 시, 위치 벡터 -> 플레이어 총에 맞은 곳에 이펙트, 파티클 등을 생성하기 위해 - 동연 -
	FVector3 m_vRayHittedPos = { 0.0f, 0.0f, 0.0f };
};

