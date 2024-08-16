#pragma once
#include "Object.h"

class CWorld;
class CLevel;
class CActorComponent;
class CSceneComponent;
class CPrimitiveComponent;
class CColliderComponent;

/**
 * @brief	액터 클래스입니다.
 * @details 액터 클래스(게임 오브젝트 클래스)
 * @author	탁준석
 * @date	2023-10-10
 */
class CActor : public CObject
{
public:
	explicit CActor() = default;
	virtual ~CActor() = default;

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
	 * @brief 새로운 액터 컴포넌트를 생성합니다.
	 * @details 이 메서드는 외부에서 액터 컴포넌트 문자열을 키(key)로 하는 액터 컴포넌트를 생성합니다.
	 * @return std::shared_ptr<T> 새로 생성한 액터 컴포넌트의 셰어드 포인터를 반환합니다.
	 * @param[in] _wstrActorComponent 액터 컴포넌트 문자열
	 */
	template<typename T, typename = std::enable_if_t<std::is_base_of_v<CActorComponent, T>>>
	std::shared_ptr<T> CreateActorComponent(const std::wstring& _wstrActorComponent)
	{
		return AddActorComponent<T>(_wstrActorComponent);
	}

	std::shared_ptr<CActorComponent> FindActorComponent(const std::wstring& _wstrActorComponent);

private:
	template<typename T>
	std::shared_ptr<T> AddActorComponent(const std::wstring& _wstrActorComponent)
	{
		if (m_umapActorComponents.find(_wstrActorComponent) != m_umapActorComponents.end()) { return nullptr; }

		std::shared_ptr<T> spActorComponent = std::make_shared<T>();
		spActorComponent->SetOwnerActor(std::dynamic_pointer_cast<CActor>(shared_from_this()));
		spActorComponent->SetLevel(m_wpLevel);
		spActorComponent->SetWorld(m_wpWorld);

		m_umapActorComponents.insert({ _wstrActorComponent, spActorComponent });
		return spActorComponent;
	}

	/**
	 * @brief 액터의 트랜스폼을 업데이트합니다.
	 * @details 
	 */
	virtual void UpdateActorTransform();

	void UpdateActorDepthZ();

public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

/********************
	Getter/Setter
********************/
public:
	/**
	 * @brief 액터가 속한 월드를 저장하거나 불러옵니다.
	 */
	void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	std::weak_ptr<CWorld> GetWorld() const { CHECK(!m_wpWorld.expired()); return m_wpWorld; }

	/**
	 * @brief 액터가 속한 레벨을 저장하거나 불러옵니다.
	 */
	void SetLevel(std::weak_ptr<CLevel> _wpLevel) { m_wpLevel = _wpLevel; }
	std::weak_ptr<CLevel> GetLevel() const { CHECK(!m_wpLevel.expired()); return m_wpLevel; }

	/**
	 * @brief 액터의 태그를 저장하거나 불러옵니다.
	 */
	void SetActorTag(const std::wstring& _wstrTag) { m_usetTags.insert(_wstrTag); }
	std::unordered_set<std::wstring>& GetActorTag() { return m_usetTags; }
	
	/**
	 * @brief 액터의 레이어를 저장하거나 불러옵니다.
	 */
	// 11.11 const 수식어를 붙인 상태로는 uset의 find함수가 제대로 작동하지 않아 const를 떼었습니다. -동연 -
	void SetActorLayer(const std::wstring& _wstrLayer) { m_usetLayers.insert(_wstrLayer); }
	std::unordered_set<std::wstring>& GetActorLayer() { return m_usetLayers; }

	/**
	 * @brief 액터의 로컬 좌표를 저장하거나 불러옵니다.
	 */
	void SetActorPosition(const FVector3& _vTranslate) { m_vTranslate = _vTranslate; }
	const FVector3& GetActorPosition() const { return m_vTranslate; }

	/**
	 * @brief 액터의 월드 좌표를 불러옵니다.
	 */
	const FVector3& GetActorWorldPosition() const { return m_vWorldPosition; }

	/**
	 * @brief 액터의 회전을 저장하거나 불러옵니다.
	 */
	void SetActorRotation(const FVector3& _vRotate) { m_vRotate = _vRotate; }
	const FVector3& GetActorRotation() const { return m_vRotate; }
	
	/**
	 * @brief 액터의 크기를 저장하거나 불러옵니다.
	 */
	void SetActorScale(const FVector3& _vScale) { m_vScale = _vScale; }
	const FVector3& GetActorScale() const { return m_vScale; }
	
	/**
	 * @brief 액터의 루트 컴포넌트를 저장하거나 불러옵니다.
	 */
	void SetRootComponent(std::weak_ptr<CSceneComponent> _wpSceneComponent);
	std::weak_ptr<CSceneComponent> GetRootComponent() const { return m_wpRootComponent; }

	/**
	 * @brief 액터의 이름을 저장하거나 불러옵니다. 10.30 - 박동연 -
	 */
	void SetActorName(const std::wstring& _wstrActorName) { m_wstrActorName = _wstrActorName; }
	const std::wstring& GetActorName() { return m_wstrActorName; }

	// 임시 코드
	void SetIsCollided(bool _bIsCollided) { m_bIsCollided = _bIsCollided; }
	bool GetIsCollided() { return m_bIsCollided; }

	ERenderType GetRenderType() const { return m_eRenderType; }
	void SetRenderType(ERenderType _eRenderType) { m_eRenderType = _eRenderType; }
	
	EMobilityType GetMobility() const { return m_eMobility; }
	void SetMobility(EMobilityType _eMobility) { m_eMobility = _eMobility; }

	/**
	 * @brief 액터의 깊이 값을 불러옵니다.
	 */
	float GetDepthZ() const { return m_fDepthZ; }

	void SetOwnerActor(std::weak_ptr<CActor> _wpOwnerActor) { m_wpOwnerActor = _wpOwnerActor; }
	std::weak_ptr<CActor> GetOwnerActor() const { return m_wpOwnerActor; }

public:
	const FMatrix& GetWorldMatrix() const { return m_matWorld; }

	const FMatrix& GetMouseRotateMatrix() const { return m_matMouseRotate; }
	void SetMouseRotateMatrix(const FMatrix& _matMouseRotate) { m_matMouseRotate = _matMouseRotate; }

	FVector3 GetForwardVector() const;

	FVector3 GetRightVector() const;

	FVector3 GetUpVector() const;

	// 싼데비스탄
	void SetIsTimeSlipped(bool _bIsTimeSlipped) { m_bIsTimeSlipped = _bIsTimeSlipped; }
	bool GetIsTimeSlipped() { return m_bIsTimeSlipped; }

/********************
	Data Members
********************/
private:
	// 액터가 속한 월드
	std::weak_ptr<CWorld> m_wpWorld;

	// 액터가 속한 레벨
	std::weak_ptr<CLevel> m_wpLevel;

	// 액터가 소유한 컴포넌트들
	std::unordered_map<std::wstring, std::shared_ptr<CActorComponent>> m_umapActorComponents;

	// 액터의 루트 컴포넌트
	std::weak_ptr<CSceneComponent> m_wpRootComponent;

	// 액터의 태그
	std::unordered_set<std::wstring> m_usetTags;

	// 액터의 레이어
	std::unordered_set<std::wstring> m_usetLayers;

	// 액터가 소유한 액터들
	std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_umapActors;

	// 액터가 속한 액터
	std::weak_ptr<CActor> m_wpOwnerActor;

protected:
	// 액터의 크기
	FVector3 m_vScale{ 1.0f, 1.0f, 1.0f };

	// 액터의 회전
	FVector3 m_vRotate{ 0.0f, 0.0f, 0.0f };

	// 액터의 이동, 액터의 로컬 좌표
	FVector3 m_vTranslate{ 0.0f, 0.0f, 0.0f };

	// 액터의 월드 좌표
	FVector3 m_vWorldPosition{ 0.0f, 0.0f, 0.0f };

	// 액터의 로컬 행렬
	FMatrix	m_matLocal{};

	// 액터의 월드 행렬
	FMatrix	m_matWorld{};

	// 마우스의 회전 행렬
	FMatrix m_matMouseRotate{};

	// 액터의 렌더 타입
	ERenderType m_eRenderType = ERenderType::NON_ALPHA;

	// 액터의 모빌리티
	EMobilityType m_eMobility = EMobilityType::DYNAMIC;

	// 액터의 이름
	std::wstring m_wstrActorName = L"";

	// 싼데비스탄
	bool m_bIsTimeSlipped = false;

private:
	IDirect3DDevice9* m_pD3DDevice9 = nullptr;

	// 알파 블렌드 깊이 값
	float m_fDepthZ = 0.0f;

	// 충돌 여부
	bool m_bIsCollided = false;
};

