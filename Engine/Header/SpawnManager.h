#pragma once

struct SpawnData
{
	// ���� �̸�
	char m_chName[64] = { NULL };

	// ���� Ʈ������
	float m_fActorTranslate[3] = { 0.0f, 0.0f, 0.0f };				// ��ġ
	float m_fActorRotate[3] = { 0.0f, 0.0f, 0.0f };					// ȸ��
	float m_fActorScale[3] = { 1.0f, 1.0f, 1.0f };					// ũ��

	/* uv�� ������ �� �ֽ��ϴ�. */
	float m_fScaleU = 1.0f;
	float m_fScaleV = 1.0f;

	// �ݶ��̴� ������Ʈ Ʈ������
	float m_fColliderComponentTranslate[3] = { 0.0f, 0.0f, 0.0f };	// ��ġ
	float m_fColliderComponentRotate[3] = { 0.0f, 0.0f, 0.0f };		// ȸ��
	float m_fColliderComponentScale[3] = { 1.0f, 1.0f, 1.0f };		// ũ��
};

class CSpawnManager final
{
	DECLARE_SINGLETON(CSpawnManager)

public:
	HRESULT Initialize();
	void Release();

public:
	std::vector<std::pair<std::string, std::shared_ptr<SpawnData>>>& GetSpawnData() { return m_vecSpawnData; }

public:
	std::shared_ptr<SpawnData> FindSpawnData(std::string _strPrefabName);
	void AddSpawnData(std::string _strPrefabName, std::shared_ptr<SpawnData> _spSpawnData);
	void ModifySpawnData(std::string _strPrefabName);
	void RemoveSpawnData(std::string _strPrefabName);

private:
	// ���� ������
	std::vector<std::pair<std::string, std::shared_ptr<SpawnData>>> m_vecSpawnData;

public:
	// ���� �ĺ���
	static int32 m_iID;
};

