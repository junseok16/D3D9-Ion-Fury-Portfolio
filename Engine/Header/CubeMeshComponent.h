#pragma once
#include "MeshComponent.h"

class CCubeMeshComponent : public CMeshComponent
{
public:
	explicit CCubeMeshComponent() = default;
	virtual ~CCubeMeshComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void SetCubeMeshInfo(const std::wstring& _wstrTextureFileName);

	void SetCubeMeshInfo(const std::wstring _wstrTextureFileName, int32 _iFileIndex, const std::wstring _wstrTextureFileExt);
};

