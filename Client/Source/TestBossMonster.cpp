#include "pch.h"
#include "TestBossMonster.h"
#include "RectangleMeshComponent.h"
#include "UIComponent.h"
#include "DeviceManager.h"
#include "RenderManager.h"
using namespace std;

void CTestBossMonster::Initialize()
{
	// 보스몬스터 컴포넌트
	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	//SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetIsRootComponent(true);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 9.f, 21.f, 10.f });
	m_wpRectangleMeshComponent.lock()->SetComponentLocalPosition({ 0.f, 0.f, 0.f });
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"../Resource/Texture/UI/Monster/BossMonster/TestMonster", 0, 0);

	// 체력바 컴포넌트
	m_wpUIComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Bar");
	m_wpUIComponent.lock()->SetIsRootComponent(true);
	//m_wpUIComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	/*m_wpUIComponent.lock()->SettingUserInterfaceInfo(
		L"../Resource/Texture/UI/Hp/Hp_Bar/Hp_Bar_",
		L"png",
		L"Hp_Bar_",
		EUserInterfaceType::STATIC,
		0, 1, 1,
		0.0f);*/
	m_wpUIComponent.lock()->SetCurrentUI(1);
	m_wpUIComponent.lock()->SetComponentScale({ 16.f, 1.f, 10.f });
	m_wpUIComponent.lock()->SetComponentLocalPosition({ 0.f, 22.f, 0.f });
	   
	CCharacter::Initialize();
}

void CTestBossMonster::BeginPlay()
{
	// m_wpUIComponent.lock()->AddTexture(L"../Resource/Texture/UI/Hp/Hp_Bar/Hp_Bar_", L"png", L"Hp_Bar_", 1);
	CCharacter::BeginPlay();
}

int32 CTestBossMonster::Update(const float& _fDeltaSeconds)
{
	return CCharacter::Update(_fDeltaSeconds);
}

int32 CTestBossMonster::LateUpdate(const float& _fDeltaSeconds)
{
	return CCharacter::LateUpdate(_fDeltaSeconds);
}

void CTestBossMonster::Render()
{
	// 테스트용 (쉽게 보기 위해서), 후면 추려내기 안해줌
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	CCharacter::Render();
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CTestBossMonster::EndPlay()
{
	CCharacter::EndPlay();
}

void CTestBossMonster::Release()
{
	CCharacter::Release();
}
