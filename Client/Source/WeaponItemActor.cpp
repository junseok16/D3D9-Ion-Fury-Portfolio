#include "pch.h"
#include "WeaponItemActor.h"
using namespace std;

void CWeaponItemActor::Initialize()
{
	m_eItemType = EItemType::WEAPON;
	CItem::Initialize();
}

void CWeaponItemActor::BeginPlay()
{
	CItem::BeginPlay();
}

int32 CWeaponItemActor::Update(const float& _fDeltaSeconds)
{
	return CItem::Update(_fDeltaSeconds);
}

int32 CWeaponItemActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CItem::LateUpdate(_fDeltaSeconds);
}

void CWeaponItemActor::Render()
{
	CItem::Render();
}

void CWeaponItemActor::EndPlay()
{
	CItem::EndPlay();
}

void CWeaponItemActor::Release()
{
	CItem::Release();
}
