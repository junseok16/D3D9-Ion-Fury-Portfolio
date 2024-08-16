#include "pch.h"
#include "MedKitActor.h"
using namespace std;

void CMedKitActor::Initialize()
{
	m_eSkillType = ESkillType::MEDKIT;
	m_iSkillNum = 1;
	CSkillActor::Initialize();
}

void CMedKitActor::BeginPlay()
{
	CSkillActor::BeginPlay();
}

int32 CMedKitActor::Update(const float& _fDeltaSeconds)
{
	return CSkillActor::Update(_fDeltaSeconds);
}

int32 CMedKitActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CSkillActor::LateUpdate(_fDeltaSeconds);
}

void CMedKitActor::Render()
{
	CSkillActor::Render();
}

void CMedKitActor::EndPlay()
{
	CSkillActor::EndPlay();
}

void CMedKitActor::Release()
{
	CSkillActor::Release();
}