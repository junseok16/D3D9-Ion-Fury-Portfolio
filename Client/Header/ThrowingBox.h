#pragma once
#include "CubeColliderActor.h"

enum class EThrowingBoxState
{
	IDLE,
	FLOAT,
	THROW,
	RETRIEVE,
};

class CCubeMeshComponent;

class CThrowingBox : public CCubeColliderActor
{
public:
	explicit CThrowingBox() = default;
	virtual ~CThrowingBox() = default;

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
	Component
********************/
private:
	void InitializeCubeMeshComponent();

	void InitializeCubeColliderComponent();

/********************
	Callbacks
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

/********************
	Methods
********************/
	void ThrowThrowingBox(float _fDeltaSeconds);

	void FloatThrowingBox(float _fDeltaSeconds);

	void RetrieveThrowingBox();

/********************
	Getter/Setter
********************/
	void SetThrowingBoxState(EThrowingBoxState _eCurThrowingBoxState);

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void SetThrowingBoxIndex(uint32 _iThrowingboxIndex) { m_iThrowingboxIndex = _iThrowingboxIndex; }

/********************
	Data Members
********************/
private:
	std::weak_ptr<CActor> m_wpPlayer;

	std::weak_ptr<CCubeMeshComponent> m_wpCubeMeshComponent;

	std::array<std::wstring, 5> m_wstrBoxs = { L"BlueContainer0_0", L"BlueContainer1_0", L"SmallWoodBox0_0" L"Tv0_0", L"Tv1_0" };

private:
	// 박스의 상태
	EThrowingBoxState m_eCurThrowingBoxState = EThrowingBoxState::RETRIEVE;

	EThrowingBoxState m_ePrevThrowingBoxState = EThrowingBoxState::RETRIEVE;

	// 박스의 이동 속도
	float m_fSpeed = 30.0f;

	// 던지는 박스 인덱스
	uint32 m_iThrowingboxIndex = 0;
};

