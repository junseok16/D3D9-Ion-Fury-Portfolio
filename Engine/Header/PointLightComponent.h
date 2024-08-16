#pragma once
#include "LightComponent.h"

class CPointLightComponent : public CLightComponent
{
public:
	explicit CPointLightComponent() = default;
	virtual ~CPointLightComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetPointLightInfo(D3DCOLORVALUE Diffuse, D3DCOLORVALUE Specular, D3DCOLORVALUE Ambient, D3DVECTOR Position, float fRange, UINT _iIndex);

};

