#include "pch.h"
#include "SunActor.h"

#include "DirectionalLightComponent.h"
//#include "PointLightComponent.h"
using namespace std;

void CSunActor::Initialize()
{
	m_wpDirectionalLightComponent = CreateActorComponent<CDirectionalLightComponent>(L"LightComponent");
	SetRootComponent(m_wpDirectionalLightComponent);
	
	/*m_wpPointLightComponent = CreateActorComponent<CPointLightComponent>(L"LightComponent");
	SetRootComponent(m_wpPointLightComponent);*/

	CActor::Initialize();
}

void CSunActor::BeginPlay()
{
	m_wpDirectionalLightComponent.lock()->SetDirLightInfo({ 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.f, -1.f, 1.f }, 0);
	/*m_wpPointLightComponent.lock()->SetPointLightInfo({ 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.5f, 0.5f, 0.5f, 1.f }, { 0.f, 10.f, 0.f }, 75.f, 0);*/
	CActor::BeginPlay();
}

int32 CSunActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CSunActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CSunActor::Render()
{
	CActor::Render();
}

void CSunActor::EndPlay()
{
	CActor::EndPlay();
}

void CSunActor::Release()
{
	CActor::Release();
}