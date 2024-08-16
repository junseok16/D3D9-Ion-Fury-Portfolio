#pragma once
#include "BTTaskNode.h"

class CReposeToTask : public CBTTaskNode
{
public:
	explicit CReposeToTask() = default;
	virtual ~CReposeToTask() = default;

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

public:
	void SetDstKey(const std::wstring& _wstrDstKey) { m_wstrDstKey = _wstrDstKey; }
	void SetCenter(const FVector3& _vCenter) { m_vCenter = _vCenter; }
	void SetWidth(float _fHeight) { m_fWidth = _fHeight; }
	void SetHeight(float _fHeight) { m_fHeight = _fHeight; }

private:
	std::wstring m_wstrDstKey = L"";

	// �߽���
	FVector3 m_vCenter = { 0.0f, 0.0f, 0.0f };

	// �̵��� �� �ִ� ���� ����
	float m_fWidth = 0;

	// �̵��� �� �ִ� ���� ����
	float m_fHeight = 0;
};

