#include "pch.h"
#include "Font.h"

#include "DeviceManager.h"
using namespace std;

HRESULT CFont::Initialize(const wchar* _pFontType, const uint32& _iWidth, const uint32& _iHeight, const uint32& _iWeight)
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_pD3DDevice9->AddRef();

	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESC));

	fontDesc.CharSet = HANGEUL_CHARSET;
	lstrcpy(fontDesc.FaceName, _pFontType);

	fontDesc.Width = _iWidth;
	fontDesc.Height = _iHeight;
	fontDesc.Weight = _iWeight;

	ENSURE(D3DXCreateFontIndirect(m_pD3DDevice9, &fontDesc, &m_pD3DFont));
	ENSURE(D3DXCreateSprite(m_pD3DDevice9, &m_pD3DSprite));

	return S_OK;
}

void CFont::Render(const wchar* _pString, const FVector2* _pPosition, D3DXCOLOR _tColor)
{
	RECT rc{ static_cast<int32>(_pPosition->x), static_cast<int32>(_pPosition->y) };

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pD3DFont->DrawTextW(m_pD3DSprite, _pString, lstrlen(_pString), &rc, DT_NOCLIP, _tColor);
	m_pD3DSprite->End();
}

void CFont::Release()
{
	m_pD3DFont->Release();
	m_pD3DSprite->Release();
	m_pD3DDevice9->Release();
}
