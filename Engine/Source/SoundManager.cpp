#include "pch.h"
#include "SoundManager.h"

using namespace std;

IMPLEMENT_SINGLETON(CSoundManager)

HRESULT CSoundManager::Initialize()
{
	// ���带 ����ϴ� ��ǥ��ü�� �����ϴ� �Լ�
	FMOD_System_Create(&m_pFmodSystem, FMOD_VERSION);

	// 1. �ý��� ������, 2. ����� ����ä�� �� , �ʱ�ȭ ���) 
	FMOD_System_Init(m_pFmodSystem, 32, FMOD_INIT_NORMAL, NULL);

	//LoadSoundFile();
	LoadSoundFiles("../../Resource/Sounds");

	return S_OK;
}
void CSoundManager::Release()
{
	for (auto& Mypair : m_umapFmodSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_umapFmodSound.clear();

	FMOD_System_Release(m_pFmodSystem);
	FMOD_System_Close(m_pFmodSystem);
	m_upInstance.reset();
}

void CSoundManager::PlaySoundEx(std::string _strSoundKey, ESoundType _eSoundType, float _fVolume)
{
	std::string strSoundKey = _strSoundKey + ".ogg";

	WCHAR tSoundKey[128] = L"";    // ��ȯ��ų ���ڿ��� ����
	size_t sLength = 0, sConvertedChars = 0; // ���� ���ڿ� ����, ��ȯ�� ���ڿ� ����

	sLength = strlen(strSoundKey.c_str()) + 1;  // ��ȯ��ų ���ڿ��� ���̸� ����
	mbstowcs_s(&sConvertedChars, tSoundKey, sLength, strSoundKey.c_str(), _TRUNCATE); // ��ȯ ��, ��ȯ�� _strSoundKey�� WCHAR tSoundKey[128] = L""; ���⿡ ���� �־���

	// ������ �ش� Ű���� WCHAR ������ ��ȯ �����ִ� ����

	std::unordered_map<WCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_umapFmodSound.begin(), m_umapFmodSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(tSoundKey, iter.first);
		});
	if (iter == m_umapFmodSound.end()) { return; }

	FMOD_System_PlaySound(m_pFmodSystem, iter->second, FALSE, FALSE, &m_pFmodChannel[(int32)_eSoundType]);
	FMOD_Channel_SetVolume(m_pFmodChannel[(int32)_eSoundType], _fVolume);
	FMOD_System_Update(m_pFmodSystem);
}

void CSoundManager::PlayBGMLoop(std::string _strSoundKey, float _fVolume)
{
	std::string strSoundKey = _strSoundKey + ".ogg";

	WCHAR tSoundKey[128] = L"";    // ��ȯ��ų ���ڿ��� ����
	size_t sLength = 0, sConvertedChars = 0; // ���� ���ڿ� ����, ��ȯ�� ���ڿ� ����

	sLength = strlen(strSoundKey.c_str()) + 1;  // ��ȯ��ų ���ڿ��� ���̸� ����
	mbstowcs_s(&sConvertedChars, tSoundKey, sLength, strSoundKey.c_str(), _TRUNCATE); // ��ȯ ��, ��ȯ�� _pSoundKey�� TCHAR tSoundKey[128] = L""; ���⿡ ���� �־���

	// ������ �ش� Ű���� WCHAR ������ ��ȯ �����ִ� ����

	std::unordered_map<WCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_umapFmodSound.begin(), m_umapFmodSound.end(), [&](auto& iter)->bool
		{
			return !lstrcmp(tSoundKey, iter.first);
		});
	if (iter == m_umapFmodSound.end()) { return; }


	FMOD_System_PlaySound(m_pFmodSystem, iter->second, FALSE, FALSE, &m_pFmodChannel[(int32)ESoundType::BGM]);
	FMOD_Channel_SetMode(m_pFmodChannel[(int32)ESoundType::BGM], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pFmodChannel[(int32)ESoundType::BGM], _fVolume);
	FMOD_System_Update(m_pFmodSystem);
}

void CSoundManager::StopSound(ESoundType _eSoundType)
{
	FMOD_Channel_Stop(m_pFmodChannel[(int32)_eSoundType]);
}

void CSoundManager::StopAll()
{
	for (int32 i = 0; i < (int32)ESoundType::ENUM_END; ++i)
		FMOD_Channel_Stop(m_pFmodChannel[i]);
}

void CSoundManager::SetChannelVolume(ESoundType _eSoundType, float _fVolume)
{
	FMOD_Channel_SetVolume(m_pFmodChannel[(int32)_eSoundType], _fVolume);
	FMOD_System_Update(m_pFmodSystem);
}

//void CSoundManager::LoadSoundFile()
//{
//	// _finddata_t : <io.h>���� �����ϸ� ���� ������ �����ϴ� ����ü
//	_finddata_t fd;
//
//	// _findfirst : <io.h>���� �����ϸ� ����ڰ� ������ ��� ������ ���� ù ��° ������ ã�� �Լ�
//	intptr_t handle = _findfirst("../../Resource/Sounds/*.*", &fd);
//
//	if (handle == -1)
//		return;
//
//	int32 iResult = 0;
//
//	char szCurPath[128] = "../../Resource/Sounds/";
//	char szFullPath[128] = "";
//
//	while (iResult != -1)
//	{
//		strcpy_s(szFullPath, szCurPath);
//
//		// "../Sound/Success.wav"
//		strcat_s(szFullPath, fd.name);
//
//		FMOD_SOUND* pSound = nullptr;
//
//		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pFmodSystem, szFullPath, FMOD_DEFAULT, 0, &pSound);
//
//		if (eRes == FMOD_OK)
//		{
//			size_t iLength = strlen(fd.name) + 1;
//
//			WCHAR* pSoundKey = new WCHAR[(int32)iLength];
//			ZeroMemory(pSoundKey, sizeof(WCHAR) * (int32)iLength);
//
//			// �ƽ�Ű �ڵ� ���ڿ��� �����ڵ� ���ڿ��� ��ȯ�����ִ� �Լ�
//			MultiByteToWideChar(CP_ACP, 0, fd.name, (int32)iLength, pSoundKey, (int32)iLength);
//
//			m_umapFmodSound.emplace(pSoundKey, pSound);
//		}
//		//_findnext : <io.h>���� �����ϸ� ���� ��ġ�� ������ ã�� �Լ�, ���̻� ���ٸ� -1�� ����
//		iResult = _findnext(handle, &fd);
//	}
//
//	FMOD_System_Update(m_pFmodSystem);
//
//	_findclose(handle);
//}

void CSoundManager::LoadSoundFiles(std::string _strPath)
{
	_finddata_t fd;
	// �־��� ��ο��� ��ġ�ϴ� ������ �ִ��� ������ ã�� 
	intptr_t handle = _findfirst((_strPath + "/*.*").c_str(), &fd);

	// ���ǿ� ���� �ʴٸ� -1�� ����
	if (handle == -1) { return; }

	int32 iResult = 0;

	while (iResult != -1)
	{
		// attrib�� ���� �Ǵ� ���丮�� �Ӽ��� ��Ÿ����, _A_SUBDIR�� ���丮�� ��Ÿ���ϴ�. ��, fd.attrib�� ���丮�̸� true
		if (fd.attrib & _A_SUBDIR)
		{
			if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0)
			{
				// ���� ��� + ���ο� ���� �̸�
				std::string strNewPath = _strPath + "/" + fd.name;
				// ��������� ���� Ž��
				LoadSoundFiles(strNewPath.c_str());
			}
		}
		else
		{
			std::string strFullPath = _strPath + "/" + fd.name;
			FMOD_SOUND* pSound = nullptr;
			FMOD_RESULT eRes = FMOD_System_CreateSound(m_pFmodSystem, strFullPath.c_str(), FMOD_DEFAULT, 0, &pSound);

			if (eRes == FMOD_OK)
			{
				size_t iLength = strlen(fd.name) + 1;
				WCHAR* pSoundKey = new WCHAR[(int32)iLength];
				ZeroMemory(pSoundKey, sizeof(WCHAR) * (int32)iLength);
				MultiByteToWideChar(CP_ACP, 0, fd.name, (int32)iLength, pSoundKey, (int32)iLength);
				m_umapFmodSound.emplace(pSoundKey, pSound);
			}
		}
		iResult = _findnext(handle, &fd);
	}
	FMOD_System_Update(m_pFmodSystem);

	_findclose(handle);
}
