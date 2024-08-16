#pragma once

class CFont;

class CFontManager final
{
	DECLARE_SINGLETON(CFontManager)

public:
	HRESULT Initialize();
	void Render();
	void Release();

public:

private:
	std::unordered_map<std::wstring, CFont*> m_umapFonts;
};

