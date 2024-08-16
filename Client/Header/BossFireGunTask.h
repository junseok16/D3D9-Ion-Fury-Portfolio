#pragma once
#include "BTTaskNode.h"

enum class EGunFireType
{
	STRAIGHT,
	ROUND,
	ENUM_END
};

class CBossFireGunTask : public CBTTaskNode
{
public:
	explicit CBossFireGunTask() = default;
	virtual ~CBossFireGunTask() = default;

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

public:
	void SetTarget(std::wstring _wstrTargetKey) { m_wstrTargetKey = _wstrTargetKey; }

	void SetNumBullet(uint32 _iBullets) { m_iBullets = _iBullets; }

	void SetFireInterval(float _fFireInterval) { m_fSumFireInterval = m_fFireInterval = _fFireInterval; }

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void SetDamage(float _fDamage) { m_fDamage = _fDamage; }

	void SetGunFireType(EGunFireType _eGunFireType) { m_eGunFireType = _eGunFireType; }

public:
	static int32 s_iBulletCounter;

private:
	std::wstring m_wstrTargetKey = L"";

	uint32 m_iBullets = 1;// 한 번에 발사할 탄 수

	uint32 m_iSumBullets = 0;

	float m_fFireInterval = 0.1f;// 발사할 탄 사이의 시간 간격

	float m_fSumFireInterval = 0.1f;

	float m_fSpeed = 1.0f;// 탄속

	float m_fDamage = 1.0f;// 탄의 대미지

	EGunFireType m_eGunFireType = EGunFireType::STRAIGHT;// 발사 타입
};

