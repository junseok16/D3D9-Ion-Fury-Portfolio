#pragma once
#include "Window.h"

class CEditorLevel;

class COutlinerWindow : public CWindow
{
public:
	explicit COutlinerWindow() = default;
	virtual ~COutlinerWindow() = default;

public:
	virtual void Initialize(std::weak_ptr<CLevel> _wpLevel) override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void UpdateHeaderFile();
		void UpdateSeparatorPrefabData();
		void UpdateSeparatorSpawnbData();

private:
	// 레벨 포인터
	std::weak_ptr<CEditorLevel> m_wpEditorLevel;

	bool m_bOutliner = true;

	// 프리팹 데이터 파일 이름
	char m_chPrefabDataFileName[64] = { 0 };

	// 스폰 데이터 파일 이름
	char m_chSpawnDataFileName[64] = { 0 };
};

