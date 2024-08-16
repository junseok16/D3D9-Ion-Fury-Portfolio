#include "pch.h"
#include "BulletActor.h"
using namespace std;

void CBulletActor::Initialize()
{
	m_eItemType = EItemType::BULLET;
	CItem::Initialize();
}

void CBulletActor::BeginPlay()
{
	CItem::BeginPlay();
}

int32 CBulletActor::Update(const float& _fDeltaSeconds)
{
	return CItem::Update(_fDeltaSeconds);
}

int32 CBulletActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CItem::LateUpdate(_fDeltaSeconds);
}

void CBulletActor::Render()
{
	CItem::Render();
}

void CBulletActor::EndPlay()
{
	CItem::EndPlay();
}

void CBulletActor::Release()
{
	CItem::Release();
}
