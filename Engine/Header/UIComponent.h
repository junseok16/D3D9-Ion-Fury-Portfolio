#pragma once
#include "MeshComponent.h"

class CTextUIComponent;
class CElement;

class CUIComponent : public CMeshComponent
{
public:
	explicit CUIComponent() = default;
	virtual ~CUIComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	/*******************
	  UI ���� ��ü ����
	*******************/
//public:
//	template<typename T, typename = std::enable_if_t<std::is_base_of_v<CElement, T>>>
//	std::shared_ptr<T> CreateElement(const std::wstring& _wstrElement)
//	{
//		return AddElement<T>(_wstrElement);
//	}
//
//	std::shared_ptr<CElement> FindElement(const std::wstring& _wstrElement);
//
//private:
//	template<typename T>
//	std::shared_ptr<T> AddElement(const std::wstring& _wstrElement)
//	{
//		if (m_umapElements.find(_wstrElement) != m_umapElements.end()) { return nullptr; }
//
//		std::shared_ptr<T> spElement = std::make_shared<T>();
//		//spElement->SetOwnerActorComponent(std::dynamic_pointer_cast<CUIComponent>(shared_from_this()));
//		spElement->SetOwnerActorComponent(std::dynamic_pointer_cast<CTextUIComponent>(shared_from_this()));
//		spElement->SetActor(m_wpActor);
//		spElement->SetLevel(m_wpLevel);
//		spElement->SetWorld(m_wpWorld);
//
//		m_umapElements.insert({ _wstrElement, spElement });
//		return spElement;
//	}
//
//	/*******************
//	  Getter Setter
//	*******************/
public:
	//void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	//std::weak_ptr<CWorld> GetWorld() const { CHECK(!m_wpWorld.expired()); return m_wpWorld; }
	//
	//void SetLevel(std::weak_ptr<CLevel> _wpLevel) { m_wpLevel = _wpLevel; }
	//std::weak_ptr<CLevel> GetLevel() const { CHECK(!m_wpLevel.expired()); return m_wpLevel; }
	//
	//void SetActor(std::weak_ptr<CActor> _wpActor) { m_wpActor = _wpActor; }
	//std::weak_ptr<CActor> GetActor() const { CHECK(!m_wpActor.expired()); return m_wpActor; }
	//
	////void SetOwnerActorComponent(std::weak_ptr<CUIComponent> _wpOwnerActorComponent) { m_wpOwnerComponent = _wpOwnerActorComponent; }
	////std::weak_ptr<CUIComponent> GetOwnerActorComponent() const { return m_wpOwnerComponent; }
	//void SetOwnerActorComponent(std::weak_ptr<CTextUIComponent> _wpOwnerActorComponent) { m_wpOwnerComponent1 = _wpOwnerActorComponent; }
	//std::weak_ptr<CTextUIComponent> GetOwnerActorComponent() const { return m_wpOwnerComponent1; }

	/*******************
	  UI ���� Methods
	*******************/
public:
	// UI ���� ����(���� ���, ���� Ȯ����, ���� Ű ��, �ִϸ��̼� Ÿ��)
	// ���� ����
	void SetCurrentUI(const int32& _iCurFrame) { m_iCurFrame = _iCurFrame; }
	void SettingUserInterfaceInfo(const std::wstring& _wstrTextureFileName,
		const uint32& _iFileBeginIndex, const uint32& _iFileEndIndex,
		const std::wstring& _wstrState, EUserInterfaceType _eUserInterfaceType);

	// Getter Setter
	void  SetCurrentState(const std::wstring& _wstrFileName) { m_wstrCurrentState = _wstrFileName; }
	const std::wstring& GetCurrentState() const { return m_wstrCurrentState; }

	void	AddUIState(const std::wstring& _wstrState, const uint32& _iBeginIndex, const uint32& _iEndIndex);

protected:
	EUserInterfaceType	m_eUserInterfaceType = EUserInterfaceType::STATIC; // UI Ÿ��(���� Ƚ��, ����, NONE)
	int32			m_iCurFrame = 0;			// ���� ������
	std::wstring	m_wstrCurrentState = L"";	// ���� ����(Ű ��)
	std::unordered_map <std::wstring, std::pair<int32, int32>> m_umapUIStateFrame; // AddState �Լ��� ���� ���°� �߰��ǰ� ��.	

//private:
//	// ������Ʈ�� ���� ����
//	std::weak_ptr<CWorld> m_wpWorld;
//
//	// ������Ʈ�� ���� ����
//	std::weak_ptr<CLevel> m_wpLevel;
//
//	// �� ������Ʈ�� ������ ����
//	std::weak_ptr<CActor> m_wpActor;
//
//	// �� ������Ʈ�� ���� ������Ʈ
//	//std::weak_ptr<CUIComponent> m_wpOwnerComponent;
//
//
//	std::weak_ptr<CTextUIComponent> m_wpOwnerComponent1;
//
//	// ������Ʈ�� ������ ���ĺ�
//	std::unordered_map<std::wstring, std::shared_ptr<CElement>> m_umapElements;
};

