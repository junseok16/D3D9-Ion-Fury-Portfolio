#pragma once

class CResourceManager final
{
	DECLARE_SINGLETON(CResourceManager)

/********************
	Framework
********************/
public:
	HRESULT Initialize();
	void Release();

/********************
	Methods
********************/
private:
	void CreateD3DTextureFromFile();

	void ReadTextureFilePaths(const std::filesystem::path& _fsFilePath);
	
	void ReadSoundFilePaths(const std::filesystem::path& _fsFilePath);

public:
	IDirect3DTexture9* FindD3DTexture(std::wstring _wstrFileName);

	IDirect3DCubeTexture9* FindD3DCubeTexture(std::wstring _wstrFileName);

/********************
	Getter/Setter
********************/
public:
	const std::vector<std::string>& GetStrFilePaths(EResourceType _eResourceType) { return m_vecStrFilePaths[(int32)_eResourceType]; }

	const std::vector<std::wstring>& GetWstrFilePaths(EResourceType _eResourceType) { return m_vecWstrFilePaths[(int32)_eResourceType]; }

	const std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>>& GetD3DTextures() { return m_vecD3DTextures; }

	const std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>>& GetD3DCubeTextures() { return m_vecD3DCubeTextures; }

	const std::wstring GetTexturePath() const { return m_fsTexturePath; }
	
	const std::wstring GetSoundPath() const { return m_fsSoundPath; }
	
	const std::wstring GetDataPath() const { return m_fsDataPath; }

/********************
	Data Members
********************/
private:
	// 디바이스 포인터
	LPDIRECT3DDEVICE9 m_pD3DDevice9 = nullptr;

	// 텍스처 폴더 경로
	std::filesystem::path m_fsTexturePath = L"..\\..\\Resource\\Textures\\";
	
	// 사운드 폴더 경로
	std::filesystem::path m_fsSoundPath = L"..\\..\\Resource\\Sounds\\";
	
	// 데이터 폴더 경로
	std::filesystem::path m_fsDataPath = L"..\\..\\Resource\\Data\\";



	// 모든 파일의 상대 경로
	std::vector<std::string> m_vecStrFilePaths[(int32)EResourceType::ENUM_END];
	
	// 모든 파일의 상대 경로
	std::vector<std::wstring> m_vecWstrFilePaths[(int32)EResourceType::ENUM_END];



	// 텍스처 포인터들
	std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>> m_vecD3DTextures;

	// 큐브 텍스처 포인터들
	std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>> m_vecD3DCubeTextures;
};

