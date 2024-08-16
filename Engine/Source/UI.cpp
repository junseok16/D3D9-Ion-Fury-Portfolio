#include "pch.h"
#include "UI.h"

#include "TextUIComponent.h"

using namespace std;

void CUI::Initialize()
{
	CActor::Initialize();
}

void CUI::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CUI::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CUI::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CUI::Render()
{
	CActor::Render();
}

void CUI::EndPlay()
{
	CActor::EndPlay();
}

void CUI::Release()
{
	CActor::Release();
}

void CUI::SetInitNumberUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextComponent, std::wstring _wstrText, const std::wstring& _wstrTextureFileName,
	const float& _iScaleX, const float& _iScaleY, const float& _iPositionX, const float& _iPositionY)
{
	int32 iSize = static_cast<int32>(_wstrText.length());

	_vecTextComponent.clear();
	_vecTextComponent.reserve(iSize);

	for (int32 i = 0; i < iSize; ++i)
	{
		std::wstring wstCombinedString = _wstrTextureFileName + std::to_wstring(i);

		_vecTextComponent.push_back(CreateActorComponent<CTextUIComponent>(wstCombinedString));
		_vecTextComponent.back().lock()->SetIsRootComponent(true);
		_vecTextComponent.back().lock()->SettingUserInterfaceInfo(_wstrTextureFileName, 0, 10, _wstrTextureFileName, EUserInterfaceType::STATIC);
		_vecTextComponent.back().lock()->SetComponentScale({ _iScaleX, _iScaleY, 0.f });
		_vecTextComponent.back().lock()->SetComponentLocalPosition({ _iPositionX + i * 36, _iPositionY, 0.f });
		_vecTextComponent.back().lock()->SetCurrentUI(0);

		WCHAR wcCurChar = _wstrText[i];

		switch (wcCurChar)
		{
		case '0':
			_vecTextComponent.back().lock()->SetCurrentUI(0);
			break;

		case '1':
			_vecTextComponent.back().lock()->SetCurrentUI(1);
			break;

		case '2':
			_vecTextComponent.back().lock()->SetCurrentUI(2);
			break;

		case '3':
			_vecTextComponent.back().lock()->SetCurrentUI(3);
			break;

		case '4':
			_vecTextComponent.back().lock()->SetCurrentUI(4);
			break;

		case '5':
			_vecTextComponent.back().lock()->SetCurrentUI(5);
			break;

		case '6':
			_vecTextComponent.back().lock()->SetCurrentUI(6);
			break;

		case '7':
			_vecTextComponent.back().lock()->SetCurrentUI(7);
			break;

		case '8':
			_vecTextComponent.back().lock()->SetCurrentUI(8);
			break;

		case '9':
			_vecTextComponent.back().lock()->SetCurrentUI(9);
			break;

		default:
			break;
		}
	}
}

void CUI::SetBeginPlayNumberUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextComponent, std::wstring _wstrText, const std::wstring& _wstrTextureFileName)
{
	int32 iSize = static_cast<int32>(_wstrText.length());

	for (int32 i = 0; i < iSize; ++i)
	{
		std::wstring wstCombinedString = _wstrTextureFileName + std::to_wstring(i);
		_vecTextComponent[i].lock()->AddUIState(wstCombinedString, 0, 10);
	}
}

void CUI::SetInitTextUI(
	std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextComponent,
	std::wstring _wstrText,
	std::wstring _wstrKey,
	const std::wstring& _wstrTextureFileName,
	const float& _iScaleX,
	const float& _iScaleY,
	const float& _iPositionX,
	const float& _iPositionY)
{
	int32 iSize = static_cast<int32>(_wstrText.length());
	
	_vecTextComponent.clear();
	_vecTextComponent.reserve(iSize);
	
	for (int32 i = 0; i < iSize; ++i)
	{
		wchar_t wcCurChar = _wstrText[i];
		int32 iCurIndex = static_cast<int32>(wcCurChar);

		if (iCurIndex >= 'A' && iCurIndex <= 'Z')
		{
			iCurIndex -= 'A';
		}
		else if (iCurIndex >= 'a' && iCurIndex <= 'z')
		{
			iCurIndex -= 'a';
		}
		else
		{
			iCurIndex = 26;
		}
		
		std::wstring wstCombinedString = _wstrKey + std::to_wstring(i);
		_vecTextComponent.push_back(CreateActorComponent<CTextUIComponent>(wstCombinedString));
		SetRootComponent(_vecTextComponent[i]);
		_vecTextComponent.back().lock()->SettingUserInterfaceInfo(_wstrTextureFileName, 0, 26, _wstrTextureFileName, EUserInterfaceType::STATIC);
		_vecTextComponent.back().lock()->SetComponentScale({ _iScaleX, _iScaleY, 0.f });
		_vecTextComponent.back().lock()->SetComponentLocalPosition({ _iPositionX + i * 13, _iPositionY, 0.f });
		_vecTextComponent.back().lock()->SetCurrentUI(iCurIndex);

		//WCHAR wcCurChar = _wstrText[i];
		//
		//switch (wcCurChar)
		//{
		//case 'a':
		//case 'A':
		//	_vecTextComponent.back().lock()->SetCurrentUI(0);
		//	break;
		//
		//case 'b':
		//case 'B':
		//	_vecTextComponent.back().lock()->SetCurrentUI(1);
		//	break;
		//
		//case 'c':
		//case 'C':
		//	_vecTextComponent.back().lock()->SetCurrentUI(2);
		//	break;
		//
		//case 'd':
		//case 'D':
		//	_vecTextComponent.back().lock()->SetCurrentUI(3);
		//	break;
		//
		//case 'e':
		//case 'E':
		//	_vecTextComponent.back().lock()->SetCurrentUI(4);
		//	break;
		//
		//case 'f':
		//case 'F':
		//	_vecTextComponent.back().lock()->SetCurrentUI(5);
		//	break;
		//
		//case 'g':
		//case 'G':
		//	_vecTextComponent.back().lock()->SetCurrentUI(6);
		//	break;
		//
		//case 'h':
		//case 'H':
		//	_vecTextComponent.back().lock()->SetCurrentUI(7);
		//	break;
		//
		//case 'i':
		//case 'I':
		//	_vecTextComponent.back().lock()->SetCurrentUI(8);
		//	break;
		//
		//case 'j':
		//case 'J':
		//	_vecTextComponent.back().lock()->SetCurrentUI(9);
		//	break;
		//
		//case 'k':
		//case 'K':
		//	_vecTextComponent.back().lock()->SetCurrentUI(10);
		//	break;
		//
		//case 'l':
		//case 'L':
		//	_vecTextComponent.back().lock()->SetCurrentUI(11);
		//	break;
		//
		//case 'm':
		//case 'M':
		//	_vecTextComponent.back().lock()->SetCurrentUI(12);
		//	break;
		//
		//case 'n':
		//case 'N':
		//	_vecTextComponent.back().lock()->SetCurrentUI(13);
		//	break;
		//
		//case 'o':
		//case 'O':
		//	_vecTextComponent.back().lock()->SetCurrentUI(14);
		//	break;
		//
		//case 'p':
		//case 'P':
		//	_vecTextComponent.back().lock()->SetCurrentUI(15);
		//	break;
		//
		//case 'q':
		//case 'Q':
		//	_vecTextComponent.back().lock()->SetCurrentUI(16);
		//	break;
		//
		//case 'r':
		//case 'R':
		//	_vecTextComponent.back().lock()->SetCurrentUI(17);
		//	break;
		//
		//case 's':
		//case 'S':
		//	_vecTextComponent.back().lock()->SetCurrentUI(18);
		//	break;
		//
		//case 't':
		//case 'T':
		//	_vecTextComponent.back().lock()->SetCurrentUI(19);
		//	break;
		//
		//case 'u':
		//case 'U':
		//	_vecTextComponent.back().lock()->SetCurrentUI(20);
		//	break;
		//
		//case 'v':
		//case 'V':
		//	_vecTextComponent.back().lock()->SetCurrentUI(21);
		//	break;
		//
		//case 'w':
		//case 'W':
		//	_vecTextComponent.back().lock()->SetCurrentUI(22);
		//	break;
		//
		//case 'x':
		//case 'X':
		//	_vecTextComponent.back().lock()->SetCurrentUI(23);
		//	break;
		//
		//case 'y':
		//case 'Y':
		//	_vecTextComponent.back().lock()->SetCurrentUI(24);
		//	break;
		//
		//case 'z':
		//case 'Z':
		//	_vecTextComponent.back().lock()->SetCurrentUI(25);
		//	break;
		//
		//default:
		//	_vecTextComponent.back().lock()->SetCurrentUI(26);
		//	break;
		//}
		//}

		//int32 iSize = static_cast<int32>(_wstrText.length());
		//
		//_vecTextComponent.clear();
		//_vecTextComponent.reserve(iSize);
		//
		//for (int32 i = 0; i < iSize; ++i)
		//{
		//	wchar_t wcCurChar = _wstrText[i];
		//	int32 iCurIndex = static_cast<int32>(wcCurChar);
		//
		//	if (iCurIndex >= 'A' && iCurIndex <= 'Z')
		//	{
		//		iCurIndex -= 'A';
		//	}
		//	else if (iCurIndex >= 'a' && iCurIndex <= 'z')
		//	{
		//		iCurIndex -= 'a';
		//	}
		//	else
		//	{
		//		iCurIndex = 26; 
		//	}
		//
		//	std::wstring wstCombinedString = _wstrKey + std::to_wstring(iCurIndex);
		//
		//	auto textComponent = CreateActorComponent<CTextUIComponent>(wstCombinedString);
		//	//textComponent.get()->SetIsRootComponent(true);
		//	SetRootComponent(textComponent);
		//	textComponent.get()->SettingUserInterfaceInfo(_wstrTextureFileName, 0, 26, _wstrTextureFileName, EUserInterfaceType::STATIC);
		//	textComponent.get()->SetComponentScale({ _iScaleX, _iScaleY, 0.f });
		//	textComponent.get()->SetComponentLocalPosition({ _iPositionX + i * 36, _iPositionY, 0.f });
		//	textComponent.get()->SetCurrentUI(iCurIndex);
		//
		//	_vecTextComponent.push_back(textComponent);
		//}
	}

}

void CUI::SetBeginPlayTextUI(std::vector<std::weak_ptr<CTextUIComponent>>& _vecTextComponent,
	std::wstring _wstrText, std::wstring _wstrKey, const std::wstring& _wstrTextureFileName)
{
	int32 iSize = static_cast<int32>(_wstrText.length());

	for (int32 i = 0; i < iSize; ++i)
	{
		std::wstring wstCombinedString = _wstrKey + std::to_wstring(i);
		_vecTextComponent[i].lock()->AddUIState(wstCombinedString, 0, 26);
	}
}