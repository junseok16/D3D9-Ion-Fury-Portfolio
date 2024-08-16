#pragma once
#include "PlayerEffectActor.h"

class CEffectComponent;

class CPlayerSkillUIActor : public CPlayerEffectActor
{
public:
	explicit CPlayerSkillUIActor() = default;
	virtual ~CPlayerSkillUIActor() = default;

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
	Methods
********************/
public:
	void EffectComponentSetting();

/********************
	Getter / Setter
********************/
public:

/********************
	Data Members
********************/
private:
	std::weak_ptr<CEffectComponent> m_wpEffectComponent;

	float m_fX; // ºäÆ÷Æ® »óÀÇ ÁÂÇ¥
	float m_fY;

	float m_fSizeX; // Å©±â
	float m_fSizeY;
};

