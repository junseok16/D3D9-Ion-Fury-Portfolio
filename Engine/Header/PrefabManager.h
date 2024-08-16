#pragma once

struct PrefabData
{
	char m_chName[64] = { NULL };												// 이름
	EMeshType m_eMeshType = EMeshType::ENUM_END;								// 메시 타입

	char m_chFileName[64] = { NULL };											// 파일 이름
	char m_chFilePath[256] = { NULL };											// 파일 경로
	int32 m_iBeginIndex = 0;													// 멀티 텍스처 시작 인덱스
	int32 m_iEndIndex = 0;														// 멀티 텍스처 끝 인덱스

	EColliderType m_eColliderType = EColliderType::NONE;						// 콜라이더 타입
	ECollisionLayerType m_eCollisionLayerType = ECollisionLayerType::ENUM_END;	// 콜리전 레이어 타입
	int32 m_iCollisionLayer = 0x0000'0000;										// 콜리전 레이어

	bool m_bMobility = false;													// 모빌리티
	ERenderType m_eRenderType = ERenderType::NON_ALPHA;							// 렌더 타입
};

class CPrefabManager
{
	DECLARE_SINGLETON(CPrefabManager)

/********************
	Framework
********************/
public:
	HRESULT Initialize();
	void Release();

/********************
	Getter/Setter
********************/
public:
	const std::vector<std::pair<std::wstring, std::shared_ptr<PrefabData>>>& GetPrefabData() { return m_vecPrefabData; }

/********************
	Methods
********************/
public:
	std::shared_ptr<PrefabData> FindPrefabData(std::wstring _wstrPrefabName);
	void AddPrefabData(std::wstring _wstrPrefabName, std::shared_ptr<PrefabData> _spPrefabData);
	void RemovePrefabData(std::wstring _wstrPrefabName);
	void ModifyPrefabData(std::wstring _wstrPrefabName);

/********************
	Data Members
********************/
private:
	// 프리팹 데이터
	std::vector<std::pair<std::wstring, std::shared_ptr<PrefabData>>> m_vecPrefabData;

public:
	// 프리팹 식별자
	static int32 m_iID;
};

