#pragma once
#include "Item.h"

class CSkillActor : public CItem
{
public:
	explicit CSkillActor() = default;
	virtual ~CSkillActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	ESkillType	GetSkillType() { return m_eSkillType; }
	int32 GetSkillNum() { return m_iSkillNum; }

protected:
	ESkillType	m_eSkillType = ESkillType::MEDKIT;
	int32		m_iSkillNum = 0;
};

