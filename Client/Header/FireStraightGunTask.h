#pragma once
#include "BTTaskNode.h"

class CFireStraightGunTask : public CBTTaskNode
{
public:
	explicit CFireStraightGunTask() = default;
	virtual ~CFireStraightGunTask() = default;

public:
	void SetTarget(std::wstring _wstrKey) { m_wstrKey = _wstrKey; }
	void SetNumBullet(uint32 _iBullets) { m_iBullets = _iBullets; }
	void SetFireInterval(float _fFireInterval) { m_fFireInterval = _fFireInterval; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetDamage(float _fDamage) { m_fDamage = _fDamage; }

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

private:
	std::wstring m_wstrKey = L"";

	uint32 m_iBullets = 1;

	uint32 m_iSumBullets = 0;

	float m_fFireInterval = 0.1f;

	float m_fSumFireInterval = 0.1f;

	float m_fSpeed = 1.0f;

	float m_fDamage = 1.0f;
};

