// default
#include "pch.h"
#include "GameManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CGameManager)

HRESULT CGameManager::Initialize()
{
	return S_OK;
}

void CGameManager::Release()
{
	m_upInstance.reset();
}
