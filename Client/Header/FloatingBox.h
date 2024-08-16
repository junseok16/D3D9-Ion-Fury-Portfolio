#pragma once
#include "CubeColliderActor.h"

enum class EFloatingBoxState
{
	// 상승, 하강
	ASCEND,
	ASCENDING,
	DESCEND,
	DESCENDING,

	// 분리, 결합
	SEPARATE,
	SEPARATING,
	COMBINE,
	COMBINING,

	// 화염 레이저
	FLAME_ON,
	FLAME_OFF,
	LASER_ON,
	LASER_OFF,
};

class CCubeMeshComponent;
class CFlameEmitter;
class CLaserEmitter;

class CFloatingBox : public CCubeColliderActor
{
public:
	explicit CFloatingBox() = default;
	virtual ~CFloatingBox() = default;

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
	Methods
********************/
	void UpdateFloatingBoxState(float _fDeltaSeconds);

/********************
	Getter/Setter
********************/
public:
	void SetFloatingBoxState(EFloatingBoxState _eFloatingBoxState);

	void SetFloatingBoxIndex(int32 _iFloatingBoxIndex) { m_iFloatingBoxIndex = _iFloatingBoxIndex; }

	EFloatingBoxState GetFloatingBoxState() const { return m_eCurFloatingBoxState; }

/********************
	Callbacks
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

/********************
	Data Members
********************/
private:
	std::weak_ptr<CCubeMeshComponent> m_wpCubeMeshComponent;

	std::weak_ptr<CFlameEmitter> m_wpFlameEmitter[2][2];

	std::weak_ptr<CLaserEmitter> m_wpLaserEmitter[4];

	EFloatingBoxState m_eCurFloatingBoxState = EFloatingBoxState::ASCEND;

	EFloatingBoxState m_ePrevFloatingBoxState = EFloatingBoxState::ASCEND;

	float m_fSpeed = 20.0f;

	int32 m_iFloatingBoxIndex = 0;

	FVector3 m_vSeparatingDir = { 1.0f, 0.0f, 0.0f };

	FVector3 m_vCombiningDir = { 1.0f, 0.0f, 0.0f };
};

