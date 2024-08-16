#pragma once
#include "Actor.h"

class CPlayerActor;
class CAnimationComponent;
class CParticleComponent;
class CSoundComponent;

class CWeaponActor : public CActor
{
public:
	explicit CWeaponActor() = default;
	virtual ~CWeaponActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	virtual void UpdateFSM();

	void SynchronizationVector();
	virtual void SetFrameInteract(int32 OffFire) {};				// �����ӿ� ���缭 �ѹ��� �����ϱ� ���� �Լ�
public:
	std::weak_ptr<CAnimationComponent>& GetAnimationComponent() { return m_wpAnimationComponent; }
	
	void SetBulletHolding(int32 iBulletNum);	// �������� iBulletNum��ŭ ���ϱ�
	void SetIsEnable(bool _bIsEnable) { m_bEnable = _bIsEnable; }
	void SetActivate(bool _bActivate) { m_bActivate = _bActivate; }

	bool GetActivate() { return m_bActivate; }
	float GetDamage() { return m_iDamage; }
	int32 GetBulletLoaded() { return m_iBulletLoaded; }
	int32 GetBulletHolding() { return m_iBulletHolding; }
	int32 GetMagazine() { return m_iMagazine; }
	int32 GetCurBullet() { return m_iBulletLoaded + m_iBulletHolding; }

	void SetSavedBulletHolding(int32 _iBulletHolding) { m_iBulletHolding = _iBulletHolding; }
	void SetSavedBulletLoaded(int32 _iBulletLoaded) { m_iBulletLoaded = _iBulletLoaded; }
	
	EWeaponType GetWeaponType() { return m_eWeaponType; }
public:
	void Reload();

protected:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;
	std::weak_ptr<CParticleComponent> m_wpParticleComponent;

	EWeaponType	m_eWeaponType		= EWeaponType::ELECTRIFRYER;
	FVector3	m_vBasePosition = { 100.0f, -150.f, 5.0f };

	int32		m_iBulletHolding = 0;	// ź ������
	int32		m_iBulletLoaded = 0;	// ������ ź
	int32		m_iBulletMaximum = 0;	// �ִ� ź
	int32		m_iMagazine = 0;		// źâ �뷮

	float		m_iDamage = 0.f;			// ������

	bool		m_bEnable = false;		// �� Ȱ��ȭ
	bool		m_bActivate = true;
	bool		m_bFrameButton = true;			// �����ӿ� ���缭 �ѹ��� �����ϱ� ���� ����
};
