#pragma once
#include "Item.h"

class CWeaponItemActor : public CItem
{
public:
	explicit CWeaponItemActor() = default;
	virtual ~CWeaponItemActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

protected:
	EWeaponType m_eWeaponType = EWeaponType::ELECTRIFRYER;
};