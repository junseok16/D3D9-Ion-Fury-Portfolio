#include "pch.h"
#include "MonsterUI.h"

#include "SpriteUIComponent.h"

void CMonsterUI::Initialize()
{
  //m_wpCrossHairUIComponent = CreateActorComponent<CSpriteUIComponent>(L"Sprite_UI");
  //m_wpCrossHairUIComponent.lock()->SetIsRootComponent(true);
  //m_wpCrossHairUIComponent.lock()->SettingUserInterfaceInfo(L"CrossHair_UI_", 0, 2, L"CrossHair_UI_", EUserInterfaceType::STATIC);
  //m_wpCrossHairUIComponent.lock()->SetComponentScale({ 100.f, 100.f, 0.f });
  //
  //// Local 포지션으로 위치값 조정, 중점은 0,0이며,  1280x720 생각하면서 배치하면됌
  //m_wpCrossHairUIComponent.lock()->SetComponentLocalPosition({ 0.f, 0.f, 0.f });
  //m_wpCrossHairUIComponent.lock()->SetCurrentUI(0);

    COutGameUI::Initialize();
}

void CMonsterUI::BeginPlay()
{
    m_wpCrossHairUIComponent.lock()->AddUIState(L"CrossHair_UI_", 0, 2);

    COutGameUI::BeginPlay();
}

int32 CMonsterUI::Update(const float& _fDeltaSeconds)
{
    return COutGameUI::Update(_fDeltaSeconds);
}

int32 CMonsterUI::LateUpdate(const float& _fDeltaSeconds)
{
    return COutGameUI::LateUpdate(_fDeltaSeconds);
}

void CMonsterUI::Render()
{
    COutGameUI::Render();
}

void CMonsterUI::EndPlay()
{
    COutGameUI::EndPlay();
}

void CMonsterUI::Release()
{
    COutGameUI::Release();
}
