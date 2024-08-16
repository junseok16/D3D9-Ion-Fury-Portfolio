#pragma once
#include "UI.h"

class CTextUIComponent;

class CTextUI : public COutGameUI
{
public:
	explicit CTextUI() = default;
	virtual ~CTextUI() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;


	void SetTextUI(std::wstring _wstrText);

	// ���� ���� ������ �� ���ڿ� �´� �ؽ��ĸ� ����ϱ� ���� �Լ� 
	// ���߿� virtual�� ���� ���� �����Լ��� �����
	//virtual void SetUINumber(const int32& _iCurFrame) override;

private:
	int32 iSize;
	std::wstring wstrText;
	std::vector<std::weak_ptr<CTextUIComponent>> m_wpTextUIComponent;
};

