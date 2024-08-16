#pragma once
#include "LightComponent.h"

class CDirectionalLightComponent : public CLightComponent
{
public:
	explicit CDirectionalLightComponent() = default;
	virtual ~CDirectionalLightComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetDirLightInfo(D3DCOLORVALUE Diffuse, D3DCOLORVALUE Specular, D3DCOLORVALUE Ambient, D3DVECTOR Direction, UINT _iIndex);
};

