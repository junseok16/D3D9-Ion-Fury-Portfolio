#pragma once
#include "Item.h"

class CLoverboyBulletActor;
class CDisperserBulletActor;
class CPenetratorBulletActor;
class CChainGunBulletActor;

class CHealthPackActor;
class CSyringeActor;
class CArmorActor;
class CArmorPieceActor;

class CItemObjectActor : public CItem
{
public:
	explicit CItemObjectActor() = default;
	virtual ~CItemObjectActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void CreateItem(int32 iCapaType);
	void GetDamaged() { m_iHp -= 1; }
	void SetCapaType(int32 _iCapaType) { m_iCapaType = _iCapaType; }
	void SetWeaponType(EWeaponType _eWeaponType) { m_eWeaponType = _eWeaponType; }
	void SetRecoveryType(ERecoveryType _eRecoveryType) { m_eRecoveryType = _eRecoveryType; }
	void SetSkillType(ESkillType _eSkillType) { m_eSkillType = _eSkillType; }

protected:
	std::weak_ptr<CLoverboyBulletActor> m_wpLoverboyBulletActor;
	std::weak_ptr<CDisperserBulletActor> m_wpDisperserBulletActor;
	std::weak_ptr<CPenetratorBulletActor> m_wpPenetratorBulletActor;
	std::weak_ptr<CChainGunBulletActor> m_wpChainGunBulletActor;

	std::weak_ptr<CHealthPackActor> m_wpCHealthPackActor;
	std::weak_ptr<CSyringeActor> m_wpSyringeActor;
	std::weak_ptr<CArmorActor> m_wpArmorActor;
	std::weak_ptr<CArmorPieceActor> m_wpArmorPieceActor;

	EWeaponType m_eWeaponType = EWeaponType::ENUM_END;
	ERecoveryType m_eRecoveryType = ERecoveryType::ENUM_END;
	ESkillType m_eSkillType = ESkillType::ENUM_END;

	int32 m_iHp = 0;
	int32 m_iCapaType = 0;
	bool m_bConsumed = false;
public:
	static uint32 s_iItemIndex;
};

