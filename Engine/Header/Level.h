#pragma once

class CWorld;
class CActor;

/**
 * @brief	���� Ŭ�����Դϴ�.
 * @details ���� Ŭ����(�� Ŭ����)�� ���͸� �ʱ�ȭ, ������Ʈ, �����ϰų� ���ο� ���͸� �����մϴ�.
 * @author	Ź�ؼ�
 * @date	2023-10-10
 */
class CLevel : public std::enable_shared_from_this<CLevel>
{
public:
	explicit CLevel() = default;
	virtual ~CLevel() = default;

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
	 * @brief ���ο� ���͸� �����մϴ�.
	 * @details �� �޼���� �ܺο��� ���� ���ڿ��� Ű(key)�� �ϴ� ���͸� �����մϴ�.
	 * @return std::shared_ptr<T> ���� ������ ������ �ξ�� �����͸� ��ȯ�մϴ�.
	 * @param[in] _wstrActor ���� ���ڿ�, _wstrTag ���� �±�, _wstrLayer ���� ���̾�
	 */
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<CActor, T>>>
	std::shared_ptr<T> CreateActor(const std::wstring& _wstrActor, const std::wstring& _wstrTag, const std::wstring& _wstrLayer)
	{
		return AddActor<T>(_wstrActor, _wstrTag, _wstrLayer);
	}

	std::shared_ptr<CActor> FindActor(const std::wstring& _wstrActor);

	/*
	*  @brief ���͸� ���� �ִ� �ؽ� ���� ������ ��ȯ�մϴ�.
	*/
	const std::unordered_map<std::wstring, std::shared_ptr<CActor>>& GetActors() { return m_umapActors; }

	/*
	*  @brief ���͸� �����մϴ�.
	*/
	void RemoveActor(const std::wstring& _wstrActor);

	/*
	*  @brief ������ ���Ϸκ��� ������ �ε��մϴ�.
	*/
	HRESULT LoadLevelFromFile(const std::wstring& _wstrLevel);

private:
	/**
	 * @brief ���ο� ���͸� �����մϴ�.
	 * @details �� �޼���� ���� ���ڿ��� Ű(key)�� �ϴ� ������ Ž���մϴ�. ���� ���ڿ��� �ش��ϴ� Ű�� ���� ���, ���͸� ���� �����մϴ�.
	 * @return std::shared_ptr<T> ���� ������ ������ �ξ�� �����͸� ��ȯ�մϴ�.
	 * @param[in] _wstrActor ���� ���ڿ�, _wstrTag ���� �±�, _wstrLayer ���� ���̾�
	 */
	template<typename T>
	std::shared_ptr<T> AddActor(const std::wstring& _wstrActor, const std::wstring& _wstrTag, const std::wstring& _wstrLayer)
	{
		if (m_umapActors.find(_wstrActor) != m_umapActors.end()) { return nullptr; }

		std::shared_ptr<T> spActor = std::make_shared<T>();
		spActor->SetWorld(m_wpWorld);
		spActor->SetLevel(shared_from_this());
		spActor->SetActorName(_wstrActor);
		spActor->SetActorTag(_wstrTag);
		spActor->SetActorLayer(_wstrLayer);

		m_umapActors.insert({ _wstrActor, spActor });
		return spActor;
	}

public:
	void AddNonDestroyActor(std::shared_ptr<CActor> _spActor);
	

/********************
	Getter/Setter
********************/
public:
	/**
	 * @brief ������ ���� ���带 �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	std::weak_ptr<CWorld> GetWorld() { CHECK(!m_wpWorld.expired()); return m_wpWorld; }

	const std::unordered_map<std::wstring, std::shared_ptr<CActor>>& GetUmapActors() { return m_umapActors; }

	void SetLevelName(std::wstring _wstrLevelName) { m_wstrLevelName = _wstrLevelName; }
	const std::wstring& GetLevelName() const { return m_wstrLevelName; }

/********************
	Data Members
********************/
private:
	std::wstring m_wstrLevelName = L"";

	// ������ ���� ����
	std::weak_ptr<CWorld> m_wpWorld;

	// ������ �����ϰ� �ִ� ���͵�
	std::unordered_map<std::wstring, std::shared_ptr<CActor>> m_umapActors;
};