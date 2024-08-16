#include "pch.h"
#include "ItemActor.h"
#include "CollisionManager.h"
#include "RectangleMeshComponent.h"
using namespace std;

void CItemActor::Initialize()
{
	CActor::Initialize();
}

void CItemActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CItemActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CItemActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CItemActor::Render()
{
	CActor::Render();
}

void CItemActor::EndPlay()
{
	CActor::EndPlay();
}

void CItemActor::Release()
{
	CActor::Release();
}
