#pragma once
#include "CubeColliderActor.h"

enum class EFlameEmitterState
{
	FLAME_ON,
	FLAME_OFF
};

class CAnimationComponent;
class CRectangleMeshComponent;
class CActor;

class CFlameEmitter : public CCubeColliderActor
{
public:
	explicit CFlameEmitter() = default;
	virtual ~CFlameEmitter() = default;

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
	void InitializeRectMeshComponent();

	void InitializeAnimationComponent();

	void InitializeCubeColliderComponent();

/********************
	Callbacks
********************/
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

/********************
	Getter/Setter
********************/
	void SetFloatingBox(std::shared_ptr<CActor> _spFloatingBox) { m_wpFloatingBox = _spFloatingBox; }

	void SetEmitterIndex(int32 _iEmitterIndex) { m_iEmitterIndex = _iEmitterIndex; }

	void SetFlameEmitterState(EFlameEmitterState _eFlameEmitterState) { m_eFlameEmitterState = _eFlameEmitterState; }

/********************
	Methods
********************/
	void UpdateEmitterPosition();

	void UpdateEmitterState();

	void UpdateEmitterAnim();

/********************
	Data Members
********************/
private:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

	std::weak_ptr<CRectangleMeshComponent> m_wpRectMeshComponent;
	
private:
	// 이 화염 분출구를 소유한 박스
	std::weak_ptr<CActor> m_wpFloatingBox;

	// 화염 대미지
	float m_fDamage = 10.0f;

	// 화염 분출 시간
	float m_fEmitTime = 0.0f;

	// 총 화염 분출 시간
	float m_fSumEmitTime = 0.0f;

	// 이 화염 분출구의 인덱스(0 ~ 3)
	int32 m_iEmitterIndex = 0;

	// 이 화염 분출구의 상태
	EFlameEmitterState m_eFlameEmitterState = EFlameEmitterState::FLAME_OFF;
};

