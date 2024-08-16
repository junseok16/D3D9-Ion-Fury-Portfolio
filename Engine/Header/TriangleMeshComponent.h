#pragma once
#include "MeshComponent.h"

class CTriangleMeshComponent : public CMeshComponent
{
public:
	explicit CTriangleMeshComponent() = default;
	virtual ~CTriangleMeshComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void SetTriangleMeshInfo(const std::wstring _wstrTextureFileName = L"", int32 _iFileIndex = 0, const std::wstring _wstrTextureFileExt = L"");
};

