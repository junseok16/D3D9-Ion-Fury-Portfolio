#pragma once
#include "UI.h"

class CUIComponent;

class CWeaponUI : public CUI
{
public:
	explicit CWeaponUI() = default;
	virtual ~CWeaponUI() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	//숫자 집어 넣으면 그 숫자에 맞는 텍스쳐를 출력하기 위한 함수 
	//virtual void SetUINumber(const int32& _iCurFrame) override;

private:
	std::weak_ptr<CUIComponent> m_wpUIHpHundredsPlaceComponent;
	std::weak_ptr<CUIComponent> m_wpUIHpTensPlaceComponent;
	std::weak_ptr<CUIComponent> m_wpUIHpOnesPlaceComponent;

	std::weak_ptr<CUIComponent> m_wpWeaponUIComponent;
};

