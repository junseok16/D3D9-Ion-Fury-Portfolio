#pragma once
#include "MeshComponent.h"

class CRectangleMeshComponent : public CMeshComponent
{
public:
	explicit CRectangleMeshComponent() = default;
	virtual ~CRectangleMeshComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void SetRectangleMeshInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex);
	void SetTextureIndex(uint32 _iIndex);
	// void SetRectangleMeshInfo(const std::wstring& _wstrTextureFilePath);

	// void SetRectangleMeshInfo(const std::wstring& _wstrTextureFileName, int32 _iFileIndex, const std::wstring& _wstrTextureFileExt);
};

