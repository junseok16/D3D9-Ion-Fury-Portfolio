#pragma once
#include "Level.h"

class CActor;

class CEditorLevel : public CLevel
{
public:
	explicit CEditorLevel() = default;
	virtual ~CEditorLevel() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;
};

