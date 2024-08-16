#pragma once
#include "BTTaskNode.h"

enum class EBombFireType
{
	PARABOLA,// ������
	STRAIGHT,
	ENUM_END
};

class CBossFireBombTask : public CBTTaskNode
{
public:
	explicit CBossFireBombTask() = default;
	virtual ~CBossFireBombTask() = default;

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

public:
	void SetTarget(std::wstring _wstrTargetKey) { m_wstrTargetKey = _wstrTargetKey; }

	void SetNumBomb(uint32 _iBombs) { m_iBombs = _iBombs; }

	void SetFireInterval(float _fFireInterval) { m_fFireInterval = _fFireInterval; }

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void SetDamage(float _fDamage) { m_fDamage = _fDamage; }

	void SetBombFireType(EBombFireType _eBombFireType) { m_eBombFireType = _eBombFireType; }

public:
	static int32 s_iBombCounter;

private:
	std::wstring m_wstrTargetKey = L"";

	uint32 m_iBombs = 1;// �� ���� �߻��� �̻��� ��

	uint32 m_iSumBombs = 0;

	float m_fFireInterval = 0.1f;// �߻��� �̻��� ������ �ð� ����

	float m_fSumFireInterval = 0.1f;

	float m_fSpeed = 1.0f;// ź��

	float m_fDamage = 1.0f;// �̻����� �����

	EBombFireType m_eBombFireType = EBombFireType::STRAIGHT;// �߻� Ÿ��
};

