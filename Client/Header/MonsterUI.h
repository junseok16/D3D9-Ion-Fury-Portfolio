#pragma once
#include "OutGameUI.h"

class CSpriteUIComponent;

class CMonsterUI : public COutGameUI
{
public:
	explicit CMonsterUI() = default;
	virtual ~CMonsterUI() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	std::weak_ptr<CSpriteUIComponent> m_wpCrossHairUIComponent;
};

