#pragma once
#include "Actor.h"

class CParticleComponent;

class CRainParticleActor : public CActor
{
public:
	explicit CRainParticleActor() = default;
	virtual ~CRainParticleActor() = default;

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
	void ParticleComponentSetting();

/********************
	Data Members
********************/
private:
	std::weak_ptr<CParticleComponent>	m_wpParticleComponent;
};

