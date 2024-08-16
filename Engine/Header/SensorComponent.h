#pragma once
#include "ActorComponent.h"

enum class ESeeingState
{
	SEE_NEAR,
	SEE_FAR,
	ENUM_END
};

enum class EHearingState
{
	HEAR_NEAR,
	HEAR_FAR,
	ENUM_END
};

class CSensorComponent : public CActorComponent
{
public:
	explicit CSensorComponent() = default;
	virtual ~CSensorComponent() = default;

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
private:
	void UpdateSeeingActor();

public:
	// �ǰ����� �̸�, �ǰ����� ������ ������, ������ ������ ������, ������ ������ �Լ�
	template<typename T, typename K>
	void BindSeeingEnterDelegate(const std::wstring& _wstrName, std::shared_ptr<K> _spDst, std::shared_ptr<T> _spSrc, void(T::* function)())
	{
		if (m_umapSeeingEnterCallbacks.find(_wstrName) != m_umapSeeingEnterCallbacks.end()) { return; }

		std::function<void(void)> m_function = [_spSrc, function]() { (_spSrc.get()->*function)(); };
		m_wpEnterSeeingActors.insert({ _wstrName, _spDst });
		m_umapSeeingEnterCallbacks.insert({ _wstrName, m_function });
	}

	template<typename T, typename K>
	void BindSeeingExitDelegate(const std::wstring& _wstrName, std::shared_ptr<K> _spDst, std::shared_ptr<T> _spSrc, void(T::* function)())
	{
		if (m_umapSeeingExitCallbacks.find(_wstrName) != m_umapSeeingExitCallbacks.end()) { return; }

		std::function<void(void)> m_function = [_spSrc, function]() { (_spSrc.get()->*function)(); };
		m_wpExitSeeingActors.insert({ _wstrName, _spDst });
		m_umapSeeingExitCallbacks.insert({ _wstrName, m_function });
	}

/********************
	Getter/Setter
********************/
public:
    float GetSeeingRadius() const { return m_fSeeingRadius; }
    void SetSeeingRadius(float _fSeeingRadius) { m_fSeeingRadius = _fSeeingRadius; }

    float GetInterval() const { return m_fInterval; }
    void SetInterval(float _fInterval) { m_fInterval = _fInterval; }

/********************
	Data Members
********************/
private:
	ESeeingState m_eCurSeeingState = ESeeingState::SEE_FAR;

	ESeeingState m_ePrevSeeingState = ESeeingState::SEE_FAR;

private:
	// û�� �ּ� ������ ����
	float m_fHearingRadius = 45.0f;

	// �ð� ������ ����
	float m_fSeeingRadius = 40.0f;

	// �Ҹ��� ��ų� ���͸� ���� �� �ʿ��� �ð� ����
	float m_fInterval = 0.5f;

	float m_fSumInterval = 0.0f;

private:
	// �� ������Ʈ�� ��ų� �� ���� ���͵�
	std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_wpEnterSeeingActors;

	std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_wpExitSeeingActors;

	std::unordered_map<std::wstring, std::function<void(void)>> m_umapSeeingEnterCallbacks;

	std::unordered_map<std::wstring, std::function<void(void)>> m_umapSeeingExitCallbacks;
};

