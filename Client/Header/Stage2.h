#pragma once
#include "Level.h"

class CSoundComponent;
class CSunActor;
class CPlayerActor;
class CPlayerEffectActor;
// class CPlayerParticleActor;

class CElectrifryerActor;
class CLoverboyActor;
class CLoverboyLHActor;
class CDisperserActor;
class CPenetratorActor;
class CChainGunActor;

class CDisperserItemActor;
class CPenetratorItemActor;
class CChainGunItemActor;

class CLoverboyBulletActor;
class CHealthPackActor;
class CSyringeActor;
class CArmorActor;
class CArmorPieceActor;

class CGarbageActor;
class CTrashCanActor;

// 신 체인저
class CSceneChangerActor;

class CMechsect;
class CCultist;
class CPustule;
class CDeacon;

// 동준
class COutGameUI;
class CInGameUI;
class CLeverBox;
class CLeverGate;
class CCardKeyBox;
class CCardKeyGate;
class CElevatorBox;
class CElevatorRightGate;
class CPowerMonitor;
class CCardKeyActor;
///////////////////////

class CStage2 : public CLevel
{
public:
	explicit CStage2() = default;
	virtual ~CStage2() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;
	std::weak_ptr<CSunActor> m_wpSunActor;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CPlayerEffectActor> m_wpPlayerEffectActor;
	// std::weak_ptr<CPlayerParticleActor> m_wpPlayerParticleActor;

	// weapon
	std::weak_ptr<CElectrifryerActor> m_wpElectrifryerActor;
	std::weak_ptr<CLoverboyActor> m_wpLoverboyActor;
	std::weak_ptr<CLoverboyLHActor> m_wpLoverboyLHActor;
	std::weak_ptr<CDisperserActor> m_wpDisperserActor;
	std::weak_ptr<CPenetratorActor> m_wpPenetratorActor;
	std::weak_ptr<CChainGunActor> m_wpChainGunActor;

	std::weak_ptr<CDisperserItemActor> m_wpDisperserItemActor;
	std::weak_ptr<CPenetratorItemActor> m_wpPenetratorItemActor;
	std::weak_ptr<CChainGunItemActor> m_wpChainGunItemActor;

	std::weak_ptr<CLoverboyBulletActor> m_wpLoverboyBulletActor;
	std::weak_ptr<CHealthPackActor> m_wpHealthPackActor;
	std::weak_ptr<CSyringeActor> m_wpSyringeActor;
	std::weak_ptr<CArmorActor> m_wpArmorActor;
	std::weak_ptr<CArmorPieceActor> m_wpArmorPieceActor;

	// monster
	std::weak_ptr<CMechsect> m_wpMechsect;
	std::weak_ptr<CCultist> m_wpCultist;
	std::weak_ptr<CPustule> m_wpPustule;
	std::weak_ptr<CDeacon> m_wpDeacon;

	// item object
	std::weak_ptr<CGarbageActor> m_wpGarbage;
	std::weak_ptr<CTrashCanActor> m_wpTrashCan;

	// scene change trigger collider
	std::weak_ptr<CSceneChangerActor> m_wpSceneChanger;

	///// 동준 
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CInGameUI> m_wpInGameUI;
	std::weak_ptr<CLeverBox> m_wpLeverBox;
	std::weak_ptr<CLeverGate> m_wpLeverGate;
	std::weak_ptr<CCardKeyBox> m_wpCardKeyBox;
	std::weak_ptr<CCardKeyGate> m_wpCardKeyGate;
	std::weak_ptr<CElevatorBox> m_wpElevatorBox;
	std::weak_ptr<CElevatorRightGate> m_wpElevatorRightGate;

	std::weak_ptr<CCardKeyActor> m_wpCardKeyActor;
	std::weak_ptr<CPowerMonitor> m_wpPowerMonitor;
	//std::weak_ptr<CElevatorLeftGate> m_wpElevatorLeftGate;
};
