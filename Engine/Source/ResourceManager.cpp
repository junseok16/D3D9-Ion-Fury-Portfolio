#include "pch.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CResourceManager)

HRESULT CResourceManager::Initialize()
{
	// 디바이스 포인터를 불러옵니다.
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();

	// 텍스처 경로를 위해 메모리를 예약합니다.
	m_vecStrFilePaths[(int32)EResourceType::TEXTURE].reserve(1024);
	m_vecWstrFilePaths[(int32)EResourceType::TEXTURE].reserve(1024);

	// 사운드 경로를 위해 메모리를 예약합니다.
	m_vecStrFilePaths[(int32)EResourceType::SOUND].reserve(64);
	m_vecWstrFilePaths[(int32)EResourceType::SOUND].reserve(64);

	// 리소스 경로를 읽습니다.
	ReadTextureFilePaths(m_fsTexturePath);
	ReadSoundFilePaths(m_fsSoundPath);
	
	// 텍스처 포인터를 만듭니다.
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
		// 파일 경로에서 확장자를 제외한 파일의 이름만 추출합니다.
		size_t iCursor = wstrFilePath.find_last_of(L"\\/");

		wstring wstrFileNameExt = L"";
		if (iCursor != string::npos) { wstrFileNameExt = wstrFilePath.substr(iCursor + 1); }
		else { wstrFileNameExt = wstrFilePath; }

		iCursor = wstrFileNameExt.find_last_of(L".");
		
		// 파일의 확장자(.png)
		const wstring& wstrFileExtension = wstrFileNameExt.substr(iCursor + 1);
		
		// 파일의 이름("WhiteWall0")
		const wstring& wstrFileName = wstrFileNameExt.substr(0, iCursor);

		// png 확장자 파일인 경우
		if (wstrFileExtension == L"png" || wstrFileExtension == L"PNG")
		{
			ENSURE(D3DXCreateTextureFromFile(m_pD3DDevice9, wstrFilePath.c_str(), (LPDIRECT3DTEXTURE9*)&pD3DTexture));
			m_vecD3DTextures.push_back({ wstrFileName, pD3DTexture });
		}
		// dds 확장자 파일인 경우
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
