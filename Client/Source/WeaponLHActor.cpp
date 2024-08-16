#include "pch.h"
#include "WeaponLHActor.h"
#include "AnimationComponent.h"
using namespace std;

void CWeaponLHActor::Initialize()
{
	SetRenderType(ERenderType::ORTHOGONAL);

	CActor::Initialize();
}

void CWeaponLHActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CWeaponLHActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CWeaponLHActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CWeaponLHActor::Render()
{
	CActor::Render();
}

void CWeaponLHActor::EndPlay()
{
	CActor::EndPlay();
}

void CWeaponLHActor::Release()
{
	CActor::Release();
}