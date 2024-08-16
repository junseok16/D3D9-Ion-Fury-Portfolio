#include "pch.h"
#include "RadarActor.h"
using namespace std;

void CRadarActor::Initialize()
{
	m_eSkillType = ESkillType::RADAR;
	m_iSkillNum = 3;
	CSkillActor::Initialize();
}

void CRadarActor::BeginPlay()
{
	CSkillActor::BeginPlay();
}

int32 CRadarActor::Update(const float& _fDeltaSeconds)
{
	return CSkillActor::Update(_fDeltaSeconds);
}

int32 CRadarActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CSkillActor::LateUpdate(_fDeltaSeconds);
}

void CRadarActor::Render()
{
	CSkillActor::Render();
}

void CRadarActor::EndPlay()
{
	CSkillActor::EndPlay();
}

void CRadarActor::Release()
{
	CSkillActor::Release();
}