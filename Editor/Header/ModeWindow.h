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
		void UpdateSeparaterMesh();				// �޽� Ÿ���� �����մϴ�.
		void UpdateSeparaterProperty();			// �̸�, �±�, ���̾ �����մϴ�.
		void UpdateSeparaterTexture();			// �ؽ�ó�� �����մϴ�.
		void UpdateSeparaterMobility();			// �����Ƽ�� �����մϴ�.
		void UpdateSeparaterAlphaBlend();		// ���� ���带 �����մϴ�.
		void UpdateSeparaterComponent();		// �ݶ��̴�, �ִϸ��̼� ������Ʈ�� �����մϴ�.
		void UpdateSeparaterPrefab();
			void UpdateButtonCreatePrefab();	// �������� �����մϴ�.
			void UpdateButtonRemovePrefab();	// �������� �����մϴ�.
			void UpdateButtonModifyPrefab();	// �������� �����մϴ�.

	void UpdateHeaderPrefab();
		void UpdateTabBarItemPrefab();
		void UpdateSeparaterTransform();		// Ʈ�������� �����մϴ�.
		void UpdateSeparaterCreateActor();		// �������� Ŭ���մϴ�.
			void UpdateButtonCreateActor();

	void UpdateHeaderActor();
		void UpdateTabBarItemActor();
		void UpdateSeparaterActor();
		void UpdateButtonRemoveActor();			// ���͸� �����մϴ�.
		void UpdateButtonModifyActor();			// ���͸� �����մϴ�.

	void UpdateMouseInput();
		void UpdateButtonModifyActor
		(
			int32 _iOffsetXT, int32 _iOffsetYT, int32 _iOffsetZT,
			int32 _iOffsetXR, int32 _iOffsetYR, int32 _iOffsetZR,
			int32 _iOffsetXS, int32 _iOffsetYS, int32 _iOffsetZS
		);

/********************
	IMGUI ����
********************/
private:
	// ���� ������
	std::weak_ptr<CEditorLevel> m_wpEditorLevel;

	// ��� â Ȱ��ȭ
	bool m_bMode = true;

/******************
	�� ����
******************/
private:
	// char* Ÿ���� �ؽ�ó ���� ���
	std::vector<const char*> m_vecD3DFilePaths;

	// char* Ÿ���� ť�� �ؽ�ó ���� ���
	std::vector<const char*> m_vecD3DCubeFilePaths;

	// �ؽ�ó �����͵�
	std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>> m_vecD3DTextures;

	// ť�� �ؽ�ó �����͵�
	std::vector<std::pair<std::wstring, IDirect3DBaseTexture9*>> m_vecD3DCubeTextures;

	// �ؽ�ó �޺� �ڽ� �ε���
	int32 m_iTextureComboBoxIndex = 0;

	// ť�� �ؽ�ó �޺� �ڽ� �ε���
	int32 m_iCubeTextureComboBoxIndex = 0;

	// �޽� �޺� �ڽ� �ε���
	int32 m_iMeshComboBoxIndex = 0;

	// ������ ����Ʈ �ڽ� �ε���
	int32 m_iPrefabListBoxIndex = 0;

	// ���� ����Ʈ �ڽ� �ε���
	int32 m_iSpawnListBoxIndex = 0;

	// �ݶ��̴� Ÿ��
	int32 m_iColliderType = 0;

	// �ݸ��� ���̾� Ÿ��
	int32 m_iCollisionLayerType = 0;

	// �浹 ���̾� üũ �ڽ� �ε���
	bool m_bCollisionLayer[5] = { false };

	// X, Y, Z�� �������� Ŭ���� ������ ��
	int32 m_iXYZ[3] = { 1 };

	int32 m_iOffset = 0;

	// �����Ƽ
	int32 m_iMobility = 0;

	// ���� ����
	int32 m_iAlpha = 0;

	int32 m_iOffsetT = 0;

	int32 m_iOffsetR = 0;

	int32 m_iOffsetS = 0;


/******************
	������ ����
******************/
private:
	char m_chName[64] = { NULL };									// �̸�
	EMeshType m_eMeshType = EMeshType::NONE;						// �޽� Ÿ��

	char m_chFileName[64] = { NULL };								// ���� �̸�
	char m_chFilePath[256] = { NULL };								// ���� ���
	int32 m_iBeginIndex = 0;
	int32 m_iEndIndex = 0;

	EColliderType m_eColliderType = EColliderType::NONE;
	ECollisionLayerType m_eCollisionLayerType = ECollisionLayerType::ENUM_END;
	int32 m_iCollisionLayer = 0x0000'0000;

	bool m_bMobility = false;
	ERenderType m_eRenderType = ERenderType::NON_ALPHA;

/******************
	���� ����
******************/
private:
	char m_chPrefabName[64] = { NULL };								// ������ �̸�
	char m_chActorName[64] = { NULL };								// ���� �̸�

	float m_fActorTranslate[3] = { 0.0f, 0.0f, 0.0f };				// ��ġ
	float m_fActorRotate[3] = { 0.0f, 0.0f, 0.0f };					// ȸ��
	float m_fActorScale[3] = { 1.0f, 1.0f, 1.0f };					// ũ��

	float m_fScaleU = 1.0f;											// u
	float m_fScaleV = 1.0f;											// v

	float m_fColliderComponentTranslate[3] = { 0.0f, 0.0f, 0.0f };	// ��ġ
	float m_fColliderComponentRotate[3] = { 0.0f, 0.0f, 0.0f };		// ȸ��
	float m_fColliderComponentScale[3] = { 1.0f, 1.0f, 1.0f };		// ũ��
};

