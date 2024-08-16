#pragma once
#include "LightComponent.h"

class CSpotLightComponent : public CLightComponent
{
public:
	explicit CSpotLightComponent() = default;
	virtual ~CSpotLightComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetSpotLightInfo(D3DCOLORVALUE Diffuse, D3DCOLORVALUE Specular, D3DCOLORVALUE Ambient, D3DVECTOR Position, D3DVECTOR Direction, float fRange, float fFalloff, float fTheta, float fPhi, UINT _iIndex);
	void SetLightPosition(D3DVECTOR Position, D3DVECTOR Direction, UINT _iIndex);

};

