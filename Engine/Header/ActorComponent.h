#pragma once
#include "Object.h"

class CWorld;
class CLevel;
class CActor;
class CElement;

/**
 * @brief	액터 컴포넌트입니다.
 * @details 액터 컴포넌트는 모든 컴포넌트의 최상위 클래스입니다.
			이 컴포넌트는 액터의 트랜스폼에 영향을 받지 않습니다.
 * @author	탁준석
 * @date	2023-10-10
 */
class CActorComponent : public CObject
{
public:
	explicit CActorComponent() = default;
	virtual ~CActorComponent() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize();
	virtual void BeginPlay();
	virtual int32 Update(const float& _fDeltaSeconds);
	virtual int32 LateUpdate(const float& _fDeltaSeconds);
	virtual void EndPlay();
	virtual void Render();
	virtual void Release();

/********************
	Methods
********************/
public:
/********************
	Getter/Setter
********************/
public:
	/**
	 * @brief 컴포넌트가 속한 월드를 저장하거나 불러옵니다.
	 */
	void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	std::weak_ptr<CWorld> GetWorld() const { CHECK(!m_wpWorld.expired()); return m_wpWorld; }

	/**
	 * @brief 컴포넌트가 속한 레벨을 저장하거나 불러옵니다.
	 */
	void SetLevel(std::weak_ptr<CLevel> _wpLevel) { m_wpLevel = _wpLevel; }
	std::weak_ptr<CLevel> GetLevel() const { CHECK(!m_wpLevel.expired()); return m_wpLevel; }

	void SetOwnerActor(std::shared_ptr<CActor> _spOwnerActor) { m_wpOwnerActor = _spOwnerActor; }
	std::weak_ptr<CActor> const GetOwnerActor() { CHECK(!m_wpOwnerActor.expired()); return m_wpOwnerActor; }

	void SetOwnerComponent(std::weak_ptr<CActorComponent> _wpOwnerComponent) { m_wpOwnerComponent = _wpOwnerComponent; }
	std::weak_ptr<CActorComponent> GetOwnerComponent() const { CHECK(!m_wpOwnerComponent.expired()); return m_wpOwnerComponent; }

/********************
	Data Members
********************/
private:
	// 이 컴포넌트를 소유한 액터가 속한 월드
	std::weak_ptr<CWorld> m_wpWorld;

	// 이 컴포넌트를 소유한 액터가 속한 레벨
	std::weak_ptr<CLevel> m_wpLevel;

	// 이 컴포넌트의 소유 컴포넌트
	std::weak_ptr<CActorComponent> m_wpOwnerComponent;

	// 이 컴포넌트를 소유한 액터
	std::weak_ptr<CActor> m_wpOwnerActor;
};

