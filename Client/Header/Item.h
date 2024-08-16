#pragma once
#include "CubeColliderActor.h"

class CAnimationComponent;
class CRectangleMeshComponent;
class CSoundComponent;

class CItem : public CCubeColliderActor
{
public:
	explicit CItem() = default;
	virtual ~CItem() = default;

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
	void SetBillboard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent);

	EItemType GetItemType() { return m_eItemType; }

protected:
	std::weak_ptr<CAnimationComponent>		m_wpAnimationComponent;
	std::weak_ptr<CRectangleMeshComponent>  m_wpRectangleMeshComponent;
	std::weak_ptr<CSoundComponent>			m_wpSoundComponent;

	EItemType m_eItemType = EItemType::ENUM_END;
	bool m_bIsDead = false;
};

