#include "pch.h"
#include "ItemObjectActor.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"

#include "LoverboyBulletActor.h"
#include "DisperserBulletActor.h"
#include "PenetratorBulletActor.h"
#include "ChainGunBulletActor.h"

#include "HealthPackActor.h"
#include "SyringeActor.h"
#include "ArmorActor.h"
#include "ArmorPieceActor.h"

using namespace std;

uint32 CItemObjectActor::s_iItemIndex = 0;

void CItemObjectActor::Initialize()
{
	CItem::Initialize();
}

void CItemObjectActor::BeginPlay()
{
	CItem::BeginPlay();
}

int32 CItemObjectActor::Update(const float& _fDeltaSeconds)
{
	return CItem::Update(_fDeltaSeconds);
}

int32 CItemObjectActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CItem::LateUpdate(_fDeltaSeconds);
}

void CItemObjectActor::Render()
{
	CItem::Render();
}

void CItemObjectActor::EndPlay()
{
	CItem::EndPlay();
}

void CItemObjectActor::Release()
{
	CItem::Release();
}

void CItemObjectActor::CreateItem(int32 iCapaType)
{
	FVector3 vPlayerVec = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetActorPosition();
	vPlayerVec -= GetActorPosition();
	D3DXVec3Normalize(&vPlayerVec, &vPlayerVec);

	switch (m_eWeaponType)
	{
	case EWeaponType::LOVERBOY:
		m_wpLoverboyBulletActor = GetLevel().lock()->CreateActor<CLoverboyBulletActor>(L"LoverboyBullet" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpLoverboyBulletActor.lock()->SetCapaType(iCapaType);
		m_wpLoverboyBulletActor.lock()->Initialize();
		m_wpLoverboyBulletActor.lock()->BeginPlay();
		m_wpLoverboyBulletActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	case EWeaponType::DISPERSER:
		m_wpDisperserBulletActor = GetLevel().lock()->CreateActor<CDisperserBulletActor>(L"DisperserBullet" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpDisperserBulletActor.lock()->Initialize();
		m_wpDisperserBulletActor.lock()->BeginPlay();
		m_wpDisperserBulletActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	case EWeaponType::PENETRATOR:
		m_wpPenetratorBulletActor = GetLevel().lock()->CreateActor<CPenetratorBulletActor>(L"PenetratorBullet" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpPenetratorBulletActor.lock()->Initialize();
		m_wpPenetratorBulletActor.lock()->BeginPlay();
		m_wpPenetratorBulletActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	case EWeaponType::CHAINGUN:
		m_wpChainGunBulletActor = GetLevel().lock()->CreateActor<CChainGunBulletActor>(L"ChainGunBullet" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpChainGunBulletActor.lock()->Initialize();
		m_wpChainGunBulletActor.lock()->BeginPlay();
		m_wpChainGunBulletActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	default:
		break;
	}

	switch (m_eRecoveryType)
	{
	case ERecoveryType::HEALTHPACK:
	{
		m_wpCHealthPackActor = GetLevel().lock()->CreateActor<CHealthPackActor>(L"HealthPack" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpCHealthPackActor.lock()->SetCapaType(iCapaType);
		m_wpCHealthPackActor.lock()->Initialize();
		m_wpCHealthPackActor.lock()->BeginPlay();
		m_wpCHealthPackActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
	}
		break;

	case ERecoveryType::SYRINGE:
		m_wpSyringeActor = GetLevel().lock()->CreateActor<CSyringeActor>(L"Syringe" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpSyringeActor.lock()->Initialize();
		m_wpSyringeActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	case ERecoveryType::ARMOR:
		m_wpArmorActor = GetLevel().lock()->CreateActor<CArmorActor>(L"Armor" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpArmorActor.lock()->SetCapaType(iCapaType);
		m_wpArmorActor.lock()->Initialize();
		m_wpArmorActor.lock()->BeginPlay();
		m_wpArmorActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	case ERecoveryType::ARMORPIECE:
		m_wpArmorPieceActor = GetLevel().lock()->CreateActor<CArmorPieceActor>(L"ArmorPiece" + to_wstring(s_iItemIndex), L"Item", L"Actor");
		m_wpArmorPieceActor.lock()->Initialize();
		m_wpArmorPieceActor.lock()->SetActorPosition(GetActorPosition() + vPlayerVec);
		break;

	default:
		break;
	}
	s_iItemIndex++;
}
