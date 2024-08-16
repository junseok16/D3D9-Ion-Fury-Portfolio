#include "pch.h"
#include "ModeWindow.h"
#include "EditorLevel.h"

#include "DeviceManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "PrefabManager.h"
#include "SpawnManager.h"
#include "CollisionManager.h"

#include "Actor.h"
#include "RectangleMeshComponent.h"
#include "CubeMeshComponent.h"
#include "RectColliderComponent.h"
#include "CubeColliderComponent.h"
using namespace std;

void CModeWindow::Initialize(std::weak_ptr<CLevel> _wpLevel)
{
	// ������ ��� �ҷ��� string���� const char*�� �����մϴ�.
	const vector<string>& vecStrFilePaths = CResourceManager::GetInstance()->GetStrFilePaths(EResourceType::TEXTURE);
	for (auto& strFilePath : vecStrFilePaths)
	{
		size_t iCursor = strFilePath.find_last_of(".");
		string strExtension = strFilePath.substr(iCursor + 1);

		if (strExtension == "png" || strExtension == "PNG")
		{
			m_vecD3DFilePaths.push_back(strFilePath.c_str());
		}
		else if (strExtension == "dds" || strExtension == "DDS")
		{
			m_vecD3DCubeFilePaths.push_back(strFilePath.c_str());
		}
	}

	// �ؽ�ó �����͵��� �ҷ��ɴϴ�.
	m_vecD3DTextures = CResourceManager::GetInstance()->GetD3DTextures();
	m_vecD3DCubeTextures = CResourceManager::GetInstance()->GetD3DCubeTextures();

	m_wpEditorLevel = dynamic_pointer_cast<CEditorLevel>(_wpLevel.lock());
	CWindow::Initialize(_wpLevel.lock());
}

void CModeWindow::BeginPlay()
{
	CWindow::BeginPlay();
}

int32 CModeWindow::Update(const float& _fDeltaSeconds)
{
	if (ImGui::Begin("Mode"), &m_bMode)
	{
		UpdateHeaderTrasform();
		UpdateHeaderPrefab();
		UpdateHeaderActor();
		UpdateMouseInput();
		ImGui::End();
	}

	return CWindow::Update(_fDeltaSeconds);
}

int32 CModeWindow::LateUpdate(const float& _fDeltaSeconds)
{
	return CWindow::LateUpdate(_fDeltaSeconds);
}

void CModeWindow::Render()
{
	CWindow::Render();
}

void CModeWindow::EndPlay()
{
	CWindow::EndPlay();
}

void CModeWindow::Release()
{
	CWindow::Release();
}

void CModeWindow::UpdateHeaderTrasform()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		UpdateSeparaterMesh();
		UpdateSeparaterTexture();
		UpdateSeparaterProperty();
		UpdateSeparaterMobility();
		UpdateSeparaterAlphaBlend();
		UpdateSeparaterComponent();
	}
}

void CModeWindow::UpdateSeparaterProperty()
{
	// �̸�, �±�, ���̾ �����մϴ�.
	ImGui::SeparatorText("Property");
	ImGui::InputTextWithHint("Name", "Name", m_chName, IM_ARRAYSIZE(m_chName));
	ImGui::Spacing();
}

void CModeWindow::UpdateSeparaterMesh()
{
	std::array<const char*, 3> arrMeshsType = { "NONE", "RECT", "CUBE" };
	ImGui::SeparatorText("Mesh");
	ImGui::Combo("Mesh", &m_iMeshComboBoxIndex, arrMeshsType.data(), (uint32)arrMeshsType.size());
	ImGui::Spacing();

	// �޽� Ÿ���� �����մϴ�.
	switch (m_iMeshComboBoxIndex)
	{
		case 0: m_eMeshType = EMeshType::NONE;		break; 
		case 1: m_eMeshType = EMeshType::RECTANGLE;	break; 
		case 2: m_eMeshType = EMeshType::CUBE;		break;
		default: CHECKF(false, TEXT("Mesh type isn't designated.")); break;
	}
	ImGui::Spacing();
}

void CModeWindow::UpdateSeparaterTexture()
{
	std::array<const char*, 6> arrPlanes = { "+X", "+Y", "+Z", "-X", "-Y", "-Z" };

	switch (m_eMeshType)
	{
	case EMeshType::NONE:
	{
		memset(m_chFileName, 0, sizeof(char) * 64);
		memset(m_chFilePath, 0, sizeof(char) * 256);
		m_iTextureComboBoxIndex = 0;
		m_iCubeTextureComboBoxIndex = 0;
		m_iBeginIndex = 0;
		m_iEndIndex = 0;
	}
	break;

	case EMeshType::RECTANGLE:
	{
		if (ImGui::TreeNode(arrPlanes[0]))
		{
			ImGui::Combo("PNG", &m_iTextureComboBoxIndex, m_vecD3DFilePaths.data(), (uint32)m_vecD3DFilePaths.size());
			ImGui::InputInt("Begin", &m_iBeginIndex);
			ImGui::InputInt("End", &m_iEndIndex);

			if (m_iBeginIndex <= 0) { m_iBeginIndex = 0; }
			if (m_iEndIndex <= 0) { m_iEndIndex = 0; }

			// �̸��� �����մϴ�.
			const wchar* wchName = m_vecD3DTextures[m_iTextureComboBoxIndex].first.c_str();
			int32 iResult = WideCharToMultiByte(CP_UTF8, 0, wchName, -1, m_chName, sizeof(m_chName), NULL, NULL);
			if (iResult <= 0) { CHECKF(false, TEXT("Failed to convert from wchar to char")); }

			// ���� �̸��� �����մϴ�.
			const wchar* wchFileName = m_vecD3DTextures[m_iTextureComboBoxIndex].first.c_str();
			iResult = WideCharToMultiByte(CP_UTF8, 0, wchFileName, -1, m_chFileName, sizeof(m_chFileName), NULL, NULL);
			if (iResult <= 0) { CHECKF(false, TEXT("Failed to convert from wchar to char")); }

			// ���� ��θ� �����մϴ�.
			strcpy_s(m_chFilePath, m_vecD3DFilePaths[m_iTextureComboBoxIndex]);

			// �̹����� ����մϴ�.
			ImGui::Image(m_vecD3DTextures[m_iTextureComboBoxIndex].second, ImVec2(60, 60), ImVec2(0, 0), ImVec2(1, 1));
			ImGui::TreePop();
		}
		ImGui::Spacing();
	}
	break;

	case EMeshType::CUBE:
	{
		m_iBeginIndex = 0;
		m_iEndIndex = 0;

		if (ImGui::TreeNode("DDS"))
		{
			ImGui::Combo("DDS", &m_iCubeTextureComboBoxIndex, m_vecD3DCubeFilePaths.data(), (uint32)m_vecD3DCubeFilePaths.size());

			// �̸��� �����մϴ�.
			const wchar* wchName = m_vecD3DCubeTextures[m_iCubeTextureComboBoxIndex].first.c_str();
			int32 iResult = WideCharToMultiByte(CP_UTF8, 0, wchName, -1, m_chName, sizeof(m_chName), NULL, NULL);
			if (iResult <= 0) { CHECKF(false, TEXT("Failed to convert from wchar to char")); }

			// ���� �̸��� �����մϴ�.
			const wchar* wchFileName = m_vecD3DCubeTextures[m_iCubeTextureComboBoxIndex].first.c_str();
			iResult = WideCharToMultiByte(CP_UTF8, 0, wchFileName, -1, m_chFileName, sizeof(m_chFileName), NULL, NULL);
			if (iResult <= 0) { CHECKF(false, TEXT("Failed to convert from wchar to char")); }

			// ���� ��θ� �����մϴ�.
			strcpy_s(m_chFilePath, m_vecD3DCubeFilePaths[m_iCubeTextureComboBoxIndex]);

			ImGui::Image(m_vecD3DCubeTextures[m_iCubeTextureComboBoxIndex].second, ImVec2(60, 60), ImVec2(0, 0), ImVec2(1, 1));
			ImGui::TreePop();
		}
	}
	break;

	default: CHECKF(false, TEXT("Mesh type isn't designated.")); break;
	}
	ImGui::Spacing();
}

void CModeWindow::UpdateSeparaterMobility()
{
	// �����Ƽ�� �����մϴ�.
	ImGui::SeparatorText("Mobility");
	ImGui::RadioButton("Static", &m_iMobility, 0);
	ImGui::SameLine(); ImGui::RadioButton("Dynamic", &m_iMobility, 1);
	ImGui::Spacing();

	switch (m_iMobility)
	{
	case 0: m_bMobility = false; break;
	case 1: m_bMobility = true; break;
	default: break;
	}
}

void CModeWindow::UpdateSeparaterAlphaBlend()
{
	// ���� ���带 �����մϴ�.
	ImGui::SeparatorText("Alpha");
	ImGui::RadioButton("NonAlpha", &m_iAlpha, 0);
	ImGui::SameLine(); ImGui::RadioButton("AlphaTest", &m_iAlpha, 1);
	ImGui::SameLine(); ImGui::RadioButton("AlphaBlend", &m_iAlpha, 2);
	ImGui::Spacing();

	switch (m_iAlpha)
	{
	case 0: m_eRenderType = ERenderType::NON_ALPHA; break;
	case 1: m_eRenderType = ERenderType::ALPHA_TEST; break;
	case 2: m_eRenderType = ERenderType::ALPHA_BLEND; break;
	default: break;
	}
}

void CModeWindow::UpdateSeparaterComponent()
{
	ImGui::SeparatorText("Component");

	if (ImGui::TreeNode("Collider"))
	{
		// �ݶ��̴� Ÿ���� �����մϴ�.
		std::array<const char*, 3> arrColliderType = { "NONE", "RECT", "CUBE" };
		ImGui::Combo("Collider", &m_iColliderType, arrColliderType.data(), (uint32)arrColliderType.size());

		switch (m_iColliderType)
		{
		case 0:
		{
			m_eColliderType			= EColliderType::NONE;
			m_eCollisionLayerType	= ECollisionLayerType::ENUM_END;
			m_iCollisionLayer		= 0;
		}
		break;

		case 1: m_eColliderType		= EColliderType::RECT; break;
		case 2: m_eColliderType		= EColliderType::CUBE; break;
		default: break;
		}
		ImGui::Spacing();

		if (m_eColliderType != EColliderType::NONE)
		{
			// �ݸ��� ���̾� Ÿ���� �����մϴ�.
			std::array<const char*, 8> arrCollisionLayerTypes = { "PLAYER", "MONSTER", "GROUND", "WALL", "INTERACTION", "ITEM", "ITEM OBJECT", "PROJECTILE" };
			ImGui::Combo("Layer", &m_iCollisionLayerType, arrCollisionLayerTypes.data(), (uint32)arrCollisionLayerTypes.size());

			switch (m_iCollisionLayerType)
			{
			case 0: m_eCollisionLayerType = ECollisionLayerType::PLAYER;		break;
			case 1: m_eCollisionLayerType = ECollisionLayerType::MONSTER;		break;
			case 2: m_eCollisionLayerType = ECollisionLayerType::GROUND;		break;
			case 3: m_eCollisionLayerType = ECollisionLayerType::WALL;			break;
			case 4: m_eCollisionLayerType = ECollisionLayerType::INTERACTION;	break;
			case 5: m_eCollisionLayerType = ECollisionLayerType::ITEM;			break;
			case 6: m_eCollisionLayerType = ECollisionLayerType::ITEMOBJECT;	break;
			case 7: m_eCollisionLayerType = ECollisionLayerType::PROJECTILE;	break;
			default: break;
			}
			ImGui::Spacing();

			// �ݸ��� ���̾ �����մϴ�.
			for (size_t i = 0; i < arrCollisionLayerTypes.size(); ++i)
			{
				if (ImGui::Checkbox(arrCollisionLayerTypes[i], &m_bCollisionLayer[i]))
				{
					if (m_bCollisionLayer[i]) { m_iCollisionLayer |= (1 << i); }
					else { m_iCollisionLayer &= ~(1 << i); }
				}
			}
		}
		ImGui::TreePop();
	}
	ImGui::Spacing();
}

void CModeWindow::UpdateHeaderPrefab()
{
	ImGui::Spacing();
	if (ImGui::CollapsingHeader("Prefab"))
	{
		ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_None;
		ImGui::SeparatorText("Prefab");
		if (ImGui::BeginTabBar("PrefabTabBar", tabBarFlags))
		{
			UpdateTabBarItemPrefab();
			ImGui::EndTabBar();
		}
		ImGui::Spacing();

		UpdateSeparaterPrefab();

		// Ʈ�������� �����մϴ�.
		UpdateSeparaterTransform();

		// ���͸� �����մϴ�.
		UpdateSeparaterCreateActor();
	}
}

void CModeWindow::UpdateTabBarItemPrefab()
{
	if (ImGui::BeginTabItem("Prefab"))
	{
		const vector<pair<wstring, shared_ptr<PrefabData>>>& vecPrefabData = CPrefabManager::GetInstance()->GetPrefabData();

		// ������ ����Ʈ �ڽ��� �׸��� �����Ͽ� �������� ������ �� �ֽ��ϴ�.
		if (ImGui::BeginListBox("Preview", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			for (size_t iIndex = 0; iIndex < vecPrefabData.size(); ++iIndex)
			{
				const bool isRectSelected = (m_iPrefabListBoxIndex == iIndex);
				if (ImGui::Selectable(vecPrefabData[iIndex].second->m_chName, isRectSelected))
				{
					m_iPrefabListBoxIndex = (int32)iIndex;

					// �޽� Ÿ���� �����մϴ�.
					switch (vecPrefabData[iIndex].second->m_eMeshType)
					{
					case EMeshType::NONE:		m_iMeshComboBoxIndex = 0; break;
					case EMeshType::RECTANGLE:	m_iMeshComboBoxIndex = 1; break;
					case EMeshType::CUBE:		m_iMeshComboBoxIndex = 2; break;
					default: CHECKF(false, TEXT("Mesh type isn't designated.")); break;
					}

					// �̸��� �����մϴ�.
					strcpy_s(m_chName, vecPrefabData[iIndex].second->m_chName);
					strcpy_s(m_chFileName, vecPrefabData[iIndex].second->m_chFileName);
					strcpy_s(m_chFilePath, vecPrefabData[iIndex].second->m_chFilePath);
					
					// �ݶ��̴� Ÿ���� �����մϴ�.
					switch (vecPrefabData[iIndex].second->m_eColliderType)
					{
					case EColliderType::NONE:	m_iColliderType = 0; break;
					case EColliderType::RECT:	m_iColliderType = 1; break;
					case EColliderType::CUBE:	m_iColliderType = 2; break;
					default: break;
					}

					// �ݸ��� ���̾� Ÿ���� �����մϴ�.
					switch (vecPrefabData[iIndex].second->m_eCollisionLayerType)
					{
					case ECollisionLayerType::PLAYER:		m_iCollisionLayerType = 0; break;
					case ECollisionLayerType::MONSTER:		m_iCollisionLayerType = 1; break;
					case ECollisionLayerType::GROUND:		m_iCollisionLayerType = 2; break;
					case ECollisionLayerType::WALL:			m_iCollisionLayerType = 3; break;
					case ECollisionLayerType::INTERACTION:	m_iCollisionLayerType = 4; break;
					case ECollisionLayerType::ITEM:			m_iCollisionLayerType = 5; break;
					case ECollisionLayerType::ITEMOBJECT:	m_iCollisionLayerType = 6; break;
					case ECollisionLayerType::PROJECTILE:	m_iCollisionLayerType = 7; break;
					default: break;
					}

					// �ݸ��� ���̾ �����մϴ�.
					for (int32 iFlag = 0; iFlag < 6; ++iFlag)
					{
						if (vecPrefabData[iIndex].second->m_iCollisionLayer & (1 << iFlag)) { m_bCollisionLayer[iFlag] = true; }
						else { m_bCollisionLayer[iFlag] = false; }
					}
					m_iCollisionLayer = vecPrefabData[iIndex].second->m_iCollisionLayer;

					// �����Ƽ�� �����մϴ�.
					if (vecPrefabData[iIndex].second->m_bMobility) { m_iMobility = 1; }
					else { m_iMobility = 0; }

					// ���� ���带 �����մϴ�.
					switch (vecPrefabData[iIndex].second->m_eRenderType)
					{
					case ERenderType::NON_ALPHA:	m_eRenderType = ERenderType::NON_ALPHA;		/*m_iAlpha = 0;*/ break;
					case ERenderType::ALPHA_TEST:	m_eRenderType = ERenderType::ALPHA_TEST;	/*m_iAlpha = 1;*/ break;
					case ERenderType::ALPHA_BLEND:	m_eRenderType = ERenderType::ALPHA_BLEND;	/*m_iAlpha = 2;*/ break;
					default: break;
					}
				}

				if (isRectSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}
}

void CModeWindow::UpdateSeparaterPrefab()
{
	UpdateButtonCreatePrefab();
	UpdateButtonModifyPrefab();
	UpdateButtonRemovePrefab();
}

void CModeWindow::UpdateButtonCreatePrefab()
{
	// �������� �����մϴ�.
	if (ImGui::Button("Create Prefab", ImVec2(120, 25)))
	{
		wstring wstrPrefabName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chName[i] == '\0') { break; }
			wstrPrefabName += m_chName[i];
		}

		// �̸��� ���� �������� �ִ� ���, �������� �ʽ��ϴ�.
		if (CPrefabManager::GetInstance()->FindPrefabData(wstrPrefabName) != nullptr) { return; }

		shared_ptr<PrefabData> spPrefabData(make_shared<PrefabData>());
		strcpy_s(spPrefabData->m_chName, m_chName);
		strcpy_s(spPrefabData->m_chFileName, m_chFileName);
		strcpy_s(spPrefabData->m_chFilePath, m_chFilePath);
		spPrefabData->m_iBeginIndex = m_iBeginIndex;
		spPrefabData->m_iEndIndex = m_iEndIndex;

		spPrefabData->m_eColliderType = m_eColliderType;
		spPrefabData->m_eMeshType = m_eMeshType;
		spPrefabData->m_eCollisionLayerType = m_eCollisionLayerType;
		spPrefabData->m_iCollisionLayer = m_iCollisionLayer;

		spPrefabData->m_bMobility = m_bMobility;
		spPrefabData->m_eRenderType = m_eRenderType;
		CPrefabManager::GetInstance()->AddPrefabData(wstrPrefabName, spPrefabData);
	}
}

void CModeWindow::UpdateButtonModifyPrefab()
{
	ImGui::SameLine();
	if (ImGui::Button("Modify Prefab", ImVec2(120, 25)))
	{
		// char[256] Ÿ���� wstring Ÿ������ ��ȯ�մϴ�.
		wstring wstrPrefabName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chName[i] == '\0') { break; }
			wstrPrefabName += m_chName[i];
		}

		shared_ptr<PrefabData> spPrefabData = CPrefabManager::GetInstance()->FindPrefabData(wstrPrefabName);
		if (!spPrefabData) { return; }

		strcpy_s(spPrefabData->m_chName, m_chName);
		strcpy_s(spPrefabData->m_chFileName, m_chFileName);
		strcpy_s(spPrefabData->m_chFilePath, m_chFilePath);
		spPrefabData->m_iBeginIndex = m_iBeginIndex;
		spPrefabData->m_iEndIndex = m_iEndIndex;

		spPrefabData->m_eColliderType = m_eColliderType;
		spPrefabData->m_eMeshType = m_eMeshType;
		spPrefabData->m_eCollisionLayerType = m_eCollisionLayerType;
		spPrefabData->m_iCollisionLayer = m_iCollisionLayer;

		spPrefabData->m_bMobility = m_bMobility;
		spPrefabData->m_eRenderType = m_eRenderType;
	}
}

void CModeWindow::UpdateButtonRemovePrefab()
{
	ImGui::SameLine();
	if (ImGui::Button("Remove Prefab", ImVec2(120, 25)))
	{
		// char[256] Ÿ���� wstring Ÿ������ ��ȯ�մϴ�.
		wstring wstrPrefabName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chName[i] == '\0') { break; }
			wstrPrefabName += m_chName[i];
		}
		CPrefabManager::GetInstance()->RemovePrefabData(wstrPrefabName);
	}
}

void CModeWindow::UpdateSeparaterTransform()
{
	// ���� Ʈ������
	ImGui::SeparatorText("Actor Transform");
	ImGui::InputFloat3("Translate", m_fActorTranslate);
	ImGui::InputFloat3("Rotate", m_fActorRotate);
	ImGui::InputFloat3("Scale", m_fActorScale);

	ImGui::SeparatorText("UV");
	ImGui::InputFloat("Scale U", &m_fScaleU);
	ImGui::InputFloat("Scale V", &m_fScaleV);

	ImGui::SeparatorText("Collider Component Transform");
	ImGui::InputFloat3("Collider Translate", m_fColliderComponentTranslate);
	ImGui::InputFloat3("Collider Rotate", m_fColliderComponentRotate);
	ImGui::InputFloat3("Collider Scale", m_fColliderComponentScale);
	ImGui::Spacing();

	if (m_iColliderType == (int32)EColliderType::NONE)
	{
		for (int32 i = 0; i < 3; ++i)
		{
			m_fColliderComponentTranslate[i] = 0.0f;
			m_fColliderComponentRotate[i] = 0.0f;
			m_fColliderComponentScale[i] = 1.0f;
		}
	}
	
	if (m_iColliderType == (int32)EColliderType::CUBE)
	{
		m_fScaleU = 1.0f;
		m_fScaleV = 1.0f;
	}
}

void CModeWindow::UpdateSeparaterCreateActor()
{
	if (ImGui::TreeNode("Create Info"))
	{
		ImGui::SeparatorText("Create");
		ImGui::InputInt("Create n by X", &m_iXYZ[0]);
		ImGui::InputInt("Create n by Y", &m_iXYZ[1]);
		ImGui::InputInt("Create n by Z", &m_iXYZ[2]);
		ImGui::InputInt("Offset", &m_iOffset);

		ImGui::SeparatorText("Transform Offset");
		ImGui::InputInt("Transpose Offset", &m_iOffsetT);
		ImGui::InputInt("Rotate Offset", &m_iOffsetR);
		ImGui::InputInt("Scale Offset", &m_iOffsetS);

		ImGui::TreePop();
	}

	for (int32 i = 0; i < 3; ++i) { if (m_iXYZ[i] < 1) { m_iXYZ[i] = 1; } }
	if (m_iOffset <= 0) { m_iOffset = 0; }

	if (m_iOffsetT <= 0) { m_iOffsetT = 0; }
	if (m_iOffsetR <= 0) { m_iOffsetR = 0; }
	if (m_iOffsetS <= 0) { m_iOffsetS = 0; }

	UpdateButtonCreateActor();
}

void CModeWindow::UpdateButtonCreateActor()
{
	if (ImGui::Button("Create Actor", ImVec2(120, 25)))
	{
		for (int32 iX = 0; iX < m_iXYZ[0]; ++iX)
		{
			for (int32 iY = 0; iY < m_iXYZ[1]; ++iY)
			{
				for (int32 iZ = 0; iZ < m_iXYZ[2]; ++iZ)
				{
					float fActorTranslate[3] = { 0 };
					float fActorRotate[3] = { 0 };
					float fActorScale[3] = { 0 };


					float fColliderComponentTranslate[3] = { 0 };
					float fColliderComponentRotate[3] = { 0 };
					float fColliderComponentScale[3] = { 0 };

					fActorTranslate[0] = m_fActorTranslate[0] + m_iOffset * iX;
					fActorTranslate[1] = m_fActorTranslate[1] + m_iOffset * iY;
					fActorTranslate[2] = m_fActorTranslate[2] + m_iOffset * iZ;

					for (int32 i = 0; i < 3; ++i)
					{
						fActorRotate[i] = m_fActorRotate[i];
						fActorScale[i] = m_fActorScale[i];

						fColliderComponentTranslate[i] = m_fColliderComponentTranslate[i];
						fColliderComponentRotate[i] = m_fColliderComponentRotate[i];
						fColliderComponentScale[i] = m_fColliderComponentScale[i];
					}

					float fScaleU = m_fScaleU;
					float fScaleV = m_fScaleV;
					
					// ������ ������ �����ɴϴ�.
					const vector<pair<wstring, shared_ptr<PrefabData>>>& vecPrefabData = CPrefabManager::GetInstance()->GetPrefabData();
					
					// �̸��� ��ȯ�մϴ�.
					wstring wstrActorName = L"";
					string strActorName = "";
					for (int32 i = 0; i < 64; ++i)
					{
						if (vecPrefabData[m_iPrefabListBoxIndex].second->m_chName[i] == '\0') { break; }
						wstrActorName += vecPrefabData[m_iPrefabListBoxIndex].second->m_chName[i];
						strActorName += vecPrefabData[m_iPrefabListBoxIndex].second->m_chName[i];
					}
					
					// ���� ��θ� ��ȯ�մϴ�.
					wstring wstrFilePath = L"";
					for (int32 j = 0; j < 256; ++j)
					{
						if (vecPrefabData[m_iPrefabListBoxIndex].second->m_chFilePath[j] == '\0') { break; }
						wstrFilePath += vecPrefabData[m_iPrefabListBoxIndex].second->m_chFilePath[j];
					}
					
					// ���� �̸��� ��ȯ�մϴ�.
					string strFileName = "";
					wstring wstrFileName = L"";
					for (int32 i = 0; i < 64; ++i)
					{
						if (vecPrefabData[m_iPrefabListBoxIndex].second->m_chFileName[i] == '\0') { break; }
						strFileName += vecPrefabData[m_iPrefabListBoxIndex].second->m_chFileName[i];
						wstrFileName += vecPrefabData[m_iPrefabListBoxIndex].second->m_chFileName[i];
					}
					
					// ���Ϳ� �ĺ��ڸ� ���Դϴ�.
					wstrActorName += (L"_A" + to_wstring(CSpawnManager::m_iID));
					strActorName += ("_A" + to_string(CSpawnManager::m_iID));
					CSpawnManager::m_iID++;

					// ���͸� �����մϴ�.
					CHECK(!m_wpEditorLevel.expired());
					shared_ptr<CActor> spActor = m_wpEditorLevel.lock()->CreateActor<CActor>(wstrActorName, L"", L"");
					
					// �޽� ������Ʈ�� �����մϴ�.
					switch (vecPrefabData[m_iPrefabListBoxIndex].second->m_eMeshType)
					{
					case EMeshType::NONE: break;

					case EMeshType::RECTANGLE:
					{
						// �޽� ������Ʈ�� �����մϴ�.
						shared_ptr<CRectangleMeshComponent> spRectangleMeshComponent = spActor->CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
						spActor->SetRootComponent(spRectangleMeshComponent);
						spRectangleMeshComponent->SetRectangleMeshInfo(wstrFileName, vecPrefabData[m_iPrefabListBoxIndex].second->m_iBeginIndex, vecPrefabData[m_iPrefabListBoxIndex].second->m_iEndIndex);

						// UV ��ǥ�� �����մϴ�.
						spRectangleMeshComponent->SetUVInfo(fScaleU, fScaleV);
						CCollisionManager::GetInstance()->AddPrimitiveComponent(spRectangleMeshComponent);
					}
					break;

					case EMeshType::CUBE:
					{
						shared_ptr<CCubeMeshComponent> spCubeMeshComponent = spActor->CreateActorComponent<CCubeMeshComponent>(L"CubeMeshComponent");
						spActor->SetRootComponent(spCubeMeshComponent);
						spCubeMeshComponent->SetCubeMeshInfo(wstrFileName);
						spCubeMeshComponent->SetUVInfo(1.0f, 1.0f);
						CCollisionManager::GetInstance()->AddPrimitiveComponent(spCubeMeshComponent);
					}
					break;

					default: CHECKF(false, TEXT("Mesh type is wrong.")); break;
					}

					// Ʈ�������� �����մϴ�.
					spActor->SetActorPosition({ fActorTranslate[0], fActorTranslate[1], fActorTranslate[2] });
					spActor->SetActorRotation({ fActorRotate[0], fActorRotate[1], fActorRotate[2] });
					spActor->SetActorScale({ fActorScale[0], fActorScale[1], fActorScale[2] });

					// �ݶ��̴� ������Ʈ�� �����մϴ�.
					switch (vecPrefabData[m_iPrefabListBoxIndex].second->m_eColliderType)
					{
					case EColliderType::NONE: break;
					case EColliderType::RECT: break;
					case EColliderType::CUBE:
					{
						weak_ptr<CCubeColliderComponent> spCubeColliderComponent = spActor->CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
						
						// �޽ð� ������Ʈ�� ���� ���, �ݶ��̴� ������Ʈ�� ��Ʈ ������Ʈ�� �˴ϴ�.
						if (vecPrefabData[m_iPrefabListBoxIndex].second->m_eMeshType == EMeshType::NONE) { spActor->SetRootComponent(spCubeColliderComponent); }

						// �޽ð� ������Ʈ�� �ִ� ���
						else { spCubeColliderComponent.lock()->SetOwnerComponent(spActor->GetRootComponent()); }
						
						spCubeColliderComponent.lock()->SetComponentLocalPosition({ fColliderComponentTranslate[0], fColliderComponentTranslate[1], fColliderComponentTranslate[2] });
						spCubeColliderComponent.lock()->SetComponentRotation({ fColliderComponentRotate[0], fColliderComponentRotate[1], fColliderComponentRotate[2] });
						spCubeColliderComponent.lock()->SetComponentScale({ fColliderComponentScale[0], fColliderComponentScale[1], fColliderComponentScale[2] });
						CCollisionManager::GetInstance()->AddColliderComponent(spCubeColliderComponent);
					}
					break;

					default: CHECKF(false, TEXT("Collider type is wrong.")) break;
					}

					// ���� Ÿ���� �����մϴ�.
					switch (vecPrefabData[m_iPrefabListBoxIndex].second->m_eRenderType)
					{
					case ERenderType::NON_ALPHA:	spActor->SetRenderType(ERenderType::NON_ALPHA);		break;
					case ERenderType::ALPHA_TEST:	spActor->SetRenderType(ERenderType::ALPHA_TEST);	break;
					case ERenderType::ALPHA_BLEND:	spActor->SetRenderType(ERenderType::ALPHA_BLEND);	break;
					case ERenderType::ORTHOGONAL:														break;
					case ERenderType::USER_INTERFACE:													break;
					default:																			break;
					}

					spActor->Initialize();
					spActor->BeginPlay();

					// Ʈ������ ������ ���� �Ŵ����� �����մϴ�.
					shared_ptr<SpawnData> spSpawnData(make_shared<SpawnData>());
					strcpy_s(spSpawnData->m_chName, vecPrefabData[m_iPrefabListBoxIndex].second->m_chName);

					for (int32 i = 0; i < 3; ++i)
					{
						// Ʈ�������� �����մϴ�.
						spSpawnData->m_fActorTranslate[i] = fActorTranslate[i];
						spSpawnData->m_fActorRotate[i] = fActorRotate[i];
						spSpawnData->m_fActorScale[i] = fActorScale[i];

						spSpawnData->m_fColliderComponentTranslate[i] = fColliderComponentTranslate[i];
						spSpawnData->m_fColliderComponentRotate[i] = fColliderComponentRotate[i];
						spSpawnData->m_fColliderComponentScale[i] = fColliderComponentScale[i];
					}

					// UV ��ǥ�� �����մϴ�.
					spSpawnData->m_fScaleU = fScaleU;
					spSpawnData->m_fScaleV = fScaleV;

					CSpawnManager::GetInstance()->AddSpawnData(strActorName, spSpawnData);
				}
			}
		}
	}
}

void CModeWindow::UpdateHeaderActor()
{
	ImGui::Spacing();
	if (ImGui::CollapsingHeader("Actor Header"))
	{
		ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_None;
		ImGui::SeparatorText("Actor");
		if (ImGui::BeginTabBar("ActorTabBar", tabBarFlags))
		{
			UpdateTabBarItemActor();
			
			ImGui::EndTabBar();
		}

		// �������� ���ͷ� �ν��Ͻ�ȭ�մϴ�.
		UpdateSeparaterActor();
	}
}

void CModeWindow::UpdateTabBarItemActor()
{
	if (ImGui::BeginTabItem("Actor Tab"))
	{
		if (ImGui::BeginListBox("Actor Listbox", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
		{
			const vector<pair<string, shared_ptr<SpawnData>>>& vecSpawnData = CSpawnManager::GetInstance()->GetSpawnData();

			for (size_t iIndex = 0; iIndex < vecSpawnData.size(); ++iIndex)
			{
				const bool isRectSelected = (m_iSpawnListBoxIndex == iIndex);
				if (ImGui::Selectable(vecSpawnData[iIndex].first.c_str(), isRectSelected))
				{
					m_iSpawnListBoxIndex = (int32)iIndex;

					for (int32 i = 0; i < 3; ++i)
					{
						m_fActorTranslate[i] = vecSpawnData[iIndex].second->m_fActorTranslate[i];
						m_fActorRotate[i]= vecSpawnData[iIndex].second->m_fActorRotate[i];
						m_fActorScale[i]= vecSpawnData[iIndex].second->m_fActorScale[i];

						m_fColliderComponentTranslate[i]= vecSpawnData[iIndex].second->m_fColliderComponentTranslate[i];
						m_fColliderComponentRotate[i]= vecSpawnData[iIndex].second->m_fColliderComponentRotate[i];
						m_fColliderComponentScale[i]= vecSpawnData[iIndex].second->m_fColliderComponentScale[i];
					}

					m_fScaleU = vecSpawnData[iIndex].second->m_fScaleU;
					m_fScaleV = vecSpawnData[iIndex].second->m_fScaleV;
				}

				if (isRectSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndTabItem();
	}
}

void CModeWindow::UpdateSeparaterActor()
{
	ImGui::SeparatorText("Actor Separater");
	UpdateButtonModifyActor();
	UpdateButtonRemoveActor();
}

void CModeWindow::UpdateButtonRemoveActor()
{
	ImGui::SameLine();
	if (ImGui::Button("Remove Actor", ImVec2(120, 25)))
	{
		// ���� �����͸� �ҷ��ɴϴ�.
		vector<pair<string, shared_ptr<SpawnData>>>& vecSpawnData = CSpawnManager::GetInstance()->GetSpawnData();

		string strActorName = vecSpawnData[m_iSpawnListBoxIndex].first;
		wstring wstrActorName(strActorName.begin(), strActorName.end());

		// ���� �����͸� �����մϴ�.
		auto iter = vecSpawnData.begin() + m_iSpawnListBoxIndex;
		vecSpawnData.erase(iter);

		// ���͸� �����մϴ�.
		m_wpEditorLevel.lock()->RemoveActor(wstrActorName);
	}
}

void CModeWindow::UpdateButtonModifyActor()
{
	if (ImGui::Button("Modify Actor", ImVec2(120, 25)))
	{

/***********************
	���� ������ ����
***********************/
		// ���� �����͸� �ҷ��ɴϴ�.
		const vector<pair<string, shared_ptr<SpawnData>>>& vecSpawnData = CSpawnManager::GetInstance()->GetSpawnData();
		
		// ������ ������ ���� �����͸� �����մϴ�.
		for (int32 i = 0; i < 3; ++i)
		{
			vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[i] = m_fActorTranslate[i];
			vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[i] = m_fActorRotate[i];
			vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[i] = m_fActorScale[i];
			vecSpawnData[m_iSpawnListBoxIndex].second->m_fColliderComponentTranslate[i] = m_fColliderComponentTranslate[i];
			vecSpawnData[m_iSpawnListBoxIndex].second->m_fColliderComponentRotate[i] = m_fColliderComponentRotate[i];
			vecSpawnData[m_iSpawnListBoxIndex].second->m_fColliderComponentScale[i] = m_fColliderComponentScale[i];
		}

/***********************
	���� ����
***********************/
		string strActorName = vecSpawnData[m_iSpawnListBoxIndex].first;
		wstring wstrActorName(strActorName.begin(), strActorName.end());

		// ������ ���͸� �����մϴ�.
		std::shared_ptr<CActor> spActor = m_wpEditorLevel.lock()->FindActor(wstrActorName);
		spActor->SetActorPosition({ m_fActorTranslate[0], m_fActorTranslate[1], m_fActorTranslate[2] });
		spActor->SetActorRotation({ m_fActorRotate[0], m_fActorRotate[1], m_fActorRotate[2] });
		spActor->SetActorScale({ m_fActorScale[0], m_fActorScale[1], m_fActorScale[2] });

		// �ݶ��̴� ������Ʈ�� �ִ� ���(�ӽ÷� ���̳��� ĳ������ Ȱ���մϴ�.)
		std::weak_ptr<CRectColliderComponent> spPlaneColliderComponent = dynamic_pointer_cast<CRectColliderComponent>(spActor->FindActorComponent(L"PlaneColliderComponent"));
		std::weak_ptr<CCubeColliderComponent> spCubeColliderComponent = dynamic_pointer_cast<CCubeColliderComponent>(spActor->FindActorComponent(L"CubeColliderComponent"));

		if (spPlaneColliderComponent.lock() != nullptr)
		{
			spPlaneColliderComponent.lock()->SetComponentLocalPosition({ m_fColliderComponentTranslate[0], m_fColliderComponentTranslate[1], m_fColliderComponentTranslate[2] });
			spPlaneColliderComponent.lock()->SetComponentRotation({ m_fColliderComponentRotate[0], m_fColliderComponentRotate[1], m_fColliderComponentRotate[2] });
			spPlaneColliderComponent.lock()->SetComponentScale({ m_fColliderComponentScale[0], m_fColliderComponentScale[1], m_fColliderComponentScale[2] });
		}
		else if (spCubeColliderComponent.lock() != nullptr)
		{
			spCubeColliderComponent.lock()->SetComponentLocalPosition({ m_fColliderComponentTranslate[0], m_fColliderComponentTranslate[1], m_fColliderComponentTranslate[2] });
			spCubeColliderComponent.lock()->SetComponentRotation({ m_fColliderComponentRotate[0], m_fColliderComponentRotate[1], m_fColliderComponentRotate[2] });
			spCubeColliderComponent.lock()->SetComponentScale({ m_fColliderComponentScale[0], m_fColliderComponentScale[1], m_fColliderComponentScale[2] });
		}
	}
}

void CModeWindow::UpdateMouseInput()
{
	if (CInputManager::GetInstance()->IsMouseDown(EMouseButtonType::RIGHT_BUTTON))
	{
		FMatrix matView;
		CDeviceManager::GetInstance()->GetDirect3DDevice9()->GetTransform(D3DTS_VIEW, &matView);

		// ī�޶��� ���� ��ǥ�� ���մϴ�.
		FMatrix matEditorCamera;
		D3DXMatrixInverse(&matEditorCamera, 0, &matView);

		POINT ptMouse{};
		::GetCursorPos(&ptMouse);
		::ScreenToClient(CDeviceManager::GetInstance()->GethWnd(), &ptMouse);

		FVector3 vCameraPos = { matEditorCamera._41, matEditorCamera._42, matEditorCamera._43 };
		shared_ptr<CActor> spActor = CCollisionManager::IntersectRayToActor(vCameraPos, ptMouse);

		unordered_map<wstring, shared_ptr<CActor>> umapActors = m_wpEditorLevel.lock()->GetActors();

		const vector<pair<string, shared_ptr<SpawnData>>>& vecSpawnData = CSpawnManager::GetInstance()->GetSpawnData();

		for (const auto& pair : umapActors)
		{
			if (pair.second != spActor) { continue; }
			
			for (int32 i = 0; i < vecSpawnData.size(); ++i)
			{
				wstring wstrName = L"";
				for (int32 j = 0; j < vecSpawnData[i].first.size(); ++j)
				{
					wstrName += vecSpawnData[i].first[j];
				}

				if (wstrName == pair.first)
				{
					m_iSpawnListBoxIndex = i;
				}
			}
		}
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_Q))
	{
		if (CInputManager::GetInstance()->IsKeyDown(DIK_UPARROW))
		{
			UpdateButtonModifyActor(m_iOffsetT, 0, 0, 0, 0, 0, 0, 0, 0);
		}

		if (CInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW))
		{
			UpdateButtonModifyActor(-m_iOffsetT, 0, 0, 0, 0, 0, 0, 0, 0);
		}
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_W))
	{
		if (CInputManager::GetInstance()->IsKeyDown(DIK_UPARROW))
		{
			UpdateButtonModifyActor(0, m_iOffsetT, 0, 0, 0, 0, 0, 0, 0);
		}

		if (CInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW))
		{
			UpdateButtonModifyActor(0, -m_iOffsetT, 0, 0, 0, 0, 0, 0, 0);
		}
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_E))
	{
		if (CInputManager::GetInstance()->IsKeyDown(DIK_UPARROW))
		{
			UpdateButtonModifyActor(0, 0, m_iOffsetT, 0, 0, 0, 0, 0, 0);

		}

		if (CInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW))
		{
			UpdateButtonModifyActor(0, 0, -m_iOffsetT, 0, 0, 0, 0, 0, 0);
		}
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_A))
	{
		if (CInputManager::GetInstance()->IsKeyDown(DIK_UPARROW))
		{
			UpdateButtonModifyActor(0, 0, 0, m_iOffsetR, 0, 0, 0, 0, 0);
		}

		if (CInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW))
		{
			UpdateButtonModifyActor(0, 0, 0, -m_iOffsetR, 0, 0, 0, 0, 0);
		}
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_S))
	{
		if (CInputManager::GetInstance()->IsKeyDown(DIK_UPARROW))
		{
			UpdateButtonModifyActor(0, 0, 0, 0, m_iOffsetR, 0, 0, 0, 0);
		}

		if (CInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW))
		{
			UpdateButtonModifyActor(0, 0, 0, 0, -m_iOffsetR, 0, 0, 0, 0);
		}
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_D))
	{
		if (CInputManager::GetInstance()->IsKeyDown(DIK_UPARROW))
		{
			UpdateButtonModifyActor(0, 0, 0, 0, 0, -m_iOffsetR, 0, 0, 0);
		}

		if (CInputManager::GetInstance()->IsKeyDown(DIK_DOWNARROW))
		{
			UpdateButtonModifyActor(0, 0, 0, 0, 0, -m_iOffsetR, 0, 0, 0);
		}
	}
}

void CModeWindow::UpdateButtonModifyActor
(
	int32 _iOffsetXT, int32 _iOffsetYT, int32 _iOffsetZT,
	int32 _iOffsetXR, int32 _iOffsetYR, int32 _iOffsetZR,
	int32 _iOffsetXS, int32 _iOffsetYS, int32 _iOffsetZS
)
{
	if (m_iSpawnListBoxIndex < 0) { return; }

	/***********************
		���� ������ ����
	***********************/
	// ���� �����͸� �ҷ��ɴϴ�.
	const vector<pair<string, shared_ptr<SpawnData>>>& vecSpawnData = CSpawnManager::GetInstance()->GetSpawnData();

	// ������ ������ ���� �����͸� �����մϴ�.

	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[0] += static_cast<float>(_iOffsetXT);
	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[1] += static_cast<float>(_iOffsetYT);
	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[2] += static_cast<float>(_iOffsetZT);

	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[0] += static_cast<float>(_iOffsetXR);
	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[1] += static_cast<float>(_iOffsetYR);
	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[2] += static_cast<float>(_iOffsetZR);

	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[0] += static_cast<float>(_iOffsetXS);
	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[1] += static_cast<float>(_iOffsetYS);
	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[2] += static_cast<float>(_iOffsetZS);

	/***********************
		���� ����
	***********************/
	string strActorName = vecSpawnData[m_iSpawnListBoxIndex].first;
	wstring wstrActorName(strActorName.begin(), strActorName.end());

	// ������ ���͸� �����մϴ�.
	std::shared_ptr<CActor> spActor = m_wpEditorLevel.lock()->FindActor(wstrActorName);
	spActor->SetActorPosition({ vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[0],	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[1],	vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorTranslate[2] });
	spActor->SetActorRotation({ vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[0],		vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[1],		vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorRotate[2] });
	spActor->SetActorScale	 ({ vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[0],		vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[1],		vecSpawnData[m_iSpawnListBoxIndex].second->m_fActorScale[2] });
}

