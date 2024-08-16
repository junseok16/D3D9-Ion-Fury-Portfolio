#pragma once
#include "UI.h"

class CUIComponent;
class CSpriteUIComponent;

class CArmorUI : public CUI
{
public:
	explicit CArmorUI() = default;
	virtual ~CArmorUI() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	//���� ���� ������ �� ���ڿ� �´� �ؽ��ĸ� ����ϱ� ���� �Լ� 
	///virtual void SetUINumber(const int32& _iCurFrame) override;

private:
	std::weak_ptr<CUIComponent> m_wpUIHpHundredsPlaceComponent;
	std::weak_ptr<CUIComponent> m_wpUIHpTensPlaceComponent;
	std::weak_ptr<CUIComponent> m_wpUIHpOnesPlaceComponent;

	std::weak_ptr<CUIComponent> m_wpArmorUIComponent;


	std::weak_ptr<CSpriteUIComponent> m_wpCrossHairUIComponent;
};

