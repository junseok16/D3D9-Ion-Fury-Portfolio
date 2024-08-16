#pragma once
#include "ParticleComponent.h"

class CSnowParticleComponent :
    public CParticleComponent
{
public:
	explicit CSnowParticleComponent() = default;
	virtual ~CSnowParticleComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;

	virtual void PreRender();
	virtual void Render() override;
	virtual void PostRender();

	virtual void EndPlay() override;
	virtual void Release() override;

public:
	virtual void ResetParticles(ParticleAttribute* _tParticleAttribute);
};

