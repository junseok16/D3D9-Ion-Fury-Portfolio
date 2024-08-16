#include "pch.h"
#include "SpawnManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CSpawnManager)

int32 CSpawnManager::m_iID = 0;

HRESULT CSpawnManager::Initialize()
{
	return S_OK;
}

std::shared_ptr<SpawnData> CSpawnManager::FindSpawnData(std::string _strPrefabName)
{
	for (const auto& pair : m_vecSpawnData)
	{
		if (pair.first == _strPrefabName) { return pair.second; }
	}

	return nullptr;
}

void CSpawnManager::AddSpawnData(std::string _strPrefabName, std::shared_ptr<SpawnData> _spSpawnData)
{
	if (!FindSpawnData(_strPrefabName))
	{
		m_vecSpawnData.push_back({ _strPrefabName, _spSpawnData });
	}
}

void CSpawnManager::RemoveSpawnData(std::string _strPrefabName)
{
	for (auto iter = m_vecSpawnData.begin(); iter != m_vecSpawnData.end(); ++iter)
	{
		if ((*iter).first == _strPrefabName)
		{
			(*iter).second.reset();
			m_vecSpawnData.erase(iter);
			break;
		}
	}
}

void CSpawnManager::ModifySpawnData(std::string _strPrefabName)
{

}

void CSpawnManager::Release()
{
	for (auto& pair : m_vecSpawnData) { if (pair.second) { pair.second.reset(); } }
	m_vecSpawnData.clear();
	m_upInstance.reset();
}