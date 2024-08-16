#pragma once

struct SpawnData
{
	// 액터 이름
	char m_chName[64] = { NULL };

	// 액터 트랜스폼
	float m_fActorTranslate[3] = { 0.0f, 0.0f, 0.0f };				// 위치
	float m_fActorRotate[3] = { 0.0f, 0.0f, 0.0f };					// 회전
	float m_fActorScale[3] = { 1.0f, 1.0f, 1.0f };					// 크기

	/* uv를 변경할 수 있습니다. */
	float m_fScaleU = 1.0f;
	float m_fScaleV = 1.0f;

	// 콜라이더 컴포넌트 트랜스폼
	float m_fColliderComponentTranslate[3] = { 0.0f, 0.0f, 0.0f };	// 위치
	float m_fColliderComponentRotate[3] = { 0.0f, 0.0f, 0.0f };		// 회전
	float m_fColliderComponentScale[3] = { 1.0f, 1.0f, 1.0f };		// 크기
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
	// 스폰 데이터
	std::vector<std::pair<std::string, std::shared_ptr<SpawnData>>> m_vecSpawnData;

public:
	// 스폰 식별자
	static int32 m_iID;
};

