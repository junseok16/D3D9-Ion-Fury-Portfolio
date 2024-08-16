#include "pch.h"
#include "CubeColliderActor.h"
#include "CubeColliderComponent.h"

using namespace std;

void CCubeColliderActor::Initialize()
{
	CActor::Initialize();
}

void CCubeColliderActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CCubeColliderActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CCubeColliderActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CCubeColliderActor::Render()
{
	CActor::Render();
}

void CCubeColliderActor::EndPlay()
{
	CActor::EndPlay();
}

void CCubeColliderActor::Release()
{
	CActor::Release();
}