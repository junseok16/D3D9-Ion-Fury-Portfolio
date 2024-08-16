#pragma once
#include "Actor.h"

class CEffectComponent;

class CPlayerEffectActor :
	public CActor
{
public:
	explicit CPlayerEffectActor() = default;
	virtual ~CPlayerEffectActor() = default;

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
	void HittedCheck(const float& _fDeltaSeconds);
	void RecallCheck();
	void BlinkCheck();
	void LockOnCheck();
	void SandevistanCheck();

	void EffectComponentSetting();

	void CheckBlinkCount();

	void CheckSkillCoolTime();

/********************
	Getter / Setter
********************/
	const std::weak_ptr<CEffectComponent>& GetEffectComponent() { return m_wpFullScreenEffectComponent; }

	void SetIsHitted(bool _bIsHitted) { m_bIsHitted = _bIsHitted; }
	bool GetIsHitted() { return m_bIsHitted; }

	void SetIsRecall(bool _bIsRecall) { m_bIsRecall = _bIsRecall; }
	bool GetIsRecall() { return m_bIsRecall; }

	void SetIsBlink(bool _bIsBlink) { m_bIsBlink = _bIsBlink; }
	bool GetIsBlink() { return m_bIsBlink; }

	void SetIsLockOn(bool _bIsLockOn) { m_bIsLockOn = _bIsLockOn; }
	bool GetIsLockOn() { return m_bIsLockOn; }

	void SetIsSandevistan(bool _bIsSandevistan) { m_bIsSandevistan = _bIsSandevistan; }
	bool GetIsSandevistan() { return m_bIsSandevistan; }

/********************
	Data Members
********************/
private:
	// 전체화면 이펙트
	std::weak_ptr<CEffectComponent> m_wpFullScreenEffectComponent;

	// 점멸 개수 이펙트
	std::weak_ptr<CEffectComponent> m_wpBlinkCountEffectComponent;

	// 점멸 아이콘
	std::weak_ptr<CEffectComponent> m_wpBlinkIconEffectComponent;

	// 점멸 쿨타임 아이콘
	std::weak_ptr<CEffectComponent> m_wpBlinkCoolTimeIconEffectComponent;

	// 시간역행 아이콘
	std::weak_ptr<CEffectComponent> m_wpRecallIconEffectComponent;

	// 시간역행 쿨타임 아이콘
	std::weak_ptr<CEffectComponent> m_wpRecallCoolTimeIconEffectComponent;
	
	
	float m_fX = 0; // 뷰포트 상의 좌표
	float m_fY = 0;

	float m_fSizeX = CFWINCX; // 크기
	float m_fSizeY = CFWINCY;

	float m_fHittedEffectTime = 0.0f;

	// 플레이어 상태
	bool m_bIsHitted = false;
	bool m_bIsRecall = false;
	bool m_bIsBlink = false;
	bool m_bIsLockOn = false;
	bool m_bIsSandevistan = false;
};

