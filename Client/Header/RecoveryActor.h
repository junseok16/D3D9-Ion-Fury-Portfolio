#pragma once
#include "Item.h"

class CRecoveryActor : public CItem
{
public:
	explicit CRecoveryActor() = default;
	virtual ~CRecoveryActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	float		GetRecNum() { return m_fRecNum; }
	ERecoveryType	GetRecoveryType() { return m_eRecoveryType; }

protected:
	ERecoveryType m_eRecoveryType = ERecoveryType::HEALTHPACK;
	float		m_fRecNum = 0;
	float		m_fCardKey = 0;
};

