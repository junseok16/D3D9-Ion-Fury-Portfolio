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
	// ������ �� ������Ʈ�� Ʈ�������� ������Ʈ�մϴ�.
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
