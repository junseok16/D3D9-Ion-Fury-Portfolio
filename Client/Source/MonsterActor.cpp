#include "pch.h"
#include "MonsterActor.h"

#include "TimerManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"

#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "InputComponent.h"
#include "SkyboxComponent.h"
#include "RectColliderComponent.h"

using namespace std;

void CMonsterActor::Initialize()
{
	AnimationSetting();

	CActor::Initialize();
}

void CMonsterActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CMonsterActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CMonsterActor::LateUpdate(const float& _fDeltaSeconds)
{
	// CActor::SetBillBoard(m_wpAnimationComponent);
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CMonsterActor::Render()
{
	CActor::Render();
}

void CMonsterActor::EndPlay()
{
	CActor::EndPlay();
}

void CMonsterActor::Release()
{
	CActor::Release();
}

void CMonsterActor::AnimationSetting()
{
	// 애니메이션 컴포넌트
	// m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"PlayerAnimationComponent");
	// m_wpAnimationComponent.lock()->SetIsRootComponent(true);
	// m_wpAnimationComponent.lock()->SettingAnimationInfo(L"../Resource/Texture/Player/Foward/Walk/Player_Walk_",		// 텍스처 파일 경로
	// 	L"png",														// 텍스처 파일 확장자
	// 	L"Player_Walk_",											// 텍스처 상태 키 값
	// 	EAnimationType::LOOP,										// 애니메이션 타입
	// 	0, 0, 3,													// 시작, 현재, 끝 프레임 인덱스
	// 	0.1f);														// 프레임 속도 설정 값
	// m_wpAnimationComponent.lock()->SetComponentScale({ 5.0f, 5.0f, 5.0f });
}