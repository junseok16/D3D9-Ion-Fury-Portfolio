#pragma once
#include "Actor.h"

class CDirectionalLightComponent;
//class CPointLightComponent;
class CSunActor : public CActor
{
public:
	explicit CSunActor() = default;
	virtual ~CSunActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	std::weak_ptr<CDirectionalLightComponent>	m_wpDirectionalLightComponent;
	//std::weak_ptr<CPointLightComponent>	m_wpPointLightComponent;
};

