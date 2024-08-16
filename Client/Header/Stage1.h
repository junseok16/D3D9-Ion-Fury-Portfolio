#pragma once
#include "Level.h"

class CSkyBox;
class CSunActor;
class CArmorActor;
class CPlayerActor;
class CSyringeActor;
class CGarbageActor;
class CLoverboyActor;
class CTrashCanActor;
class CChainGunActor;
class CDisperserActor;
class CLoverboyLHActor;
class CArmorPieceActor;
class CPenetratorActor;
class CHealthPackActor;
class CElectrifryerActor;
class CPlayerEffectActor;
class CChainGunItemActor;
class CDisperserItemActor;
class CPlayerParticleActor;
class CPenetratorItemActor;
class CLoverboyBulletActor;

// 신 체인저
class CSceneChangerActor;

class CDeacon;
class CCultist;
class CPustule;
class CMechsect;

// 동준
class CInGameUI;
class COutGameUI;

class CFinalGate;
class CLeverGate;
class CCardKeyGate;
class CElevatorFloor;

class CLeverBox;
class CCardKeyBox;
class CPowerMonitor;
class CFinalGateBox;
class CPowerMonitor1;
class CElevatorKeyBox;
class CElevatorKeyBox1;
class CCardKeyActor;

class CStage1 : public CLevel
{
public:
	explicit CStage1() = default;
	virtual ~CStage1() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	// player
	std::weak_ptr<CSunActor> m_wpSunActor;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CPlayerEffectActor> m_wpPlayerEffectActor;

	// weapon
	std::weak_ptr<CChainGunActor> m_wpChainGunActor;
	std::weak_ptr<CLoverboyActor> m_wpLoverboyActor;
	std::weak_ptr<CDisperserActor> m_wpDisperserActor;
	std::weak_ptr<CPenetratorActor> m_wpPenetratorActor;
	std::weak_ptr<CLoverboyLHActor> m_wpLoverboyLHActor;
	std::weak_ptr<CElectrifryerActor> m_wpElectrifryerActor;

	std::weak_ptr<CChainGunItemActor> m_wpChainGunItemActor;
	std::weak_ptr<CDisperserItemActor> m_wpDisperserItemActor;
	std::weak_ptr<CPenetratorItemActor> m_wpPenetratorItemActor;

	std::weak_ptr<CArmorActor> m_wpArmorActor;
	std::weak_ptr<CSyringeActor> m_wpSyringeActor;
	std::weak_ptr<CHealthPackActor> m_wpHealthPackActor;
	std::weak_ptr<CArmorPieceActor> m_wpArmorPieceActor;
	std::weak_ptr<CLoverboyBulletActor> m_wpLoverboyBulletActor;

	// monster
	std::weak_ptr<CDeacon> m_wpDeacon;
	std::weak_ptr<CPustule> m_wpPustule;
	std::weak_ptr<CCultist> m_wpCultist;
	std::weak_ptr<CMechsect> m_wpMechsect;

	// item object
	std::weak_ptr<CGarbageActor> m_wpGarbage;
	std::weak_ptr<CTrashCanActor> m_wpTrashCan;

	// scene change trigger collider
	std::weak_ptr<CSceneChangerActor> m_wpSceneChanger;

	///// 동준 
	std::weak_ptr<CSkyBox> m_wpSkyBox;
	std::weak_ptr<CInGameUI> m_wpInGameUI;
	std::weak_ptr<CLeverBox> m_wpLeverBox;
	std::weak_ptr<CFinalGate> m_wpFinalGate;
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CLeverGate> m_wpLeverGate;
	std::weak_ptr<CCardKeyBox> m_wpCardKeyBox;
	std::weak_ptr<CCardKeyGate> m_wpCardKeyGate;
	std::weak_ptr<CFinalGateBox> m_wpFinalGateBox;
	std::weak_ptr<CPowerMonitor> m_wpPowerMonitor;
	std::weak_ptr<CPowerMonitor1> m_wpPowerMonitor1;
	std::weak_ptr<CElevatorFloor> m_wpElevatorFloor;

	std::weak_ptr<CElevatorKeyBox> m_wpElevatorKeyBox;
	std::weak_ptr<CElevatorKeyBox1> m_wpElevatorKeyBox1;

	std::weak_ptr<CCardKeyActor> m_wpCardKeyActor;
	//std::weak_ptr<CElevatorLeftGate> m_wpElevatorLeftGate;
};
