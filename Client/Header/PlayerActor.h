#pragma once
#include "Character.h"

class CWeaponActor;
class CItemObjectActor;
class CPlayerEffectActor;
class CPlayerParticleActor;

class CSkyboxComponent;
class CCameraComponent;
class CSpotLightComponent;
class CParticleComponent;
class CSoundComponent;

enum class ERecallVoiceType
{
	DEJAVU,
	COMBACK,
	REFIGHT,
	ENUM_END
};

enum class EPlayerHittedSound
{
	NUM_1,
	NUM_2,
	NUM_3,
	ENUM_END
};

/**
 * @brief �÷��̾� ���� Ŭ�����Դϴ�.
 * @author �ڵ���
 * @date 2023-10-19
 */

class CPlayerActor : public CCharacter
{
public:
	explicit CPlayerActor() = default;
	virtual ~CPlayerActor() = default;

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

/********************
	Methods
********************/
public:
	void SetBillboard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent);

	void UpdateMouseMovement();

	void UpdateFSM(const float& _fDeltaSeconds);

	void UpdateSkillState();

	void UpdateSkillCoolTime(const float& _fDeltaSeconds);

	void AddWeapon(std::weak_ptr<CWeaponActor> _wpWeaponActor);

	void AddEffect(std::weak_ptr<CPlayerEffectActor> _wpEffectActor);

	void ColRecoveryItem(ERecoveryType eRecType, float fRecNum);

	void ColCardKeyItem(ERecoveryType eRecType);

	std::shared_ptr<CCubeColliderActor> HitScan();

/********************
	Component Initialization
********************/
private:
	virtual void ColliderSetting() override;
	virtual void PhysicsSetting() override;
	virtual void SoundSetting() override;

	void EffectSetting();
	void StatusSetting();
	void CameraSetting();
	void LightSetting();

	void KeyInput(const float& _fDeltaSeconds);

/********************
	Callbacks
********************/
public:
	// �ǰ�
	virtual void GetDamaged(const float& _fDamage);

private:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);
	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);
	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	// �̵�
	void MoveForward(int32 _iAxisValue, const float& _fDeltaSeconds);
	void MoveRight(int32 _iAxisValue, const float& _fDeltaSeconds);
	void Jump();
	void Crouch();

	// ����
	void Attack1();
	void Attack2();
	void Reload();

private:
	// ���� ��ü
	void ChangeWeapon(int32 _iWeaponNumber);

	// ��ų
	void Recall();		// �ӽ�
	void RecallOn() { if (!m_bRecallLock) { m_bRecallLock = true; m_iRecallCount = 0; } }
	void Blink();		// �ӽ�
	void BlinkOn() { m_bBlinkLock = true; m_fBlinkSec = 0.f; m_fForward = 1.f; m_fRight = 1.f; }
	void Sandevistan();

	// �ɷ�(ȸ�� ŰƮ, ���̴�)
	void UseRecoveryKit();
	void UseRadar();
	void ReduceExcessHp();

	// �ӽ� �ڵ�
	void ResetCurBullet();	// �ӽ�
	void SavePlayerInfo();	// �ӽ�
	
	void ShakeWeapon(float _fAxisValue);
	void LightOnOff();

public:
	bool IsBlickEnable() const { return m_bBlinkEnable; }
	bool IsRecallEnable() const { return m_bRecallEnable; }
	bool IsSandevistanEnable() const { return m_bBlinkEnable; }

	bool IsDisperserEnable() const { return m_bDisperser; }
	bool IsPenetratorEnable() const { return m_bPenetrator; }
	bool IsChainGunEnable() const { return m_bChainGun; }

/********************
	Getter / Setter
********************/
public:
	const	std::vector<std::weak_ptr<CWeaponActor>> GetWeaponVec() { return m_vecWeapons; }

	const	std::vector<std::weak_ptr<CPlayerEffectActor>> GetEffectVec() { return m_vecEffects; }

	void	SetCurrentWeapon(std::weak_ptr<CWeaponActor> _wpWeaponActor) { m_wpCurrentWeapon = _wpWeaponActor; }
	const	std::weak_ptr<CWeaponActor> GetCurrentWeapon() { CHECK(!m_wpCurrentWeapon.expired()); return m_wpCurrentWeapon; }

	void	SetHealingKit(int32 iKit) { m_iHealingKit += iKit; }
	const	int32& GetHealingKit() { return m_iHealingKit; }

	void	SetRadar(int32 iRadar) { m_iRadar += iRadar; }
	const	int32& GetRadar() { return m_iRadar; }

	void	SetJumpSpeed(const float& _fJumpSpeed) { m_fJumpSpeed = _fJumpSpeed; }
	const	float& GetJumpSpeed() { return m_fJumpSpeed; }

	void	SetBlinkCount(int32 _iBlinkCount) { m_iBlinkCurCount = _iBlinkCount; }
	int32   GetBlinkCount() { return m_iBlinkCurCount; }

	float	GetBlinkCoolTime() { return m_fBlinkCoolTime; }
	float	GetBlinkCoolRecovery() { return m_fBlinkCoolRecovery; }

	float	GetRecallCoolTime() { return m_fRecallCoolTime; }
	float	GetRecallCoolRecovery() { return m_fRecallCoolRecovery; }

	const	int32& GetCurWeaponNumber() { return m_iCurWeaponNumber; }

	void	SetDisperserEnable() { m_bDisperser = true; }
	void	SetPenetratorEnable() { m_bPenetrator = true; }
	void	SetChainGunEnable() { m_bChainGun = true; }

	void	SetBlinkEnable() { m_bBlinkEnable = true; }
	void	SetRecallEnable() { m_bRecallEnable = true; }
	void	SetSandevistanEnable() { m_bSandevistanEnable = true; }

	// LoverboyActor���� ī�޶� �ҷ��ͼ� SoundComponent�ϱ� ���� 
	std::weak_ptr<CCameraComponent> GetCurCamera() { return m_wpCameraComponent; }

	int32 GetCardKeyItem() { return m_iCardKeyNum; }
	void SetCardKeyItem(int32 _iCardKeyNum) { m_iCardKeyNum = _iCardKeyNum; }

/********************
	Data Members
********************/
private:
	std::weak_ptr<CSkyboxComponent>	m_wpSkyboxComponent;
	std::weak_ptr<CCameraComponent>	m_wpCameraComponent;
	std::weak_ptr<CSpotLightComponent> m_wpSpotLightComponent;

private:
#pragma region ����

	// ����
	std::vector<std::weak_ptr<CWeaponActor>> m_vecWeapons; // ����� ����
	std::weak_ptr<CWeaponActor> m_wpCurrentWeapon; // ���� ����ִ� ����

	int32 m_iCurWeaponNumber = 0; // ���� ������ �ε���
	int32 m_iCardKeyNum = 0;

	// ��Ʈ��ĵ, �Ѿ� ��
	int32 m_iBullet = 0;
	EWeaponType	m_wpPreWeapon = EWeaponType::ENUM_END;

	// ���� ȹ��
	bool		m_bDisperser = false;
	bool		m_bPenetrator = false;
	bool		m_bChainGun = false;

#pragma endregion ����
	
#pragma region �ִϸ��̼�

	// �ִϸ��̼�
	std::vector<std::weak_ptr<CPlayerEffectActor>> m_vecEffects; // ����Ʈ ���͵� ����
	std::wstring m_wstrAnimationState; // ���� �ִϸ��̼� ����

#pragma endregion �ִϸ��̼�

#pragma region ����

	// ���̽�
	EPlayerHittedSound m_ePlayerHittedSound = EPlayerHittedSound::NUM_1;

	ERecallVoiceType m_eRecallVoice = ERecallVoiceType::DEJAVU;

#pragma endregion ����

#pragma region ��ų

	// �ð�����
	bool		m_bRecallLock = false;
	std::list<PlayerInfo> m_lstPlayerInfo;
	std::list<PlayerInfo>::iterator m_lstIter;
	PlayerInfo	m_tPlayerInfo;
	int32		m_iRecallCount = 0;
	float		m_fRecallSaveSec = 0.f;

	int32		m_iRecallCurCount = 0; // ���� ��밡���� �ð����� Ƚ��
	int32		m_iRecallMaxCount = 1; // �ִ� ��밡���� �ð����� Ƚ��
	float		m_fRecallCoolRecovery = 0.0f;
	float		m_fRecallCoolTime = 10.0f; // �ð����� ��Ÿ��

	// ����
	bool		m_bBlinkLock = false;
	bool		m_bBlinkSound = false;
	bool		m_bWallCol = false;
	float		m_fBlinkSec = 0.f;
	float		m_fForward = 0.f;
	float		m_fRight = 0.f;

	int32		m_iBlinkCurCount = 3; // ���� ��밡���� ���� Ƚ��
	int32		m_iBlinkMaxCount = 3; // �ִ� ��밡���� ���� Ƚ��
	float		m_fBlinkCoolRecovery = 0.0f; // �� �ð��� m_fBlinkCoolTime�� �Ǹ� ������ �Ѱ� ���ϴ�.
	float		m_fBlinkCoolTime = 5.0f; // ���� ��Ÿ��

	// �ڵ�����
	bool		m_bIsLockOn = false;

	// �ѵ���ź
	bool		m_bIsSandevistan = false;

	// ��ų ���
	bool		m_bBlinkEnable = true;
	bool		m_bRecallEnable = true;
	bool		m_bSandevistanEnable = true;

#pragma endregion ��ų

#pragma region ��Ÿ

	// [ ȸ�� ŰƮ M / ���̴� N ]
	int32 m_iHealingKit = 0;
	int32 m_iRadar = 0;

	// ��Ÿ
	bool		m_bIsButton = false; // ü�� �ʰ� �� �ð� ��
	float		m_fShakeTime = 0.f;
	float		m_fStandard = 0.f; // �÷��̾� ü�¿� ī��Ʈ

	// ����
	BOOL		m_bIsLightEnable = TRUE; // ������ �Ѵ¿�

#pragma endregion ��Ÿ

};