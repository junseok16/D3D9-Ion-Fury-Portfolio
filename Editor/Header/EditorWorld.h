#pragma once
#include "World.h"

class CModeWindow;
class COutlinerWindow;
class CEditorCamera;

class CEditorWorld : public CWorld
{
public:
	explicit CEditorWorld() = default;
	virtual ~CEditorWorld() = default;

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

protected:
	std::shared_ptr<CEditorCamera> m_spEditorCamera;
	std::shared_ptr<CModeWindow> m_spModeWindow;
	std::shared_ptr<COutlinerWindow> m_spOutlinerWindow;
};

