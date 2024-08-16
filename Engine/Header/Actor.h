#pragma once
#include "Object.h"

class CWorld;
class CLevel;
class CActorComponent;
class CSceneComponent;
class CPrimitiveComponent;
class CColliderComponent;

/**
 * @brief	���� Ŭ�����Դϴ�.
 * @details ���� Ŭ����(���� ������Ʈ Ŭ����)
 * @author	Ź�ؼ�
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
	 * @brief ���ο� ���� ������Ʈ�� �����մϴ�.
	 * @details �� �޼���� �ܺο��� ���� ������Ʈ ���ڿ��� Ű(key)�� �ϴ� ���� ������Ʈ�� �����մϴ�.
	 * @return std::shared_ptr<T> ���� ������ ���� ������Ʈ�� �ξ�� �����͸� ��ȯ�մϴ�.
	 * @param[in] _wstrActorComponent ���� ������Ʈ ���ڿ�
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
	 * @brief ������ Ʈ�������� ������Ʈ�մϴ�.
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
	 * @brief ���Ͱ� ���� ���带 �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetWorld(std::weak_ptr<CWorld> _wpWorld) { m_wpWorld = _wpWorld; }
	std::weak_ptr<CWorld> GetWorld() const { CHECK(!m_wpWorld.expired()); return m_wpWorld; }

	/**
	 * @brief ���Ͱ� ���� ������ �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetLevel(std::weak_ptr<CLevel> _wpLevel) { m_wpLevel = _wpLevel; }
	std::weak_ptr<CLevel> GetLevel() const { CHECK(!m_wpLevel.expired()); return m_wpLevel; }

	/**
	 * @brief ������ �±׸� �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetActorTag(const std::wstring& _wstrTag) { m_usetTags.insert(_wstrTag); }
	std::unordered_set<std::wstring>& GetActorTag() { return m_usetTags; }
	
	/**
	 * @brief ������ ���̾ �����ϰų� �ҷ��ɴϴ�.
	 */
	// 11.11 const ���ľ ���� ���·δ� uset�� find�Լ��� ����� �۵����� �ʾ� const�� �������ϴ�. -���� -
	void SetActorLayer(const std::wstring& _wstrLayer) { m_usetLayers.insert(_wstrLayer); }
	std::unordered_set<std::wstring>& GetActorLayer() { return m_usetLayers; }

	/**
	 * @brief ������ ���� ��ǥ�� �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetActorPosition(const FVector3& _vTranslate) { m_vTranslate = _vTranslate; }
	const FVector3& GetActorPosition() const { return m_vTranslate; }

	/**
	 * @brief ������ ���� ��ǥ�� �ҷ��ɴϴ�.
	 */
	const FVector3& GetActorWorldPosition() const { return m_vWorldPosition; }

	/**
	 * @brief ������ ȸ���� �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetActorRotation(const FVector3& _vRotate) { m_vRotate = _vRotate; }
	const FVector3& GetActorRotation() const { return m_vRotate; }
	
	/**
	 * @brief ������ ũ�⸦ �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetActorScale(const FVector3& _vScale) { m_vScale = _vScale; }
	const FVector3& GetActorScale() const { return m_vScale; }
	
	/**
	 * @brief ������ ��Ʈ ������Ʈ�� �����ϰų� �ҷ��ɴϴ�.
	 */
	void SetRootComponent(std::weak_ptr<CSceneComponent> _wpSceneComponent);
	std::weak_ptr<CSceneComponent> GetRootComponent() const { return m_wpRootComponent; }

	/**
	 * @brief ������ �̸��� �����ϰų� �ҷ��ɴϴ�. 10.30 - �ڵ��� -
	 */
	void SetActorName(const std::wstring& _wstrActorName) { m_wstrActorName = _wstrActorName; }
	const std::wstring& GetActorName() { return m_wstrActorName; }

	// �ӽ� �ڵ�
	void SetIsCollided(bool _bIsCollided) { m_bIsCollided = _bIsCollided; }
	bool GetIsCollided() { return m_bIsCollided; }

	ERenderType GetRenderType() const { return m_eRenderType; }
	void SetRenderType(ERenderType _eRenderType) { m_eRenderType = _eRenderType; }
	
	EMobilityType GetMobility() const { return m_eMobility; }
	void SetMobility(EMobilityType _eMobility) { m_eMobility = _eMobility; }

	/**
	 * @brief ������ ���� ���� �ҷ��ɴϴ�.
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

	// �ѵ���ź
	void SetIsTimeSlipped(bool _bIsTimeSlipped) { m_bIsTimeSlipped = _bIsTimeSlipped; }
	bool GetIsTimeSlipped() { return m_bIsTimeSlipped; }

/********************
	Data Members
********************/
private:
	// ���Ͱ� ���� ����
	std::weak_ptr<CWorld> m_wpWorld;

	// ���Ͱ� ���� ����
	std::weak_ptr<CLevel> m_wpLevel;

	// ���Ͱ� ������ ������Ʈ��
	std::unordered_map<std::wstring, std::shared_ptr<CActorComponent>> m_umapActorComponents;

	// ������ ��Ʈ ������Ʈ
	std::weak_ptr<CSceneComponent> m_wpRootComponent;

	// ������ �±�
	std::unordered_set<std::wstring> m_usetTags;

	// ������ ���̾�
	std::unordered_set<std::wstring> m_usetLayers;

	// ���Ͱ� ������ ���͵�
	std::unordered_map<std::wstring, std::weak_ptr<CActor>> m_umapActors;

	// ���Ͱ� ���� ����
	std::weak_ptr<CActor> m_wpOwnerActor;

protected:
	// ������ ũ��
	FVector3 m_vScale{ 1.0f, 1.0f, 1.0f };

	// ������ ȸ��
	FVector3 m_vRotate{ 0.0f, 0.0f, 0.0f };

	// ������ �̵�, ������ ���� ��ǥ
	FVector3 m_vTranslate{ 0.0f, 0.0f, 0.0f };

	// ������ ���� ��ǥ
	FVector3 m_vWorldPosition{ 0.0f, 0.0f, 0.0f };

	// ������ ���� ���
	FMatrix	m_matLocal{};

	// ������ ���� ���
	FMatrix	m_matWorld{};

	// ���콺�� ȸ�� ���
	FMatrix m_matMouseRotate{};

	// ������ ���� Ÿ��
	ERenderType m_eRenderType = ERenderType::NON_ALPHA;

	// ������ �����Ƽ
	EMobilityType m_eMobility = EMobilityType::DYNAMIC;

	// ������ �̸�
	std::wstring m_wstrActorName = L"";

	// �ѵ���ź
	bool m_bIsTimeSlipped = false;

private:
	IDirect3DDevice9* m_pD3DDevice9 = nullptr;

	// ���� ���� ���� ��
	float m_fDepthZ = 0.0f;

	// �浹 ����
	bool m_bIsCollided = false;
};

