#pragma once
#include "SceneComponent.h"

class CLightComponent : public CSceneComponent
{
public:
	explicit CLightComponent() = default;
	virtual ~CLightComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetLightOnOff(UINT _iIndex, BOOL bEnable);

protected:
	LPDIRECT3DDEVICE9	m_pD3DDevice9 = nullptr;
	D3DLIGHT9			m_tLightInfo;
	UINT				m_iIndex = 0;		// 라이트 인덱스. 쌤이 8개 할 수 있다고 했으니 0부터 7까지. 설정할때 조심해야함
};
