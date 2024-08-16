#pragma once
#include "CubeColliderActor.h"

class CStage1;
class CStage2;
class CStage3;
class CStage4;

class CSceneChangerActor : public CCubeColliderActor
{
public:
	explicit CSceneChangerActor() = default;
	virtual ~CSceneChangerActor() = default;

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

private:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);
};

