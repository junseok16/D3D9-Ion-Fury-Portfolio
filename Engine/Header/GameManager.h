#pragma once

class CActor;

struct NonDestroyData
{
	// ������ �� ��, ������ ź ��
	std::pair<int32, int32> prLoverboy = { 6, 100 };
	std::pair<int32, int32> prPenetrator = { 40, 100 };
	std::pair<int32, int32> prDisperser = { 6, 100 };
	std::pair<int32, int32> prChainGun = { 0, 200 };

	// �÷��̾�
	float fCurHp = 100.0f;
	float fCurArmor = 0.0f;
	float fMaxArmor = 0.0;

	// ��ų
	bool bBlinkEnable = true;
	bool bRecallEnable = true;
	bool bSandevistanEnable = true;

	// ����
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
	// ���� ������ ������ ������
	NonDestroyData m_tNonDestroyData;
};

