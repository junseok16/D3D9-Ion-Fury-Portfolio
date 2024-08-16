#include "pch.h"
#include "EditorLevel.h"
#include "Actor.h"
#include "CubeMeshComponent.h"
using namespace std;

void CEditorLevel::Initialize()
{
	CLevel::Initialize();
}

void CEditorLevel::BeginPlay()
{
	CLevel::BeginPlay();
}

int32 CEditorLevel::Update(const float& _fDeltaSeconds)
{
	return CLevel::Update(_fDeltaSeconds);
}

int32 CEditorLevel::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CEditorLevel::Render()
{
	CLevel::Render();
}

void CEditorLevel::EndPlay()
{
	CLevel::EndPlay();
}

void CEditorLevel::Release()
{
	CLevel::Release();
}
