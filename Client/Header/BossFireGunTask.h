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

	uint32 m_iBullets = 1;// �� ���� �߻��� ź ��

	uint32 m_iSumBullets = 0;

	float m_fFireInterval = 0.1f;// �߻��� ź ������ �ð� ����

	float m_fSumFireInterval = 0.1f;

	float m_fSpeed = 1.0f;// ź��

	float m_fDamage = 1.0f;// ź�� �����

	EGunFireType m_eGunFireType = EGunFireType::STRAIGHT;// �߻� Ÿ��
};

