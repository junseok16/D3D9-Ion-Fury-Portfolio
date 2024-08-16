#pragma once
#include "UI.h"

class CLeverBox;
class CWeaponActor;
class CPlayerActor;
class CRecoveryActor;
class CSoundComponent;
class CTextUIComponent;
class CSpriteUIComponent;

class COutGameUI : public CUI
{
public:
	explicit COutGameUI() = default;
	virtual ~COutGameUI() = default;

public:
	virtual void  Initialize() override;
	virtual void  BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void  Render() override;
	virtual void  EndPlay() override;
	virtual void  Release() override;

	// Number �÷��̾� ü��, ���� ü��, ��ź��, ������ ���� ���� �������ִ� �Լ�(���� UI������ �ٲ�� ������ ���� ����)
	void SetPlayerUINumber(const int32& _iCurFrame);
	void SetArmorUINumber(const int32& _iCurFrame);
	void SetBulletUINumber(const int32& _iCurFrame);
	void SetItemUINumber(const int32& _iCurFrame);

	// Icon �÷��̾�, ����, ���� ����, ������ ���� ������ �������ִ� �Լ�
	void SetPlayerIconUI(const int32& _iCurFrame);
	void SetArmorIconUI(const int32& _iCurFrame);
	void SetBulletIconUI(EWeaponType _eWeaponType);
	void SetItemIconUI(int32 _eItemType);
	void SetItemNumIconUI(ESkillType _eSkillType);
	void SetItemTextIconUI(ESkillType _eSkillType);

	void SetDisLeverActor(float _fDis) { m_fLeverDis = _fDis; }
	void SetDisCardKeyActor(float _fDis) { m_fCardKeyDis = _fDis; }
	void SetDisElevatorButtonActor(float _fDis) { m_fElevatorButtonDis = _fDis; }
	void SetDisElevatorButtonActor1(float _fDis) { m_fElevatorButtonDis1 = _fDis; }
	void SetPowerMonitorActor(float _fDis) { m_fPowerMonitorDis = _fDis; }
	void SetPowerMonitorActor1(float _fDis) { m_fPowerMonitorDis1 = _fDis; }
	void InteractiveBoxTextUI();

	// ���� ���� ü���� �ʱⰪ�� �������ֱ� ���� �Լ�
	void InitBossMonsterInfo(float _fMaxHp);

	// ���� ���Ϳ��� ���� �������� ���� ���� ü�¹� ���̸� �����ϴ� �Լ�
	void SetBossMonsterHpBar(float _fPlayerAtk);

	void ActivateBossHpBar();

private:
	void KeyInput();
	void OutGameUISetting();
	void OutGameUIBegingPlaySetting();

public:
	// �浹 �� ��� ���ο� ���õ� �Լ��Դϴ�(���� �̻����)
	void SetAlphabetSprites(const std::vector<std::weak_ptr<CTextUIComponent>>& vecAlphabetComponents, const std::wstring& text);
	void SetAlphabetSprites1(const std::wstring& _wstrText);
	void ClearVecInteractiveBox() { m_vecInteractiveBoxUIComponent.clear(); }

	// Getter Setter
	const std::vector<std::weak_ptr<CTextUIComponent>>& GetInteractiveBoxUIComponent() const { return m_vecInteractiveBoxUIComponent;}
	void SetInteractiveBoxUIComponent(const std::vector<std::weak_ptr<CTextUIComponent>>& vec) { m_vecInteractiveBoxUIComponent = vec;}

private:
	float m_fDamagePerHit = 0.045f;
	float m_fComScaleX = 225.f;
	float m_fBossMaxHp = 5000.f;
	float m_fLeverDis = 0.f;
	float m_fCardKeyDis = 0.f;
	float m_fElevatorButtonDis = 0.f;
	float m_fElevatorButtonDis1 = 0.f;
	float m_fPowerMonitorDis = 0.f;
	float m_fPowerMonitorDis1 = 0.f;
	float m_fRotationZ = 0.f;
	std::weak_ptr<CRecoveryActor> m_wpRecoveryActor;
	std::weak_ptr<CLeverBox> m_wpLeverBoxActor;
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;



	std::weak_ptr<CSpriteUIComponent>  m_wpCrossHairUIComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpCrossHairRedUIComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpPlayerUIComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpBulletUIComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpArmorUIComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpItemUIComponent;

	// ���� ü�¹�
	std::weak_ptr<CSpriteUIComponent>  m_wpBossBarComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpBossHpBarComponent;

	// ���� ���� �ٲ�� ���� ����
	std::weak_ptr<CSpriteUIComponent>  m_wpPlayerHpHundredsPlaceComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpPlayerHpTensPlaceComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpPlayerHpOnesPlaceComponent;

	std::weak_ptr<CSpriteUIComponent>  m_wpArmorHpHundredsPlaceComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpArmorHpTensPlaceComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpArmorHpOnesPlaceComponent;

	std::weak_ptr<CSpriteUIComponent>  m_wpBulletHpHundredsPlaceComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpBulletHpTensPlaceComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpBulletHpOnesPlaceComponent;

	std::weak_ptr<CSpriteUIComponent>  m_wpItemNumComponent;
	std::weak_ptr<CSpriteUIComponent>  m_wpItemTextComponent;

	// ���� �ٲ� ������ ����� ���͵�
	std::vector<std::weak_ptr<CTextUIComponent>> m_vecPlayerHpUIComponent;
	std::vector<std::weak_ptr<CTextUIComponent>> m_vecArmorHpUIComponent;
	std::vector<std::weak_ptr<CTextUIComponent>> m_vecBulletHpUIComponent;
	std::vector<std::weak_ptr<CTextUIComponent>> m_vecAlphabetUIComponent;

	std::vector<std::weak_ptr<CTextUIComponent>> m_vecInteractiveBoxUIComponent;

	std::weak_ptr<CSoundComponent> m_wpSoundComponent;

};
