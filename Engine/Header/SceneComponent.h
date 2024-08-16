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
	 * @brief 컴포넌트의 로컬 좌표를 저장하거나 불러옵니다.
	 */
	void SetComponentLocalPosition(const FVector3& _vTranslate) { m_vTranslate = _vTranslate; }
	const FVector3& GetComponentLocalPosition() const { return m_vTranslate; }

	/**
	 * @brief 컴포넌트의 월드 좌표를 불러옵니다.
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
	// 루트 컴포넌트 여부
	bool m_bIsRootComponent = false;

protected:
	// 컴포넌트의 크기
	FVector3 m_vScale{ 1.0f, 1.0f, 1.0f };

	// 컴포넌트의 회전
	FVector3 m_vRotate{ 0.0f, 0.0f, 0.0f };

	// 컴포넌트의 이동
	FVector3 m_vTranslate{ 0.0f, 0.0f, 0.0f };

	// 컴포넌트의 월드 좌표
	FVector3 m_vWorldPosition{ 0.0f, 0.0f, 0.0f };

	// 부모 액터 혹은 컴포넌트의 월드 행렬
	FMatrix m_matOwnerWorld{};

	// 컴포넌트의 로컬 행렬
	FMatrix	m_matLocal{};

	// 컴포넌트의 월드 행렬
	FMatrix	m_matWorld{};
};

