#include "pch.h"
#include "InteractiveBox.h"

#include "SoundComponent.h"
#include "AnimationComponent.h"
using namespace std;

void CInteractiveBox::Initialize()
{
	CActor::Initialize();
}

void CInteractiveBox::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CInteractiveBox::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CInteractiveBox::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CInteractiveBox::Render()
{
	CActor::Render();
}

void CInteractiveBox::EndPlay()
{
	CActor::EndPlay();
}

void CInteractiveBox::Release()
{
	CActor::Release();
}
