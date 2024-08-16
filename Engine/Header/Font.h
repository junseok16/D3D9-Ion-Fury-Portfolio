#pragma once

class CFont final
{
private:
	explicit CFont() = default;
	~CFont() = default;

public:
	HRESULT Initialize(const wchar* _pFontType, const uint32& _iWidth, const uint32& _iHeight, const uint32& _iWeight);
	void Render(const wchar* _pCharacter, const FVector2* _pPosition, D3DXCOLOR _tColor);
	void Release();

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice9 = nullptr;
	LPD3DXSPRITE m_pD3DSprite = nullptr;
	LPD3DXFONT m_pD3DFont = nullptr;
};

