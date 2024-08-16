#pragma once
#include "Item.h"

class CBulletActor : public CItem
{
public:
	explicit CBulletActor() = default;
	virtual ~CBulletActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

protected:
	UINT		GetBulletNumber() { return m_iBulletNumber; }	// ÃÑ¾Ë °¹¼ö ¿Ã·Á¾ßÇÒ ¶§ ¸®ÅÏÇÒ ÃÑ¾Ë

protected:
	EWeaponType m_eWeaponType = EWeaponType::ELECTRIFRYER;
	UINT		m_iBulletNumber = 0;
};

