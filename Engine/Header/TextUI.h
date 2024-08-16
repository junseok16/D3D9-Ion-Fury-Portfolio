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

	//숫자 집어 넣으면 그 숫자 텍스쳐를 출력하기 위한 함수 
	//virtual void SetUINumber(const int32& _iCurFrame);

	void SetTextUI(std::wstring _wstrText);

private:
	std::weak_ptr<CTextUIComponent> m_wpTextUIComponent;
};

