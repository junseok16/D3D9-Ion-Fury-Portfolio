#pragma once
#include "CubeColliderActor.h"

class CRectangleMeshComponent;

class CWarmechCharge : public CCubeColliderActor
{
public:
	explicit CWarmechCharge() = default;
	virtual ~CWarmechCharge() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void InitializeRectMeshComponent();

	void UpdateChargePosition();

private:
	std::weak_ptr<CRectangleMeshComponent> m_wpRectMeshComponent;
};

