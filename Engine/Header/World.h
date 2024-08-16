#pragma once

class CLevel;

/**
 * @brief	���� Ŭ�����Դϴ�.
 * @details ���� Ŭ������ ������ �ʱ�ȭ, ������Ʈ, �����ϰų� ���ο� ������ �����մϴ�.
 * @author	Ź�ؼ�
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
	 * @brief ������ ��ȯ�մϴ�.
	 * @details �� �޼���� ���� ���ڿ��� Ű(key)�� ���޹޾� ������ ��ȯ�մϴ�.
	 * @param[in] _wstrLevel ���� ���ڿ�
	 */
	void ChangeLevelTo(const std::wstring& _wstrLevel);

	/**
	 * @brief ������ �����մϴ�.
	 * @details �� �޼���� ���� ���ڿ��� Ű(key)�� ���޹޾� ������ �����մϴ�.
	 * @param[in] _wstrLevel ���� ���ڿ�
	 */
	void RemoveLevel(const std::wstring& _wstrLevel);

	/**
	 * @brief ���ο� ������ �����մϴ�.
	 * @details �� �޼���� �ܺο��� ���� ���ڿ��� Ű(key)�� �ϴ� ������ �����մϴ�.
	 * @return std::shared_ptr<T> ���� ������ ������ �ξ�� �����͸� ��ȯ�մϴ�.
	 * @param[in] _wstrLevel ���� ���ڿ�
	 */
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<CLevel, T>>>
	std::shared_ptr<T> CreateLevel(const std::wstring& _wstrLevel) 
	{ 
		return AddLevel<T>(_wstrLevel); 
	}

	std::shared_ptr<CLevel> FindLevel(const std::wstring& _wstrLevel);

private:
	/**
	 * @brief ���ο� ������ �����մϴ�.
	 * @details �� �޼���� ���� ���ڿ��� Ű(key)�� �ϴ� ������ Ž���մϴ�. ���� ���ڿ��� �ش��ϴ� Ű�� ���� ���, ������ ���� �����մϴ�.
	 * @return std::shared_ptr<T> ���� ������ ������ �ξ�� �����͸� ��ȯ�մϴ�.
	 * @param[in] _wstrLevel ���� ���ڿ�
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
	 * @brief ���� ������ �ҷ��ɴϴ�.
	 */
	std::weak_ptr<CLevel> GetLevel() { CHECK(!m_wpLevel.expired());  return m_wpLevel; }

/********************
	Data Members
********************/
protected:
	// ���� ����
	std::weak_ptr<CLevel> m_wpLevel;

	// ���尡 �����ϰ� �ִ� ������
	std::unordered_map<std::wstring, std::shared_ptr<CLevel>> m_umapLevels;
};

