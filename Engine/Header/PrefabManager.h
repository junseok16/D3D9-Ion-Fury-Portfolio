#pragma once

struct PrefabData
{
	char m_chName[64] = { NULL };												// �̸�
	EMeshType m_eMeshType = EMeshType::ENUM_END;								// �޽� Ÿ��

	char m_chFileName[64] = { NULL };											// ���� �̸�
	char m_chFilePath[256] = { NULL };											// ���� ���
	int32 m_iBeginIndex = 0;													// ��Ƽ �ؽ�ó ���� �ε���
	int32 m_iEndIndex = 0;														// ��Ƽ �ؽ�ó �� �ε���

	EColliderType m_eColliderType = EColliderType::NONE;						// �ݶ��̴� Ÿ��
	ECollisionLayerType m_eCollisionLayerType = ECollisionLayerType::ENUM_END;	// �ݸ��� ���̾� Ÿ��
	int32 m_iCollisionLayer = 0x0000'0000;										// �ݸ��� ���̾�

	bool m_bMobility = false;													// �����Ƽ
	ERenderType m_eRenderType = ERenderType::NON_ALPHA;							// ���� Ÿ��
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
	// ������ ������
	std::vector<std::pair<std::wstring, std::shared_ptr<PrefabData>>> m_vecPrefabData;

public:
	// ������ �ĺ���
	static int32 m_iID;
};

