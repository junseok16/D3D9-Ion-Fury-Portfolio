#pragma once
#include "ActorComponent.h"

class CInputComponent : public CActorComponent
{
public:
	explicit CInputComponent() = default;
	virtual ~CInputComponent() = default;

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
	void AxisMapping(const std::wstring& _wstrAxis, int32 _iKey, int32 _iScale);

	template<typename T>
	void BindAxis(const std::wstring& _wstrAxis, std::shared_ptr<T> _spOwner, void(T::* function)(int32))
	{
		std::function<void(int32)> m_function = [_spOwner, function](int32 _iAxisValue)
		{ (_spOwner.get()->*function)(_iAxisValue); };

		if (m_umapAxisCallbacks.find(_wstrAxis) != m_umapAxisCallbacks.end()) { return; }
		m_umapAxisCallbacks.insert({ _wstrAxis, m_function });
	}

	void ActionMapping(const std::wstring& _wstrAction, int32 _iKey);

	template<typename T>
	void BindAction(const std::wstring& _wstrAxis, std::shared_ptr<T> _spOwner, void(T::* function)())
	{
		std::function<void(void)> m_function = [_spOwner, function]()
		{ (_spOwner.get()->*function)(); };

		if (m_umapActionCallbacks.find(_wstrAxis) != m_umapActionCallbacks.end()) { return; }
		m_umapActionCallbacks.insert({ _wstrAxis, m_function });
	}

/********************
	Data Members
********************/
private:
	std::unordered_multimap<std::wstring /* Axis */, std::pair<int32 /* Key */, int32 /* Scale */>> m_ummapAxisMaps;
	std::unordered_map<std::wstring /* Axis */, std::function<void(int32) /* Callback */>> m_umapAxisCallbacks;

	std::unordered_multimap<std::wstring /* Action */, int32 /* Key */> m_ummapActionMaps;
	std::unordered_map<std::wstring /* Action */, std::function<void(void) /* Callback */>> m_umapActionCallbacks;
};

