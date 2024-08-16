#include "pch.h"
#include "RecoveryActor.h"
using namespace std;

void CRecoveryActor::Initialize()
{
	m_eItemType = EItemType::RECOVERY;
	CItem::Initialize();
}

void CRecoveryActor::BeginPlay()
{
	CItem::BeginPlay();
}

int32 CRecoveryActor::Update(const float& _fDeltaSeconds)
{
	return CItem::Update(_fDeltaSeconds);
}

int32 CRecoveryActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CItem::LateUpdate(_fDeltaSeconds);
}

void CRecoveryActor::Render()
{
	CItem::Render();
}

void CRecoveryActor::EndPlay()
{
	CItem::EndPlay();
}

void CRecoveryActor::Release()
{
	CItem::Release();
}
