#pragma once
#include "Level.h"

// actor
class CSunActor;
class CPlayerActor;
class CSkinjob;

class CAcidWater;
class CFloatingBox;
class CThrowingBox;

// weapon
class CElectrifryerActor;
class CLoverboyActor;
class CDisperserActor;
class CPenetratorActor;
class CChainGunActor;

// effect
class CPlayerEffectActor;

// UI
class COutGameUI;
class CInGameUI;

class CStage4 : public CLevel
{
public:
	explicit CStage4() = default;
	virtual ~CStage4() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	// 광원 액터
	std::weak_ptr<CSunActor> m_wpSun;

	// 플레이어 액터
	std::weak_ptr<CPlayerActor> m_wpPlayer;

	// 플레이어 무기 액터
	std::weak_ptr<CPlayerEffectActor> m_wpPlayerEffectActor;
	std::weak_ptr<CElectrifryerActor> m_wpElectrifryer;
	std::weak_ptr<CLoverboyActor> m_wpLoverboy;
	std::weak_ptr<CDisperserActor> m_wpDisperser;
	std::weak_ptr<CPenetratorActor> m_wpPenetrator;
	std::weak_ptr<CChainGunActor> m_wpChainGun;

	// 보스 액터
	std::weak_ptr<CSkinjob> m_wpSkinjob;

	// 사용자 인터페이스 액터
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CInGameUI> m_wpInGameUI;

private:
	// 랜덤 박스
	std::weak_ptr<CThrowingBox> m_wpThrowingBox[6];

	// 3 x 3 발판
	std::weak_ptr<CFloatingBox> m_wpFloatingBox[3][3];

	// 산성 물
	std::weak_ptr<CAcidWater> m_wpAcidWater[9][9];
};

