#pragma once
#include "Actor.h"

class CSoundComponent;

class CInteractiveBox : public CActor
{
public:
	explicit CInteractiveBox() = default;
	virtual ~CInteractiveBox() = default;

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

public:
	bool GetDoorStatus() { return m_bDoorStatus; }
	void SetDoorStatus(bool _bDoorStatus) { m_bDoorStatus = _bDoorStatus; }

protected:
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;
	bool m_bDoorStatus = false;
};
