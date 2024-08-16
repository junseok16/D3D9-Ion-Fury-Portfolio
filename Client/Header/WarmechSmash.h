#pragma once
#include "CubeColliderActor.h"

class CRectangleMeshComponent;

class CWarmechSmash : public CCubeColliderActor
{
public:
	explicit CWarmechSmash() = default;
	virtual ~CWarmechSmash() = default;

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

/********************
	Component
********************/
public:
	void InitializeRectMeshComponent();

/********************
	Data Members
********************/
private:
	std::weak_ptr<CRectangleMeshComponent> m_wpRectMeshComponent;
};

