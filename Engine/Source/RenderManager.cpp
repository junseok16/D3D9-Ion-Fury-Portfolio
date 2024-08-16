#include "pch.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "Actor.h"
#include "CameraComponent.h"
using namespace std;

IMPLEMENT_SINGLETON(CRenderManager)

HRESULT CRenderManager::Initialize(bool _bEditor)
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_bEditor = _bEditor;

	if (_bEditor) { m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); }
	else { m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); }
	
	m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice9->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	D3DMATERIAL9 tMaterial;

	ZeroMemory(&tMaterial, sizeof(D3DMATERIAL9));

	tMaterial.Diffuse = { 1.f, 1.f, 1.f, 1.f };	// ���ݻ籤
	tMaterial.Ambient = { 1.f, 1.f, 1.f, 1.f };	// ȯ�汤
	tMaterial.Specular = { 1.f, 1.f, 1.f, 1.f };// ���ݻ籤(���̴� ���� ������ �Ⱦ�, �⺻������ ��Ȱ��ȭ)
	tMaterial.Emissive = { 0.f, 0.f, 0.f, 0.f };// �� �߻�(���� �ȹ޾Ƶ� ȥ�ڼ� ����, �ֺ��� ������� ����)
	tMaterial.Power = 0;		// ���ݻ籤�� ��ī�ο� ����, ���������� ���̶���Ʈ ����. ���ݻ籤�� ��Ȱ��ȭ�� ���� 0.f

	m_pD3DDevice9->SetMaterial(&tMaterial);
	return S_OK;
}

void CRenderManager::Render()
{
	// ���� ������ ���͸� �����մϴ�.
	if (!m_bEditor)
	{
		// ���� ��, ���� ���
		ENSURE(m_pD3DDevice9->SetTransform(D3DTS_VIEW, &(m_wpCurCameraComponent.lock()->GetPersViewMatrix())));
		ENSURE(m_pD3DDevice9->SetTransform(D3DTS_PROJECTION, &(m_wpCurCameraComponent.lock()->GetPersProjMatrix())));
	}

	// ������� ���� �ӽ÷� �ø����� �ʽ��ϴ�.
	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	if (m_bEditor) { m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); }
	else { m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE); }

	RenderNonAlpha();
	RenderAlphaTest();
	RenderAlphaBlend();

	if (!m_bEditor) { m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); }

	// ������� ���� �ӽ÷� �ø����� �ʽ��ϴ�.
	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���� ������ ���͸� �����մϴ�.
	if (!m_bEditor)
	{
		// ���� ��, ���� ���
		ENSURE(m_pD3DDevice9->SetTransform(D3DTS_VIEW, &(m_wpCurCameraComponent.lock()->GetOrthoViewMatrix())));
		ENSURE(m_pD3DDevice9->SetTransform(D3DTS_PROJECTION, &(m_wpCurCameraComponent.lock()->GetOrthoProjMatrix())));
	}

	RenderOrthogonal();
	RenderAlphaBlendOrthogonal();
	RenderUserInterface();
	Clear();
}

void CRenderManager::InsertActor(ERenderType _eRenderType, std::weak_ptr<CActor> _wpActor)
{
	CHECK(!_wpActor.expired());
	m_lstActors[(int32)_eRenderType].push_back(_wpActor);
}

void CRenderManager::RemoveActor(ERenderType _eRenderType, std::weak_ptr<CActor> _wpActor)
{
	CHECK(!_wpActor.expired());
	for (auto iter = m_lstActors[(int32)_eRenderType].begin(); iter != m_lstActors[(int32)_eRenderType].end();)
	{
		if (iter->lock()->GetActorName() == _wpActor.lock()->GetActorName())
		{
			(*iter).reset();
			m_lstActors[(int32)_eRenderType].erase(iter);
			break;
		}
		else
		{
			iter++;
		}
	}
}

void CRenderManager::RenderNonAlpha()
{
	for (auto& wpActor : m_lstActors[(int32)ERenderType::NON_ALPHA])
	{
		CHECK(!wpActor.expired());
		wpActor.lock()->Render();
	}
}

void CRenderManager::RenderAlphaTest()
{
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHAREF, 128);
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& wpActor : m_lstActors[(int32)ERenderType::ALPHA_TEST])
	{
		CHECK(!wpActor.expired());
		wpActor.lock()->Render();
	}
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CRenderManager::RenderAlphaBlend()
{
	// ���� ���� �����մϴ�. 
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���� ���� �������� �����մϴ�.
	m_lstActors[(int32)ERenderType::ALPHA_BLEND].sort
	(
		[] (std::weak_ptr<CActor> _wpDst, std::weak_ptr<CActor> _spSrc)
		-> bool { return _wpDst.lock()->GetDepthZ() > _spSrc.lock()->GetDepthZ(); }
	);

	for (auto& wpActor : m_lstActors[(int32)ERenderType::ALPHA_BLEND])
	{
		CHECK(!wpActor.expired());
		wpActor.lock()->Render();
	}
	// ���� ���带 ���ϴ�.
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CRenderManager::RenderAlphaBlendOrthogonal()
{
	// ���� ���� �����մϴ�. 
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���� ���� �������� �����մϴ�.
	m_lstActors[(int32)ERenderType::ALPHA_BLEND_ORTHOGONAL].sort
	(
		[](std::weak_ptr<CActor> _wpDst, std::weak_ptr<CActor> _spSrc)
		-> bool { return _wpDst.lock()->GetDepthZ() > _spSrc.lock()->GetDepthZ(); }
	);

	for (auto& wpActor : m_lstActors[(int32)ERenderType::ALPHA_BLEND_ORTHOGONAL])
	{
		CHECK(!wpActor.expired());
		wpActor.lock()->Render();
	}
	// ���� ���带 ���ϴ�.
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CRenderManager::RenderOrthogonal()
{
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHAREF, 128);
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& wpActor : m_lstActors[(int32)ERenderType::ORTHOGONAL])
	{
		CHECK(!wpActor.expired());
		wpActor.lock()->Render();
	}
	
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CRenderManager::RenderUserInterface()
{
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHAREF, 128);
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& wpActor : m_lstActors[(int32)ERenderType::USER_INTERFACE])
	{
		CHECK(!wpActor.expired());
		wpActor.lock()->Render();
	}
	
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CRenderManager::Clear()
{
	for (int32 iIndex = 0; iIndex < (int32)ERenderType::ENUM_END; ++iIndex)
	{
		m_lstActors[iIndex].clear();
	}
}

void CRenderManager::Release()
{
	Clear();

	// ���� �Ŵ����� �����մϴ�.
	m_upInstance.reset();
}