#pragma once
#include "Creature.h"

class CMovementComponent;
class CInputComponent;

/**
 * @brief 캐릭터 클래스입니다.
 * @details 캐릭터 클래스는 무브먼트, 인풋 컴포넌트를 데이터 멤버로 갖고 있습니다.
 * @author 탁준석
 * @date 2023-10-06
 */
class CCharacter : public CCreature
{
public:
	explicit CCharacter() = default;
	virtual ~CCharacter() = default;

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

/********************
	Getter/Setter
********************/
public:
	std::weak_ptr<CMovementComponent> GetMovementComponent() { return m_wpMovementComponent; }
	std::weak_ptr<CInputComponent> GetInputComponent() { return m_wpInputComponent; }

/********************
	Data Members
********************/
protected:
	std::weak_ptr<CMovementComponent> m_wpMovementComponent;
	std::weak_ptr<CInputComponent> m_wpInputComponent;
};

