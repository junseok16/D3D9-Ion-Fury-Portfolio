#pragma once

class CWorld;
class CActor;

/**
 * @brief	레벨 클래스입니다.
 * @details 레벨 클래스(신 클래스)는 액터를 초기화, 업데이트, 렌더하거나 새로운 액터를 생성합니다.
 * @author	탁준석
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
	 * @brief 새로운 액터를 생성합니다.
	 * @details 이 메서드는 외부에서 액터 문자열을 키(key)로 하는 액터를 생성합니다.
	 * @return std::shared_ptr<T> 새로 생성한 액터의 셰어드 포인터를 반환합니다.
	 * @param[in] _wstrActor 액터 문자열, _wstrTag 액터 태그, _wstrLayer 액터 레이어
	 */
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<CActor, T>>>
	std::shared_ptr<T> CreateActor(const std::wstring& _wstrActor, const std::wstring& _wstrTag, const std::wstring& _wstrLayer)
	{
		return AddActor<T>(_wstrActor, _wstrTag, _wstrLayer);
	}

	std::shared_ptr<CActor> FindActor(const std::wstring& _wstrActor);

	/*
	*  @brief 액터를 갖고 있는 해시 맵의 참조를 반환합니다.
	*/
	const std::unordered_map<std::wstring, std::shared_ptr<CActor>>& GetActors() { return m_umapActors; }

	/*
	*  @brief 액터를 삭제합니다.
	*/
	void RemoveActor(const std::wstring& _wstrActor);

	/*
	*  @brief 데이터 파일로부터 레벨을 로드합니다.
	*/
	HRESULT LoadLevelFromFile(const std::wstring& _wstrLevel);

private:
	/**
	 * @brief 새로운 액터를 생성합니다.
	 * @details 이 메서드는 액터 문자열을 키(key)로 하는 액터을 탐색합니다. 액터 문자열에 해당하는 키가 없는 경우, 액터를 새로 생성합니다.
	 * @return std::shared_ptr<T> 새로 생성한 액터의 셰어드 포인터를 반환합니다.
	 * @param[in] _wstrActor 액터 문자열, _wstrTag 액터 태그, _wstrLayer 액터 레이어
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
	 * @brief 레벨이 속한 월드를 저장하거나 불러옵니다.
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

	// 레벨이 속한 월드
	std::weak_ptr<CWorld> m_wpWorld;

	// 레벨이 소유하고 있는 액터들
	std::unordered_map<std::wstring, std::shared_ptr<CActor>> m_umapActors;
};