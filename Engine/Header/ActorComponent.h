#pragma once
#include "Object.h"

class CWorld;
class CLevel;
class CActor;
class CElement;

/**
 * @brief	���� ������Ʈ�Դϴ�.
 * @details ���� ������Ʈ�� ��� ������Ʈ�� �ֻ��� Ŭ�����Դϴ�.
			�� ������Ʈ�� ������ Ʈ�������� ������ ���� �ʽ��ϴ�.
 * @author	Ź�ؼ�
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
	 * @brief ������Ʈ�� ���� ���带 �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	std::weak_ptr<CWorld> GetWorld() const { CHECK(!m_wpWorld.expired()); return m_wpWorld; }

	/**
	 * @brief ������Ʈ�� ���� ������ �����ϰų� �ҷ��ɴϴ�.
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
	// �� ������Ʈ�� ������ ���Ͱ� ���� ����
	std::weak_ptr<CWorld> m_wpWorld;

	// �� ������Ʈ�� ������ ���Ͱ� ���� ����
	std::weak_ptr<CLevel> m_wpLevel;

	// �� ������Ʈ�� ���� ������Ʈ
	std::weak_ptr<CActorComponent> m_wpOwnerComponent;

	// �� ������Ʈ�� ������ ����
	std::weak_ptr<CActor> m_wpOwnerActor;
};

