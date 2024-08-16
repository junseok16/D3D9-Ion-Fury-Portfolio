#pragma once
#include "MeshComponent.h"

class CSkyboxComponent : public CMeshComponent
{
public:
	explicit CSkyboxComponent() = default;
	virtual ~CSkyboxComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void SetSkyboxInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex);
};

