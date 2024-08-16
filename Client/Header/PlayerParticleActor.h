#pragma once
#include "Actor.h"

class CParticleComponent;

class CPlayerParticleActor : public CActor
{
public:
	explicit CPlayerParticleActor() = default;
	virtual ~CPlayerParticleActor() = default;

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
/********************
	Methods
********************/
public:
	void ParticleComponentSetting();

/********************
	Getter / Setter
********************/
public:
	std::weak_ptr<CParticleComponent>& GetParticleComponent() { return m_wpParticleComponent; }

/********************
	Data Members
********************/
private:
	std::weak_ptr<CParticleComponent> m_wpParticleComponent;

};