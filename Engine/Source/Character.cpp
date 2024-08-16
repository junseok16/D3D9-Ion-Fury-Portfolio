#include "pch.h"
#include "Character.h"

#include "InputComponent.h"
using namespace std;

void CCharacter::Initialize()
{
	m_wpInputComponent = CreateActorComponent<CInputComponent>(TEXT("InputComponent"));
	CCreature::Initialize();
}

void CCharacter::BeginPlay()
{
	CCreature::BeginPlay();
}

int32 CCharacter::Update(const float& _fDeltaSeconds)
{
	return CCreature::Update(_fDeltaSeconds);
}

int32 CCharacter::LateUpdate(const float& _fDeltaSeconds)
{
	return CCreature::LateUpdate(_fDeltaSeconds);
}

void CCharacter::Render()
{
	CCreature::Render();
}

void CCharacter::EndPlay()
{
	CCreature::EndPlay();
}

void CCharacter::Release()
{
	CCreature::Release();
}
