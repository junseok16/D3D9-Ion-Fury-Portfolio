#include "pch.h"
#include "SnowParticleComponent.h"

#include "Actor.h"

void CSnowParticleComponent::Initialize()
{
	for(int i = 0; i < 50; ++i)
		AddParticle();
	
	CParticleComponent::Initialize();
}