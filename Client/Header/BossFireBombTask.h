#pragma once
#include "BTTaskNode.h"

enum class EBombFireType
{
	PARABOLA,// 포물선
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

	uint32 m_iBombs = 1;// 한 번에 발사할 미사일 수

	uint32 m_iSumBombs = 0;

	float m_fFireInterval = 0.1f;// 발사할 미사일 사이의 시간 간격

	float m_fSumFireInterval = 0.1f;

	float m_fSpeed = 1.0f;// 탄속

	float m_fDamage = 1.0f;// 미사일의 대미지

	EBombFireType m_eBombFireType = EBombFireType::STRAIGHT;// 발사 타입
};

