#pragma once

class CActor;

struct NonDestroyData
{
	// 장전된 발 수, 보유한 탄 수
	std::pair<int32, int32> prLoverboy = { 6, 100 };
	std::pair<int32, int32> prPenetrator = { 40, 100 };
	std::pair<int32, int32> prDisperser = { 6, 100 };
	std::pair<int32, int32> prChainGun = { 0, 200 };

	// 플레이어
	float fCurHp = 100.0f;
	float fCurArmor = 0.0f;
	float fMaxArmor = 0.0;

	// 스킬
	bool bBlinkEnable = true;
	bool bRecallEnable = true;
	bool bSandevistanEnable = true;

	// 무기
	bool bPenetratorEnable = true;
	bool bDisperserEnable = true;
	bool bChainGunEnable = true;
};

class CGameManager final
{
	DECLARE_SINGLETON(CGameManager)

/********************
	Framework
********************/
public:
	HRESULT Initialize();
	void Release();

/********************
	Methods
********************/
public:
	void SetNonDestroyData(NonDestroyData _tNonDestroyData) { m_tNonDestroyData = _tNonDestroyData; }

	NonDestroyData GetNonDestroyData() const { return m_tNonDestroyData; }

private:
	// 다음 레벨로 복사할 데이터
	NonDestroyData m_tNonDestroyData;
};

