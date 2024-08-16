#pragma once
#include "Level.h"

class CCubeColliderActor;

// ����
class CSunActor;
class CRainParticleActor;
class CWallLaser;
class CWallBlade;
class CPlayerActor;
class CPlayerEffectActor;

// ��ī�̹ڽ�
class CSkyBox;

// �÷��̾� ���� ����
class CElectrifryerActor;
class CLoverboyActor;
class CDisperserActor;
class CPenetratorActor;
class CChainGunActor;

// ���� ����
class CWarmechHead;
class CWarmechLeg;
class CWarmechSmash;
class CWarmechCharge;
class CSceneChangerActor;
class CBossTrigger;

// ����� �������̽� ����
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
	// ���� ����
	std::weak_ptr<CSunActor> m_wpSun;

	// ��ƼŬ ����
	std::weak_ptr<CRainParticleActor> m_wpRainParticleActor;

	// �÷��̾� ����
	std::weak_ptr<CPlayerActor> m_wpPlayer;
	std::weak_ptr<CPlayerEffectActor> m_wpPlayerEffectActor;

	// �÷��̾� ���� ����
	std::weak_ptr<CElectrifryerActor> m_wpElectrifryer;
	std::weak_ptr<CLoverboyActor> m_wpLoverboy;
	std::weak_ptr<CDisperserActor> m_wpDisperser;
	std::weak_ptr<CPenetratorActor> m_wpPenetrator;
	std::weak_ptr<CChainGunActor> m_wpChainGun;

	// ���� ����
	std::weak_ptr<CWarmechHead> m_wpWarmechHead;
	std::weak_ptr<CWarmechLeg> m_wpWarmechLeg;

	std::weak_ptr<CWarmechSmash> m_wpSmash;
	// std::weak_ptr<CWarmechCharge> m_wpCharge;

	// ����� �������̽� ����
	std::weak_ptr<COutGameUI> m_wpOutGameUI;
	std::weak_ptr<CInGameUI> m_wpInGameUI;

	// �������� ���� ���� ����
	std::weak_ptr<CActor> m_wpSafeFloor[16];

	// �������� ���� ���� ���� �ݶ��̴�
	// std::weak_ptr<CActor> m_wpSafeFloorCollider;

	// ������
	std::weak_ptr<CWallLaser> m_wpWallLasers[36];

	// Į��
	std::weak_ptr<CWallBlade> m_wpWallBlade[8];

	// ��ī�̹ڽ�
	std::weak_ptr<CSkyBox> m_wpSkyBox;

	// ���� Ʈ����
	std::weak_ptr<CBossTrigger> m_wpBossTrigger;

	// ���� ��ȯ Ʈ����
	std::weak_ptr<CSceneChangerActor> m_wpLevelChangeTrigger;
};

