#pragma once
#include "CubeColliderActor.h"

enum class ELaserEmitterType
{
	VERTICAL,
	HORIZONTAL,
	UP_DIAGONAL,
	DOWN_DIAGONAL,
};

enum class ELaserEmitterState
{
	LASER_ON,
	LASER_OFF,
};

class CAnimationComponent;

class CLaserEmitter : public CCubeColliderActor
{
public:
	explicit CLaserEmitter() = default;
	virtual ~CLaserEmitter() = default;

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
public:
	void InitializeAnimationComponent();

	void InitializeCubeColliderComponent();

/********************
	Callbacks
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

/********************
	Getter/Setter
********************/
	void SetFloatingBox(std::shared_ptr<CActor> _spFloatingBox) { m_wpFloatingBox = _spFloatingBox; }

	void SetLaserEmitterType(ELaserEmitterType _eLaserEmitterType) { m_eLaserEmitterType = _eLaserEmitterType; }

	void SetLaserEmitterState(ELaserEmitterState _eLaserEmitterState) { m_eLaserEmitterState = _eLaserEmitterState; }

/********************
	Methods
********************/
	void UpdateEmitterPosition(float _fDeltaSeconds);

	void UpdateEmitterState();

	void UpdateEmitterAnim();

private:
	void MoveVertical(float _fDeltaSeconds);

	void MoveHorizontal(float _fDeltaSeconds);

	void MoveUpDiagonal(float _fDeltaSeconds);

	void MoveDownDiagonal(float _fDeltaSeconds);

/********************
	Data Members
********************/
private:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

private:
	// 이 레이저 분출구를 소유한 박스
	std::weak_ptr<CActor> m_wpFloatingBox;

	// 레이저 이동 속도
	float m_fSpeed = 10.0f;

	// 레이저 대미지
	float m_fDamage = 10.0f;

	// 레이저 위치
	FVector3 m_vPos = { 0.0f, 36.2f, 0.0f };

	// 레이저 이동 방향
	FVector3 m_vDir = { 0.0f, 0.0f, 0.0f };

	// 이 레이저 분출구의 상태
	ELaserEmitterState m_eLaserEmitterState = ELaserEmitterState::LASER_ON;

	// 이 레이저 분출구의 타입
	ELaserEmitterType m_eLaserEmitterType = ELaserEmitterType::VERTICAL;
};

