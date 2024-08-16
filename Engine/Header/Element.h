#pragma once
#include "TextUIComponent.h"


/**
 * @brief	������Ʈ Ŭ�����Դϴ�.
 * @details ������Ʈ (������Ʈ ���� �� ���� ����)
 * @author	�̵���
 * @date	2023-11-04
 */
class CElement : public CTextUIComponent
{
public:
	explicit CElement() = default;
	virtual ~CElement() = default;

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

	void SetElementSpriteInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex);

	/********************
		Methods
	********************/
public:
	/********************
		Getter/Setter
	********************/
public:
	/**
	 * @brief ������Ʈ�� ���� ����, ����, ����, ������Ʈ, ������Ʋ�� �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	std::weak_ptr<CWorld> GetWorld() const { CHECK(!m_wpWorld.expired()); return m_wpWorld; }

	void SetLevel(std::weak_ptr<CLevel> _wpLevel) { m_wpLevel = _wpLevel; }
	std::weak_ptr<CLevel> GetLevel() const { CHECK(!m_wpLevel.expired()); return m_wpLevel; }

	void SetActor(std::weak_ptr<CActor> _spActor) { m_wpActor = _spActor; }
	std::weak_ptr<CActor> const GetActor() { CHECK(!m_wpActor.expired()); return m_wpActor; }

	void SetOwnerUIComponent(std::shared_ptr<CTextUIComponent> _wpOwnerComponent) { m_wpOwnerComponent = _wpOwnerComponent; }
	std::weak_ptr<CTextUIComponent> GetOwnerUIComponent() const { CHECK(!m_wpOwnerComponent.expired()); return m_wpOwnerComponent; }

	void SetOwnerUIElement(std::weak_ptr<CElement> _spOwnerElement) { m_wpOwnerElement = _spOwnerElement; }
	std::weak_ptr<CElement> const GetOwnerUIElement() { CHECK(!m_wpOwnerElement.expired()); return m_wpOwnerElement; }


	/********************
		Data Members
	********************/
private:
	// �� ������Ʈ�� ������ ���Ͱ� ���� ����
	std::weak_ptr<CWorld> m_wpWorld;

	// �� ������Ʈ�� ������ ���Ͱ� ���� ����
	std::weak_ptr<CLevel> m_wpLevel;

	// �� ������Ʈ�� ������ ����
	std::weak_ptr<CActor> m_wpActor;

	// �� ������Ʈ�� ������ ����
	std::weak_ptr<CTextUIComponent> m_wpOwnerComponent;

	// �� ������Ʈ�� ���� ������Ʈ
	std::weak_ptr<CElement> m_wpOwnerElement;



};

