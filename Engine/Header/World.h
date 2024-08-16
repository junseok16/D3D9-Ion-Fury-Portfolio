#pragma once

class CLevel;

/**
 * @brief	월드 클래스입니다.
 * @details 월드 클래스는 레벨을 초기화, 업데이트, 렌더하거나 새로운 레벨을 생성합니다.
 * @author	탁준석
 * @date	2023-10-10
 */
class CWorld : public std::enable_shared_from_this<CWorld>
{
public:
	explicit CWorld() = default;
	virtual ~CWorld() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize();
	virtual void BeginPlay();
	virtual int32 Update(const float& _fDeltaSeconds);
	virtual int32 LateUpdate(const float& _fDeltaSeconds);
	virtual void Render();
	virtual void EndPlay();
	virtual void Release();

/********************
	Methods
********************/
public:
	/**
	 * @brief 레벨을 전환합니다.
	 * @details 이 메서드는 레벨 문자열을 키(key)로 전달받아 레벨을 전환합니다.
	 * @param[in] _wstrLevel 레벨 문자열
	 */
	void ChangeLevelTo(const std::wstring& _wstrLevel);

	/**
	 * @brief 레벨을 삭제합니다.
	 * @details 이 메서드는 레벨 문자열을 키(key)로 전달받아 레벨을 삭제합니다.
	 * @param[in] _wstrLevel 레벨 문자열
	 */
	void RemoveLevel(const std::wstring& _wstrLevel);

	/**
	 * @brief 새로운 레벨을 생성합니다.
	 * @details 이 메서드는 외부에서 레벨 문자열을 키(key)로 하는 레벨을 생성합니다.
	 * @return std::shared_ptr<T> 새로 생성한 레벨의 셰어드 포인터를 반환합니다.
	 * @param[in] _wstrLevel 레벨 문자열
	 */
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<CLevel, T>>>
	std::shared_ptr<T> CreateLevel(const std::wstring& _wstrLevel) 
	{ 
		return AddLevel<T>(_wstrLevel); 
	}

	std::shared_ptr<CLevel> FindLevel(const std::wstring& _wstrLevel);

private:
	/**
	 * @brief 새로운 레벨을 생성합니다.
	 * @details 이 메서드는 레벨 문자열을 키(key)로 하는 레벨을 탐색합니다. 레벨 문자열에 해당하는 키가 없는 경우, 레벨을 새로 생성합니다.
	 * @return std::shared_ptr<T> 새로 생성한 레벨의 셰어드 포인터를 반환합니다.
	 * @param[in] _wstrLevel 레벨 문자열
	 */
	template<typename T>
	std::shared_ptr<T> AddLevel(const std::wstring& _wstrLevel)
	{
		if (m_umapLevels.find(_wstrLevel) != m_umapLevels.end()) { return nullptr; }

		std::shared_ptr<T> spLevel = std::make_shared<T>();
		spLevel->SetWorld(shared_from_this());
		spLevel->SetLevelName(_wstrLevel);
		m_umapLevels.insert({ _wstrLevel, spLevel });
		return spLevel;
	}

/********************
	Getter/Setter
********************/
public:
	/**
	 * @brief 현재 레벨을 불러옵니다.
	 */
	std::weak_ptr<CLevel> GetLevel() { CHECK(!m_wpLevel.expired());  return m_wpLevel; }

/********************
	Data Members
********************/
protected:
	// 현재 레벨
	std::weak_ptr<CLevel> m_wpLevel;

	// 월드가 소유하고 있는 레벨들
	std::unordered_map<std::wstring, std::shared_ptr<CLevel>> m_umapLevels;
};

