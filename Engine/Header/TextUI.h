#pragma once
#include "UI.h"

class CTextUIComponent;

class CTextUI : public CUI
{
public:
	explicit CTextUI() = default;
	virtual ~CTextUI() = default;

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

	//���� ���� ������ �� ���� �ؽ��ĸ� ����ϱ� ���� �Լ� 
	//virtual void SetUINumber(const int32& _iCurFrame);

	void SetTextUI(std::wstring _wstrText);

private:
	std::weak_ptr<CTextUIComponent> m_wpTextUIComponent;
};

