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
	// �޽��� �� ������
	LPD3DXMESH m_pMesh = nullptr;

	// �÷� ���ؽ� ��ǥ
	std::vector<ColorVertex> m_vecColorVertices;

	// �÷� �ε��� ����
	std::vector<ColorIndex> m_vecColorIndices;

	// �ݶ��̴� Ÿ��(���, ��, ������ü)
	EColliderType m_eColliderType = EColliderType::ENUM_END;

	// �ݸ��� ���̾�(�� �ݶ��̴� ������Ʈ�� �浹�ؾ� �� �ٸ� �ݶ��̴� ������Ʈ��)
	uint32 m_iCollisionLayer = 0x0000'0000;

	// �ݸ��� ���̾� Ÿ��
	ECollisionLayerType m_eCollisionLayerType = ECollisionLayerType::ENUM_END;

	// �� �ݶ��̴� ������Ʈ�� �浹�� �ٸ� �ݶ��̴� ������Ʈ��
	std::unordered_set<std::shared_ptr<CColliderComponent>> m_usetColliderComponents;

	// 11.19 (�ӽ�) ������ �浹���� ��, ��ġ ���� -> �÷��̾� �ѿ� ���� ���� ����Ʈ, ��ƼŬ ���� �����ϱ� ���� - ���� -
	FVector3 m_vRayHittedPos = { 0.0f, 0.0f, 0.0f };
};

