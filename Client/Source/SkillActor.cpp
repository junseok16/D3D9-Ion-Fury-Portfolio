#include "pch.h"
#include "SkillActor.h"
using namespace std;

void CSkillActor::Initialize()
{
	m_eItemType = EItemType::SKILL;
	CItem::Initialize();
}

void CSkillActor::BeginPlay()
{
	CItem::BeginPlay();
}

int32 CSkillActor::Update(const float& _fDeltaSeconds)
{
	return CItem::Update(_fDeltaSeconds);
}

int32 CSkillActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CItem::LateUpdate(_fDeltaSeconds);
}

void CSkillActor::Render()
{
	CItem::Render();
}

void CSkillActor::EndPlay()
{
	CItem::EndPlay();
}

void CSkillActor::Release()
{
	CItem::Release();
}