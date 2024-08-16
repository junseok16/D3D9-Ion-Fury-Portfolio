#pragma once
#include "Level.h"

class CCubeColliderActor;

// 액터
class CSunActor;
class CRainParticleActor;
class CWallLaser;
class CWallBlade;
class CPlayerActor;
class CPlayerEffectActor;

// 스카이박스
class CSkyBox;

// 플레이어 무기 액터
class CElectrifryerActor;
class CLoverboyActor;
class CDisperserActor;
class CPenetratorActor;
class CChainGunActor;

// 보스 액터
class CWarmechHead;
class CWarmechLeg;
class CWarmechSmash;
class CWarmechCharge;
class CSceneChangerActor;
class CBossTrigger;

// 사용자 인터페이스 액터
class COutGameUI;
class CInGameUI;

class CStage3 : public CLevel
{
public:
	explicit CStage3() = default;
	virtual ~CStage3() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	std::weak_ptr<COutGameUI> GetOutGameUI() const { return m_wpOutGameUI; }

/********************
	Data Members
********************/
private:
	// 광원 액터
	std::weak_ptr<CSunActor> m_wpSun;

	// 파티클 액터
	std::weak_ptr<CRainParticleActor> m_wpRainParticleActor;

	// 플레이어 액터
	std::weak_ptr<CPlayerActor> m_wpPlayer;
	std::weak_ptr<CPlayerEffectActor> m_wpPlayerEffectActor;

	// 플레이어 무기 액터
	std::weak_ptr<CElectrifryerActor> m_wpElectrifryer;
	std::weak_ptr<CLoverboyActor> m_wpLoverboy;
	std::weak_ptr<CDisperserActor> m_wpDisperser;
	std::weak_ptr<CPenetratorActor> m_wpPenetrator;
	std::weak_ptr<CChainGunActor> m_wpChainGun;

	// 보스 액터
	std::weak_ptr<CWarmechHead> m_wpWarmechHead;
	std::weak_ptr<CWarmechLeg> m_wpWarmechLeg;

	std::weak_ptr<CWarmechSmash> m_wpSmash;
	// std::weak_ptr<CWarmechCharge> m_wpCharge;

	// 사용자 인터페이스 액터
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CInGameUI> m_wpInGameUI;

	// 안전하지 않은 안전 발판
	std::weak_ptr<CActor> m_wpSafeFloor[16];

	// 안전하지 않은 안전 발판 콜라이더
	// std::weak_ptr<CActor> m_wpSafeFloorCollider;

	// 레이저
	std::weak_ptr<CWallLaser> m_wpWallLasers[36];

	// 칼날
	std::weak_ptr<CWallBlade> m_wpWallBlade[8];

	// 스카이박스
	std::weak_ptr<CSkyBox> m_wpSkyBox;

	// 보스 트리거
	std::weak_ptr<CBossTrigger> m_wpBossTrigger;

	// 레벨 전환 트리거
	std::weak_ptr<CSceneChangerActor> m_wpLevelChangeTrigger;
};

