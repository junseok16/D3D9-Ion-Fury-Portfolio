#pragma once

class CActor;
class CCameraComponent;

class CRenderManager final
{
	DECLARE_SINGLETON(CRenderManager)

/********************
	Framework
********************/
public:
	HRESULT Initialize(bool _bEditor);
	void Render();
	void Release();
	void Clear();

/********************
	Methods
********************/
public:
	void InsertActor(ERenderType _eRenderType, std::weak_ptr<CActor> _wpActor);

	void RemoveActor(ERenderType _eRenderType, std::weak_ptr<CActor> _wpActor);

private:
	void RenderNonAlpha();
	void RenderAlphaTest();
	void RenderAlphaBlend();

	void RenderAlphaBlendOrthogonal();
	void RenderOrthogonal();
	void RenderUserInterface();

/********************
	Getter/Setter
********************/
public:
	void SetCurRenderCamera(std::weak_ptr<CCameraComponent> _wpCurCameraComponent) { m_wpCurCameraComponent = _wpCurCameraComponent; }
	
	std::weak_ptr<CCameraComponent> GetCurRenderCamera() { return m_wpCurCameraComponent; }

/********************
	Data Members
********************/
public:
	// ������ ����
	bool m_bEditor = false;

private:
	// ����̽� ������
	LPDIRECT3DDEVICE9 m_pD3DDevice9 = nullptr;

	// ������ ��� ���͵�
	std::list<std::weak_ptr<CActor>> m_lstActors[(int32)ERenderType::ENUM_END];

	// ���� ������ ī�޶�
	std::weak_ptr<CCameraComponent> m_wpCurCameraComponent;

	// �ٸ� ī�޶��
	std::unordered_map<std::wstring, std::weak_ptr<CCameraComponent>> m_umapCameraComponents;
};

