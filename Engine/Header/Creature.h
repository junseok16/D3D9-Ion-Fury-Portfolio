#pragma once
#include "CubeColliderActor.h"

class CAnimationComponent;
class CPhysicsComponent;
class CEffectComponent;
class CParticleComponent;
class CSoundComponent;

/**
 * @brief	크리처 클래스입니다.
 * @details 크리처 클래스
 * @author	박동연
 * @date	2023-10-30
 */
class CCreature : public CCubeColliderActor
{
public:
	explicit CCreature() = default;
	virtual ~CCreature() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize();
	virtual void BeginPlay();
	virtual int32 Update(const float& _fDeltaSeconds);
	virtual int32 LateUpdate(const float& _fDeltaSeconds);
	virtual void Render();
	virtual void EndPlay();
	virtual void Release();

/********************
	Methods
********************/
public:
	virtual void AnimationSetting();
	virtual void ColliderSetting();
	virtual void PhysicsSetting();
	virtual void ParticleSetting();
	virtual void SoundSetting();

public:
	virtual void GetDamaged(const float& _fDamage);

	virtual int32 DeadCheck(const float& _fDeltaSeconds);

/********************
	Getter/Setter
********************/
public:
	void	SetIsCollided(bool _bIsCollided) { m_bIsCollided = _bIsCollided; }
	bool	GetIsCollided() { return m_bIsCollided; }

	void	SetIsOnAir(bool _bIsOnAir) { m_bIsOnAir = _bIsOnAir; }
	bool	GetIsOnAir() { return m_bIsOnAir; }

public:
	std::weak_ptr<CAnimationComponent> GetAnimationComponent() const { CHECK(!m_wpAnimationComponent.expired()); return m_wpAnimationComponent; }
	std::weak_ptr<CCubeColliderComponent> GetCubeColliderComponent() const { CHECK(!m_wpCubeColliderComponent.expired()); return m_wpCubeColliderComponent; }
	std::weak_ptr<CPhysicsComponent> GetPhysicsComponent() const { CHECK(!m_wpPhysicsComponent.expired()); return m_wpPhysicsComponent; }
	std::weak_ptr<CSoundComponent> GetSoundComponent() const { CHECK(!m_wpSoundComponent.expired()); return m_wpSoundComponent; }
public:
	// 김병조
	// 체력
	void SetCurHp(float _fHp) { m_fCurHp = _fHp; }
	float GetCurHp() const { return m_fCurHp; }
	void SetCurHpPlus(float _fHp) { m_fCurHp += _fHp; }
	void SetCurHpMinus(float _fHp) { m_fCurHp -= _fHp; }
	void SetCurHpMax() { m_fCurHp = m_fMaxHp; }

	// 최대 체력
	void SetMaxHp(const float& _fMaxHp) { m_fMaxHp = _fMaxHp; }
	float GetMaxHp() const { return m_fMaxHp; }

	// 방어구
	void SetCurArmor(float _fArmor) { m_fCurArmor = _fArmor; }
	float GetCurArmor() const { return m_fCurArmor; }
	void SetCurArmorPlus(float _fArmor) { m_fCurArmor += _fArmor; }
	void SetMaxArmor(float _fArmor) { m_fMaxArmor = _fArmor; }
	float GetMaxArmor() const { return m_fMaxArmor; }

	// 이동 속도
	void SetSpeed(const float& _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() const { return m_fSpeed; }

	// 점프 속도
	void SetJumpSpeed(const float& _fJumpSpeed) { m_fJumpSpeed = _fJumpSpeed; }
	const float& GetJumpSpeed() { return m_fJumpSpeed; }

/********************
	Data Members
********************/
protected:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;
	std::weak_ptr<CPhysicsComponent> m_wpPhysicsComponent;
	std::weak_ptr<CEffectComponent> m_wpEffectComponent;
	std::weak_ptr<CParticleComponent> m_wpParticleComponent;
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;

	std::wstring m_wstrAnimationState;// 현재 애니메이션 상태

	// 스테이터스
	float		m_fCurHp = 100.0f;		// 현재 Hp
	float		m_fMaxHp = 100.0f;		// 최대 Hp
	float		m_fCurArmor = 100.0f;	// 현재 Armor
	float		m_fMaxArmor = 150.0f;	// 최대 Armor

	float		m_fSpeed = 15.0f;		// 이동 속도
	float		m_fJumpSpeed = 50.0f;	// 점프 속도

	float		m_fJumpTime = 0.0f;

	float		m_fDeadTime = 0.0f;		// 죽고나서 사라지기까지의 시간

	// 물리
	bool m_bIsCollided = false;		// 충돌 중일 때 참
	bool m_bIsOnAir = false;		// 공중에 있을 때 참
	bool m_bIsMove = false;			// 이동 중일 때 참
};

