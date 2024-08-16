#pragma once
#include "BTTaskNode.h"

enum class ESpawnMonsterType
{
	MECHSECT,
	DEACON,
	ENUM_END
};

class CBossSpawnMonsterTask : public CBTTaskNode
{
public:
	explicit CBossSpawnMonsterTask() = default;
	virtual ~CBossSpawnMonsterTask() = default;

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

public:
	void SetNumMonster(uint32 _iNumMonster) { m_iNumMonster = _iNumMonster; }

	void SetSpawnMonsterType(ESpawnMonsterType _eSpawnMonsterType) { m_eSpawnMonsterType = _eSpawnMonsterType; }

public:
	static int32 s_iMonsterCounter;

	// �� ���� ������ ���� ���� ��
	uint32 m_iNumMonster = 0;

	// ������ ���� Ÿ��
	ESpawnMonsterType m_eSpawnMonsterType = ESpawnMonsterType::DEACON;
};

