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
	// �� ������ ���ⱸ�� ������ �ڽ�
	std::weak_ptr<CActor> m_wpFloatingBox;

	// ������ �̵� �ӵ�
	float m_fSpeed = 10.0f;

	// ������ �����
	float m_fDamage = 10.0f;

	// ������ ��ġ
	FVector3 m_vPos = { 0.0f, 36.2f, 0.0f };

	// ������ �̵� ����
	FVector3 m_vDir = { 0.0f, 0.0f, 0.0f };

	// �� ������ ���ⱸ�� ����
	ELaserEmitterState m_eLaserEmitterState = ELaserEmitterState::LASER_ON;

	// �� ������ ���ⱸ�� Ÿ��
	ELaserEmitterType m_eLaserEmitterType = ELaserEmitterType::VERTICAL;
};

