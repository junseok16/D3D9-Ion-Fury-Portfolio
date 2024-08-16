#pragma once
#include "Level.h"

class CPlayerActor;
class CGenjiActor;
class CHealthPackActor;
class CTerrainActor;
class CElectrifryerActor;

class CTestLevel : public CLevel
{
public:
	explicit CTestLevel() = default;
	virtual ~CTestLevel() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CGenjiActor> m_wpGenjiActor;
	std::weak_ptr<CTerrainActor> m_wpTerrainActor;
	std::weak_ptr<CElectrifryerActor> m_wpElectrifryerActor;
};

