#pragma once
#include "Actor.h"

class CPlayerActor;
class CSkyboxComponent;

class CSkyBox : public CActor
{
public:
	explicit CSkyBox() = default;
	virtual ~CSkyBox() = default;

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
	void InitializeSkyboxComponent();

	void SetSkybox(const std::wstring& _wstrSkyboxFileName) { m_wstrSkyboxFileName = _wstrSkyboxFileName; }

private:
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;

	std::weak_ptr<CSkyboxComponent>	m_wpSkyboxComponent;

	std::wstring m_wstrSkyboxFileName = L"";
};

