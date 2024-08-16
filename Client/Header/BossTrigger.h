#pragma once
#include "CubeColliderActor.h"

class CWarmechLeg;
class CWarmechHead;
class CSkinjob;
class CPlayerActor;

class CBossTrigger : public CCubeColliderActor
{
public:
	explicit CBossTrigger() = default;
	virtual ~CBossTrigger() = default;

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
	Getter/Setter
********************/
public:
	void SetWarmechLeg(std::weak_ptr<CWarmechLeg> _wpWarmechLeg) { m_wpWarmechLeg = _wpWarmechLeg; }

	void SetWarmechHead(std::weak_ptr<CWarmechHead> _wpWarmechHead) { m_wpWarmechHead = _wpWarmechHead; }

	void SetSkinjob(std::weak_ptr<CSkinjob> _wpSkinjob) { m_wpSkinjob = _wpSkinjob; }

/********************
	Overrides
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	std::weak_ptr<CWarmechLeg> m_wpWarmechLeg;
	
	std::weak_ptr<CWarmechHead> m_wpWarmechHead;

	std::weak_ptr<CSkinjob> m_wpSkinjob;

	std::weak_ptr<CPlayerActor> m_wpPlayer;

	bool m_bIsTriggered = false;
};

