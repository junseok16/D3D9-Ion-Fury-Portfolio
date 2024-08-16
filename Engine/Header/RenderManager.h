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
	// 에디터 여부
	bool m_bEditor = false;

private:
	// 디바이스 포인터
	LPDIRECT3DDEVICE9 m_pD3DDevice9 = nullptr;

	// 렌더할 모든 액터들
	std::list<std::weak_ptr<CActor>> m_lstActors[(int32)ERenderType::ENUM_END];

	// 현재 렌더할 카메라
	std::weak_ptr<CCameraComponent> m_wpCurCameraComponent;

	// 다른 카메라들
	std::unordered_map<std::wstring, std::weak_ptr<CCameraComponent>> m_umapCameraComponents;
};

