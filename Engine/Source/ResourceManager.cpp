#include "pch.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CResourceManager)

HRESULT CResourceManager::Initialize()
{
	// ����̽� �����͸� �ҷ��ɴϴ�.
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();

	// �ؽ�ó ��θ� ���� �޸𸮸� �����մϴ�.
	m_vecStrFilePaths[(int32)EResourceType::TEXTURE].reserve(1024);
	m_vecWstrFilePaths[(int32)EResourceType::TEXTURE].reserve(1024);

	// ���� ��θ� ���� �޸𸮸� �����մϴ�.
	m_vecStrFilePaths[(int32)EResourceType::SOUND].reserve(64);
	m_vecWstrFilePaths[(int32)EResourceType::SOUND].reserve(64);

	// ���ҽ� ��θ� �н��ϴ�.
	ReadTextureFilePaths(m_fsTexturePath);
	ReadSoundFilePaths(m_fsSoundPath);
	
	// �ؽ�ó �����͸� ����ϴ�.
	CreateD3DTextureFromFile();
	return S_OK;
}

void CResourceManager::ReadTextureFilePaths(const std::filesystem::path& _fsFilePath)
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(m_fsTexturePath))
	{
		if (filesystem::is_regular_file(fsEntry))
		{
			m_vecStrFilePaths[(int32)EResourceType::TEXTURE].push_back(fsEntry.path().generic_string());
			m_vecWstrFilePaths[(int32)EResourceType::TEXTURE].push_back(fsEntry.path());
		}
	}
}

void CResourceManager::ReadSoundFilePaths(const std::filesystem::path& _fsFilePath)
{
	for (const filesystem::directory_entry& fsEntry : filesystem::recursive_directory_iterator(_fsFilePath))
	{
		if (filesystem::is_regular_file(fsEntry))
		{
			m_vecStrFilePaths[(int32)EResourceType::SOUND].push_back(fsEntry.path().generic_string());
			m_vecWstrFilePaths[(int32)EResourceType::SOUND].push_back(fsEntry.path());
		}
	}
}

void CResourceManager::CreateD3DTextureFromFile()
{
	IDirect3DBaseTexture9* pD3DTexture = nullptr;

	for (const auto& wstrFilePath : m_vecWstrFilePaths[(int32)EResourceType::TEXTURE])
	{
		// ���� ��ο��� Ȯ���ڸ� ������ ������ �̸��� �����մϴ�.
		size_t iCursor = wstrFilePath.find_last_of(L"\\/");

		wstring wstrFileNameExt = L"";
		if (iCursor != string::npos) { wstrFileNameExt = wstrFilePath.substr(iCursor + 1); }
		else { wstrFileNameExt = wstrFilePath; }

		iCursor = wstrFileNameExt.find_last_of(L".");
		
		// ������ Ȯ����(.png)
		const wstring& wstrFileExtension = wstrFileNameExt.substr(iCursor + 1);
		
		// ������ �̸�("WhiteWall0")
		const wstring& wstrFileName = wstrFileNameExt.substr(0, iCursor);

		// png Ȯ���� ������ ���
		if (wstrFileExtension == L"png" || wstrFileExtension == L"PNG")
		{
			ENSURE(D3DXCreateTextureFromFile(m_pD3DDevice9, wstrFilePath.c_str(), (LPDIRECT3DTEXTURE9*)&pD3DTexture));
			m_vecD3DTextures.push_back({ wstrFileName, pD3DTexture });
		}
		// dds Ȯ���� ������ ���
		else if (wstrFileExtension == L"dds" || wstrFileExtension == L"DDS")
		{
			ENSURE(D3DXCreateCubeTextureFromFile(m_pD3DDevice9, wstrFilePath.c_str(), (LPDIRECT3DCUBETEXTURE9*)&pD3DTexture));
			m_vecD3DCubeTextures.push_back({ wstrFileName, pD3DTexture });
		}
	}
}

IDirect3DCubeTexture9* CResourceManager::FindD3DCubeTexture(std::wstring _wstrFileName)
{
	for (const auto& pair : m_vecD3DCubeTextures)
	{
		if (pair.first == _wstrFileName) { return (IDirect3DCubeTexture9*)pair.second; break; }
	}
	return nullptr;
}

IDirect3DTexture9* CResourceManager::FindD3DTexture(std::wstring _wstrFileName)
{
	for (const auto& pair : m_vecD3DTextures)
	{
		if (pair.first == _wstrFileName) { return (IDirect3DTexture9*)pair.second; break; }
	}
	return nullptr;
}

void CResourceManager::Release()
{
	for (auto& pair : m_vecD3DCubeTextures)
	{
		if (pair.second) { pair.second->Release(); pair.second = nullptr; }
	}
	m_vecD3DCubeTextures.clear();

	for (auto& pair : m_vecD3DTextures)
	{
		if (pair.second) { pair.second->Release(); pair.second = nullptr; }
	}
	m_vecD3DTextures.clear();

	m_upInstance.reset();
}
