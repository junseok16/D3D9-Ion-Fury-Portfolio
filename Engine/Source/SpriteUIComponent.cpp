#include "pch.h"
#include "SpriteUIComponent.h"

void CSpriteUIComponent::Initialize()
{
    CNonInteractiveUIComponent::Initialize();
}

void CSpriteUIComponent::BeginPlay()
{
    CNonInteractiveUIComponent::BeginPlay();
}

int32 CSpriteUIComponent::Update(const float& _fDeltaSeconds)
{
    return CNonInteractiveUIComponent::Update(_fDeltaSeconds);
}

int32 CSpriteUIComponent::LateUpdate(const float& _fDeltaSeconds)
{
    return CNonInteractiveUIComponent::LateUpdate(_fDeltaSeconds);
}

void CSpriteUIComponent::Render()
{
    CNonInteractiveUIComponent::Render();
}

void CSpriteUIComponent::EndPlay()
{
    CNonInteractiveUIComponent::EndPlay();
}

void CSpriteUIComponent::Release()
{
    CNonInteractiveUIComponent::Release();
}

void CSpriteUIComponent::SetUINumber(const int32& _iCurFrame)
{
	int32 Num[3];
	std::string strNum = std::to_string(_iCurFrame);

	if (_iCurFrame <= 999 && _iCurFrame >= 0) {
		if (_iCurFrame > 99 && _iCurFrame <= 999) {
			Num[0] = strNum[0] - '0';
			Num[1] = strNum[1] - '0';
			Num[2] = strNum[2] - '0';
		}
		else if (_iCurFrame > 9 && _iCurFrame <= 99) {
			Num[0] = 10;
			Num[1] = strNum[0] - '0';
			Num[2] = strNum[1] - '0';
		}
		else if (_iCurFrame >= 0 && _iCurFrame <= 9) {
			Num[0] = 10;
			Num[1] = 10;
			Num[2] = strNum[0] - '0';
		}
	}
	else {
		Num[0] = 10;
		Num[1] = 10;
		Num[2] = 10;
	}
	SetCurrentUI(Num[0]);
	SetCurrentUI(Num[1]);
	SetCurrentUI(Num[2]);
}