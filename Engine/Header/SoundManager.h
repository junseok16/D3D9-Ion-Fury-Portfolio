#pragma once

class CSoundManager final
{
	DECLARE_SINGLETON(CSoundManager)

public:
	HRESULT Initialize();
	void Release();

public:
	/* Ȥ�� �𸣴� ���ܵ�
	//void PlaySound(TCHAR* _pSoundKey, ESoundType _eSoundType, float _fVolume);
	//void PlayBGMLoop(TCHAR* _pSoundKey, float _fVolume);
	*/
	void PlaySoundEx(std::string _strSoundKey, ESoundType _eSoundType, float _fVolume);
	void PlayBGMLoop(std::string _strSoundKey, float _fVolume);
	void StopSound(ESoundType _eSoundType);
	void StopAll();
	void SetChannelVolume(ESoundType _eSoundType, float _fVolume);

private:
	//void LoadSoundFile();
	void LoadSoundFiles(std::string _strPath);

private:
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pFmodSystem;

	//FMOD::Syste

	// ���� ���ҽ� ������ ���� ��ü 
	std::unordered_map<WCHAR*, FMOD_SOUND*> m_umapFmodSound;

	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pFmodChannel[(int32)ESoundType::ENUM_END];
};


