#pragma once
#include "ActorComponent.h"

class CSceneComponent : public CActorComponent
{
public:
	explicit CSceneComponent() = default;
	virtual ~CSceneComponent() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

/********************
	Getter/Setter
********************/
public:
	/**
	 * @brief ������Ʈ�� ���� ��ǥ�� �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetComponentLocalPosition(const FVector3& _vTranslate) { m_vTranslate = _vTranslate; }
	const FVector3& GetComponentLocalPosition() const { return m_vTranslate; }

	/**
	 * @brief ������Ʈ�� ���� ��ǥ�� �ҷ��ɴϴ�.
	 */
	void SetComponentWorldPosition(const FVector3& _vWorld) { m_vWorldPosition = _vWorld; }
	const FVector3& GetComponentWorldPosition() const { return m_vWorldPosition; }

	void SetComponentRotation(const FVector3& _vRotate) { m_vRotate = _vRotate; }
	const FVector3& GetComponentRotation() const { return m_vRotate; }

	void SetComponentScale(const FVector3& _vScale) { m_vScale = _vScale; }
	const FVector3& GetComponentScale() const { return m_vScale; }

	void SetIsRootComponent(bool _bIsRootComponent) { m_bIsRootComponent = _bIsRootComponent; }
	bool GetIsRootComponent() const { return m_bIsRootComponent; }

public:
	const FMatrix& GetWorldMatrix() const { return m_matWorld; }
	void SetWorldMatrix(const FMatrix& _matWorld) { m_matWorld = _matWorld; }

	// FVector3 GetForwardVector() const;
	// 
	// FVector3 GetRightVector() const;
	// 
	// FVector3 GetUpVector() const;

/********************
	Methods
********************/
private:
	void UpdateSceneComponentTransform();

/********************
	Data Members
********************/
private:
	// ��Ʈ ������Ʈ ����
	bool m_bIsRootComponent = false;

protected:
	// ������Ʈ�� ũ��
	FVector3 m_vScale{ 1.0f, 1.0f, 1.0f };

	// ������Ʈ�� ȸ��
	FVector3 m_vRotate{ 0.0f, 0.0f, 0.0f };

	// ������Ʈ�� �̵�
	FVector3 m_vTranslate{ 0.0f, 0.0f, 0.0f };

	// ������Ʈ�� ���� ��ǥ
	FVector3 m_vWorldPosition{ 0.0f, 0.0f, 0.0f };

	// �θ� ���� Ȥ�� ������Ʈ�� ���� ���
	FMatrix m_matOwnerWorld{};

	// ������Ʈ�� ���� ���
	FMatrix	m_matLocal{};

	// ������Ʈ�� ���� ���
	FMatrix	m_matWorld{};
};

