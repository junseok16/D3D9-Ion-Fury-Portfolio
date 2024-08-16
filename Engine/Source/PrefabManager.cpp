#include "pch.h"
#include "PrefabManager.h"
#include "DeviceManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CPrefabManager)

int32 CPrefabManager::m_iID = 0;

HRESULT CPrefabManager::Initialize()
{
    return S_OK;
}

std::shared_ptr<PrefabData> CPrefabManager::FindPrefabData(std::wstring _wstrPrefabName)
{
	for (const auto& pair : m_vecPrefabData) { if (pair.first == _wstrPrefabName) { return pair.second; } }
	return nullptr;
}

void CPrefabManager::AddPrefabData(std::wstring _wstrPrefabName, std::shared_ptr<PrefabData> _spPrefabData)
{
	if (FindPrefabData(_wstrPrefabName)) { return; }
	m_vecPrefabData.push_back({ _wstrPrefabName, _spPrefabData });
}

void CPrefabManager::RemovePrefabData(std::wstring _wstrPrefabName)
{
	for (auto iter = m_vecPrefabData.begin(); iter != m_vecPrefabData.end(); ++iter)
	{
		if ((*iter).first == _wstrPrefabName)
		{
			(*iter).second.reset();
			m_vecPrefabData.erase(iter);
			break;
		}
	}
}

void CPrefabManager::ModifyPrefabData(std::wstring _wstrPrefabName)
{

}

void CPrefabManager::Release()
{
	for (auto& pair : m_vecPrefabData) { if (pair.second) { pair.second.reset(); } }
	m_vecPrefabData.clear();
	m_upInstance.reset();
}