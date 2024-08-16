#pragma once
#include "WeaponActor.h"

class CSoundComponent;

class CChainGunActor : public CWeaponActor
{
public:
	explicit CChainGunActor() = default;
	virtual ~CChainGunActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	virtual void UpdateFSM() override;
	virtual void SetFrameInteract(int32 OffFire) override;				// �����ӿ� ���缭 �ѹ߸� ��� ���� �Լ�

private:
	void Input();
	void SubAccel();
	void AnimationSetting();

private:
	float	m_fAccel = 0.f;
	float	m_fDelta = 0.f;
	bool	m_bShoot = false;		// ������ ������ �� ���� ���پ��� ����
};

