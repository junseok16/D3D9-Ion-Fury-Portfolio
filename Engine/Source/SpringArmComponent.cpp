#include "pch.h"
#include "SpringArmComponent.h"

void CSpringArmComponent::Initialize()
{
	CSceneComponent::Initialize();
}

void CSpringArmComponent::BeginPlay()
{
	CSceneComponent::BeginPlay();
}

int32 CSpringArmComponent::Update(const float& _fDeltaSeconds)
{
	// 스프링 암 컴포넌트의 트랜스폼을 업데이트합니다.
	return CSceneComponent::Update(_fDeltaSeconds);
}

int32 CSpringArmComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CSceneComponent::LateUpdate(_fDeltaSeconds);
}

void CSpringArmComponent::Render()
{
	CSceneComponent::Render();
}

void CSpringArmComponent::EndPlay()
{
	CSceneComponent::EndPlay();
}

void CSpringArmComponent::Release()
{
	CSceneComponent::Release();
}
