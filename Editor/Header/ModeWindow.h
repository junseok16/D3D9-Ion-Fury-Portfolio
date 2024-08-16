#pragma once
#include "Window.h"

class CEditorLevel;
class CActor;

class CModeWindow : public CWindow
{
public:
	explicit CModeWindow() = default;
	virtual ~CModeWindow() = default;

public:
	virtual void Initialize(std::weak_ptr<CLevel> _wpLevel) override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	void UpdateHeaderTrasform();
		void UpdateSeparaterMesh();				// 메시 타입을 설정합니다.
		void UpdateSeparaterProperty();			// 이름, 태그, 레이어를 설정합니다.
		void UpdateSeparaterTexture();			// 텍스처를 설정합니다.
		void UpdateSeparaterMobility();			// 모빌리티를 설정합니다.
		void UpdateSeparaterAlphaBlend();		// 알파 블랜드를 설정합니다.
		void UpdateSeparaterComponent();		// 콜라이더, 애니메이션 컴포넌트를 설정합니다.
		void UpdateSeparaterPrefab();
			void UpdateButtonCreatePrefab();	// 프리팹을 생성합니다.
			void UpdateButtonRemovePrefab();	// 프리팹을 삭제합니다.
			void UpdateButtonModifyPrefab();	// 프리팹을 수정합니다.

	void UpdateHeaderPrefab();
		void UpdateTabBarItemPrefab();
		void UpdateSeparaterTransform();		// 트랜스폼을 설정합니다.
		void UpdateSeparaterCreateActor();		// 프리팹을 클론합니다.
			void UpdateButtonCreateActor();

	void UpdateHeaderActor();
		void UpdateTabBarItemActor();
		void UpdateSeparaterActor();
		void UpdateButtonRemoveActor();			// 액터를 삭제합니다.
		void UpdateButtonModifyActor();			// 액터를 수정합니다.

	void UpdateMouseInput();
		void UpdateButtonModifyActor
		(
			int32 _iOffsetXT, int32 _iOffsetYT, int32 _iOffsetZT,
			int32 _iOffsetXR, int32 _iOffsetYR, int32 _iOffsetZR,
			int32 _iOffsetXS, int32 _iOffsetYS, int32 _iOffsetZS
		);

/********************
	IMGUI 정보
********************/
private:
	// 레벨 에디터
	std::weak_ptr<CEditorLevel> m_wpEditorLevel;

	// 모드 창 활성화
	bool m_bMode = true;

/******************
	툴 정보
******************/
private:
	// char* 타입의 텍스처 파일 경로
	std::vector<const char*> m_vecD3DFilePaths;

	// char* 타입의 큐브 텍스처 파일 경로
	std::vector<const char*> m_vecD3DCubeFilePaths;

	// 텍스처 포인터들
	std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>> m_vecD3DTextures;

	// 큐브 텍스처 포인터들
	std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>> m_vecD3DCubeTextures;

	// 텍스처 콤보 박스 인덱스
	int32 m_iTextureComboBoxIndex = 0;

	// 큐브 텍스처 콤보 박스 인덱스
	int32 m_iCubeTextureComboBoxIndex = 0;

	// 메시 콤보 박스 인덱스
	int32 m_iMeshComboBoxIndex = 0;

	// 프리팹 리스트 박스 인덱스
	int32 m_iPrefabListBoxIndex = 0;

	// 스폰 리스트 박스 인덱스
	int32 m_iSpawnListBoxIndex = 0;

	// 콜라이더 타입
	int32 m_iColliderType = 0;

	// 콜리전 레이어 타입
	int32 m_iCollisionLayerType = 0;

	// 충돌 레이어 체크 박스 인덱스
	bool m_bCollisionLayer[5] = { false };

	// X, Y, Z축 방향으로 클론할 프리팹 수
	int32 m_iXYZ[3] = { 1 };

	int32 m_iOffset = 0;

	// 모빌리티
	int32 m_iMobility = 0;

	// 알파 블렌드
	int32 m_iAlpha = 0;

	int32 m_iOffsetT = 0;

	int32 m_iOffsetR = 0;

	int32 m_iOffsetS = 0;


/******************
	프리팹 정보
******************/
private:
	char m_chName[64] = { NULL };									// 이름
	EMeshType m_eMeshType = EMeshType::NONE;						// 메시 타입

	char m_chFileName[64] = { NULL };								// 파일 이름
	char m_chFilePath[256] = { NULL };								// 파일 경로
	int32 m_iBeginIndex = 0;
	int32 m_iEndIndex = 0;

	EColliderType m_eColliderType = EColliderType::NONE;
	ECollisionLayerType m_eCollisionLayerType = ECollisionLayerType::ENUM_END;
	int32 m_iCollisionLayer = 0x0000'0000;

	bool m_bMobility = false;
	ERenderType m_eRenderType = ERenderType::NON_ALPHA;

/******************
	스폰 정보
******************/
private:
	char m_chPrefabName[64] = { NULL };								// 프리팹 이름
	char m_chActorName[64] = { NULL };								// 액터 이름

	float m_fActorTranslate[3] = { 0.0f, 0.0f, 0.0f };				// 위치
	float m_fActorRotate[3] = { 0.0f, 0.0f, 0.0f };					// 회전
	float m_fActorScale[3] = { 1.0f, 1.0f, 1.0f };					// 크기

	float m_fScaleU = 1.0f;											// u
	float m_fScaleV = 1.0f;											// v

	float m_fColliderComponentTranslate[3] = { 0.0f, 0.0f, 0.0f };	// 위치
	float m_fColliderComponentRotate[3] = { 0.0f, 0.0f, 0.0f };		// 회전
	float m_fColliderComponentScale[3] = { 1.0f, 1.0f, 1.0f };		// 크기
};

