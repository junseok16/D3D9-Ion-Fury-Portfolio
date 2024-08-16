#include "pch.h"
#include "PowerMonitor1.h"

#include "Level.h"

// Manager
#include "InputManager.h"
#include "RenderManager.h"

// Actor
#include "OutGameUI.h"
#include "PlayerActor.h"

// Component
#include "SoundComponent.h"
#include "AnimationComponent.h"

using namespace std;

void CPowerMonitor1::Initialize()
{
    InGameSetting();

    m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
    m_wpSoundComponent.lock()->SetOwnerComponent(m_wpSoundComponent);

    SetRenderType(ERenderType::NON_ALPHA);
    CInteractiveBox::Initialize();
}

void CPowerMonitor1::BeginPlay()
{
    m_wpOutGameUI = dynamic_pointer_cast<COutGameUI>(GetLevel().lock()->FindActor(L"OutGameUI"));
    m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
    m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 1.f, 30.f, 1.f, 90.f);

    m_wpPowerMonitor.lock()->AddState(L"PowerMonitor", 0, 12);
    m_wpPowerMonitor.lock()->AddState(L"PowerMonitor1", 13, 15);

    CInteractiveBox::BeginPlay();
}

int32 CPowerMonitor1::Update(const float& _fDeltaSeconds)
{
    KeyInput(_fDeltaSeconds);
    SetPowerMonitorFrame();

    return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CPowerMonitor1::LateUpdate(const float& _fDeltaSeconds)
{
    return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CPowerMonitor1::Render()
{
    CInteractiveBox::Render();
}

void CPowerMonitor1::EndPlay()
{
    CInteractiveBox::EndPlay();
}

void CPowerMonitor1::Release()
{
    CInteractiveBox::Release();
}

int32 CPowerMonitor1::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
    return 0;
}

void CPowerMonitor1::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CPowerMonitor1::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CPowerMonitor1::KeyInput(const float& _fDeltaSeconds)
{
    FVector3 fv = m_wpPlayerActor.lock()->GetActorWorldPosition() - m_wpPowerMonitor.lock()->GetOwnerActor().lock()->GetActorWorldPosition();
    float fDis = D3DXVec3Length(&fv);

    m_wpOutGameUI.lock()->SetPowerMonitorActor1(fDis);

    if (m_fElapsedTime <= 1.f)
    {
        if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::RIGHT_BUTTON)
            && m_wpPlayerActor.lock()->GetCurWeaponNumber() == (int32)EWeaponType::ELECTRIFRYER
            && fDis <= 50.f)
        {
            m_fElapsedTime += _fDeltaSeconds;
            m_wpPowerMonitor.lock()->SetCurFrame(0);
            m_wpPowerMonitor.lock()->SetIsAnimate(true);
        }
    }
    if (m_fElapsedTime > 1.f)
    {
        m_fElapsedTime = 0.0f;
        m_bPowerMonitor = true;
    }
}

void CPowerMonitor1::InGameSetting()
{
    m_wpPowerMonitor = CreateActorComponent<CAnimationComponent>(L"PowerMonitorComponent");
    SetRootComponent(m_wpPowerMonitor);
    m_wpPowerMonitor.lock()->SettingAnimationInfo(L"PowerMonitor0_", 0, 15, L"PowerMonitor", EAnimationType::DESIGNATED_TIME, 0.5f);
    m_wpPowerMonitor.lock()->SetCurFrame(0);
    m_wpPowerMonitor.lock()->SetIsAnimate(false);

}

void CPowerMonitor1::SetPowerMonitorFrame()
{
    std::wstring wstrCurrentState = m_wpPowerMonitor.lock()->GetCurrentState();
    int32 iEndFrame = m_wpPowerMonitor.lock()->GetStateFrame(wstrCurrentState).second;

    if (m_bPowerMonitor == true && m_wpPowerMonitor.lock()->GetCurFrame() == iEndFrame)
    {
        m_wpPowerMonitor.lock()->SetCurrentState(L"PowerMonitor1");
        m_wpPowerMonitor.lock()->SetAnimationType(EAnimationType::LOOP);
        m_wpPlayerActor.lock()->SetRecallEnable();
    }
    else if (m_bPowerMonitor == false && m_wpPowerMonitor.lock()->GetCurFrame() == 9)
    {
        m_wpPowerMonitor.lock()->SetCurFrame(0);
        m_wpPowerMonitor.lock()->SetIsAnimate(false);
        m_wpPowerMonitor.lock()->SetAnimationType(EAnimationType::LOOP);
    }
}
