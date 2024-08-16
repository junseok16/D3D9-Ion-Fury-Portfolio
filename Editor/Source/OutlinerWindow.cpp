#include "pch.h"
#include "OutlinerWindow.h"
#include "EditorLevel.h"

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

void COutlinerWindow::Initialize(std::weak_ptr<CLevel> _wpLevel)
{
	m_wpEditorLevel = dynamic_pointer_cast<CEditorLevel>(_wpLevel.lock());

	// 텍스처 포인터들을 불러옵니다.
	CWindow::Initialize(_wpLevel.lock());
}

void COutlinerWindow::BeginPlay()
{
	CWindow::BeginPlay();
}

int32 COutlinerWindow::Update(const float& _fDeltaSeconds)
{
	if (ImGui::Begin("Outliner"), &m_bOutliner)
	{
		UpdateHeaderFile();
		ImGui::End();
	}
	return CWindow::Update(_fDeltaSeconds);
}

int32 COutlinerWindow::LateUpdate(const float& _fDeltaSeconds)
{
	return CWindow::LateUpdate(_fDeltaSeconds);
}

void COutlinerWindow::Render()
{
	CWindow::Render();
}

void COutlinerWindow::EndPlay()
{
	CWindow::EndPlay();
}

void COutlinerWindow::Release()
{
	CWindow::Release();
}

void COutlinerWindow::UpdateHeaderFile()
{
	ImGui::Spacing();
	if (ImGui::CollapsingHeader("File"))
	{
		UpdateSeparatorPrefabData();
		UpdateSeparatorSpawnbData();
	}
}

void COutlinerWindow::UpdateSeparatorPrefabData()
{
	ImGui::SeparatorText("Prefab File");
	ImGui::InputTextWithHint("Prefab Data", "Stage00_Prefab", m_chPrefabDataFileName, IM_ARRAYSIZE(m_chPrefabDataFileName));

	if (ImGui::Button("Save Prefab", ImVec2(120, 25)))
	{
		wstring wstrPrefabDataFileName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chPrefabDataFileName[i] == '\0') { break; }
			else { wstrPrefabDataFileName += m_chPrefabDataFileName[i]; }
		}

		const wstring& wstrDataPath = CResourceManager::GetInstance()->GetDataPath();

		// 프리팹 데이터를 불러옵니다.
		const vector<pair<wstring, shared_ptr<PrefabData>>>& vecPrefabData = CPrefabManager::GetInstance()->GetPrefabData();
		ofstream ostrWriteFile(wstrDataPath + wstrPrefabDataFileName + L".dat", ios::out | ios::binary);

		if (ostrWriteFile.is_open())
		{
			for (const auto& PrefabDatum : vecPrefabData)
			{
				ostrWriteFile.write(reinterpret_cast<char*>(PrefabDatum.second.get()), sizeof(PrefabData));
			}
			ostrWriteFile.close();
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Load Prefab", ImVec2(120, 25)))
	{
		wstring wstrPrefabDataFileName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chPrefabDataFileName[i] == '\0') { break; }
			else { wstrPrefabDataFileName += m_chPrefabDataFileName[i]; }
		}

		// 프리팹 데이터를 읽는다.
		const wstring& wstrDataPath = CResourceManager::GetInstance()->GetDataPath();
		ifstream istrReadFile(wstrDataPath + wstrPrefabDataFileName + L".dat", ios::in | ios::binary);

		if (!istrReadFile.is_open())
		{
			CHECKF(false, TEXT("Failed to open this prefab file!"));
			return;
		}
		
		while (!istrReadFile.eof())
		{
			shared_ptr<PrefabData> spPrefabData(make_shared<PrefabData>());
			istrReadFile.read(reinterpret_cast<char*>(spPrefabData.get()), sizeof(PrefabData));

			if (istrReadFile.eof()) { break; }

			wstring wstrPrefabName = L"";
			for (int32 i = 0; i < 64; ++i)
			{
				if (spPrefabData->m_chName[i] == '\0') { break; }
				wstrPrefabName += spPrefabData->m_chName[i];
			}

			CPrefabManager::GetInstance()->AddPrefabData(wstrPrefabName, spPrefabData);
		}
		istrReadFile.close();
	}
}

void COutlinerWindow::UpdateSeparatorSpawnbData()
{
	ImGui::SeparatorText("Spawn File");
	ImGui::InputTextWithHint("Spawn Data", "Stage00_Spawn", m_chSpawnDataFileName, IM_ARRAYSIZE(m_chSpawnDataFileName));

	if (ImGui::Button("Save Spawn", ImVec2(120, 25)))
	{
		wstring wstrSpawnDataFileName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chSpawnDataFileName[i] == '\0') { break; }
			else { wstrSpawnDataFileName += m_chSpawnDataFileName[i]; }
		}

		const wstring& wstrDataPath = CResourceManager::GetInstance()->GetDataPath();
		ofstream ostrWriteFile(wstrDataPath + wstrSpawnDataFileName + L".dat", ios::out | ios::binary);

		const vector<pair<string, shared_ptr<SpawnData>>>& vecSpawnData = CSpawnManager::GetInstance()->GetSpawnData();
		if (ostrWriteFile.is_open())
		{
			for (const auto& pair : vecSpawnData)
			{
				ostrWriteFile.write(reinterpret_cast<char*>(pair.second.get()), sizeof(SpawnData));
			}
			ostrWriteFile.close();
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Load Spawn", ImVec2(120, 25)))
	{
		wstring wstrSpawnDataFileName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_chSpawnDataFileName[i] == '\0') { break; }
			else { wstrSpawnDataFileName += m_chSpawnDataFileName[i]; }
		}

		// 스폰 데이터를 읽는다.
		const wstring& wstrDataPath = CResourceManager::GetInstance()->GetDataPath();
		ifstream istrReadFile(wstrDataPath + wstrSpawnDataFileName + L".dat", ios::in | ios::binary);
		if (!istrReadFile.is_open()) { CHECKF(false, TEXT("Failed to open this spawn file!")); return; }
		
		while (!istrReadFile.eof())
		{
			/*********************************************
				스폰 매니저에 스폰 데이터를 저장합니다.
			*********************************************/

			shared_ptr<SpawnData> spSpawnData(make_shared<SpawnData>());
			istrReadFile.read(reinterpret_cast<char*>(spSpawnData.get()), sizeof(SpawnData));

			if (istrReadFile.eof()) { break; }

			string strActorName = "";
			wstring wstrActorName = L"";
			for (int32 i = 0; i < 64; ++i)
			{
				if (spSpawnData->m_chName[i] == '\0') { break; }
				strActorName += spSpawnData->m_chName[i];
				wstrActorName += spSpawnData->m_chName[i];
			}

			wstring wstrActorName_A = wstrActorName + L"_A" + to_wstring(CSpawnManager::m_iID);
			string strActorName_A = strActorName + "_A" + to_string(CSpawnManager::m_iID);
			CSpawnManager::m_iID++;

			CSpawnManager::GetInstance()->AddSpawnData(strActorName_A, spSpawnData);
			
			/*********************************************
				프리팹을 클론해 액터를 생성합니다.
			*********************************************/
			const vector<pair<wstring, shared_ptr<PrefabData>>>& vecPrefabData = CPrefabManager::GetInstance()->GetPrefabData();

			// 액터를 생성합니다.
			CHECK(!m_wpEditorLevel.expired());
			shared_ptr<CActor> spActor = m_wpEditorLevel.lock()->CreateActor<CActor>(wstrActorName_A, L"", L"");

			for (const auto& pair : vecPrefabData)
			{
				if (pair.first != wstrActorName) { continue; }

				// 파일 이름을 변환합니다.
				string strFileName = "";
				wstring wstrFileName = L"";
				for (int32 i = 0; i < 64; ++i)
				{
					if (pair.second->m_chFileName[i] == '\0') { break; }
					strFileName += pair.second->m_chFileName[i];
					wstrFileName += pair.second->m_chFileName[i];
				}

				// 메시 컴포넌트를 설정합니다.
				switch (pair.second->m_eMeshType)
				{
				case EMeshType::NONE: break;

				case EMeshType::RECTANGLE:
				{
					shared_ptr<CRectangleMeshComponent> spRectangleMeshComponent = spActor->CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
					spActor->SetRootComponent(spRectangleMeshComponent);
					spRectangleMeshComponent->SetUVInfo(spSpawnData->m_fScaleU, spSpawnData->m_fScaleV);
					spRectangleMeshComponent->SetRectangleMeshInfo(wstrFileName, pair.second->m_iBeginIndex, pair.second->m_iEndIndex);
					CCollisionManager::GetInstance()->AddPrimitiveComponent(spRectangleMeshComponent);
				}
				break;

				case EMeshType::CUBE:
				{
					shared_ptr<CCubeMeshComponent> spCubeMeshComponent = spActor->CreateActorComponent<CCubeMeshComponent>(L"CubeMeshComponent");
					spActor->SetRootComponent(spCubeMeshComponent);
					spCubeMeshComponent->SetCubeMeshInfo(wstrFileName);
					CCollisionManager::GetInstance()->AddPrimitiveComponent(spCubeMeshComponent);
				}
				break;

				default: break;
				}

				// 트랜스폼을 설정합니다.
				spActor->SetActorScale({ spSpawnData->m_fActorScale[0], spSpawnData->m_fActorScale[1], spSpawnData->m_fActorScale[2] });
				spActor->SetActorRotation({ spSpawnData->m_fActorRotate[0], spSpawnData->m_fActorRotate[1], spSpawnData->m_fActorRotate[2] });
				spActor->SetActorPosition({ spSpawnData->m_fActorTranslate[0], spSpawnData->m_fActorTranslate[1], spSpawnData->m_fActorTranslate[2] });
				
				// 콜라이더 컴포넌트를 설정합니다.
				switch (pair.second->m_eColliderType)
				{
				case EColliderType::NONE: break;
				case EColliderType::RECT: break;
				case EColliderType::CUBE:
				{
					shared_ptr<CCubeColliderComponent> spCubeColliderComponent = spActor->CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
					
					// 메시가 컴포넌트가 없는 경우, 콜라이더 컴포넌트가 루트 컴포넌트가 됩니다.
					if (pair.second->m_eMeshType == EMeshType::NONE) { spActor->SetRootComponent(spCubeColliderComponent); }
					
					// 메시 컴포넌트가 있는 경우
					else { spCubeColliderComponent->SetOwnerComponent(spActor->GetRootComponent()); }

					spCubeColliderComponent->SetComponentLocalPosition({ spSpawnData->m_fColliderComponentTranslate[0], spSpawnData->m_fColliderComponentTranslate[1], spSpawnData->m_fColliderComponentTranslate[2] });
					spCubeColliderComponent->SetComponentRotation({ spSpawnData->m_fColliderComponentRotate[0], spSpawnData->m_fColliderComponentRotate[1], spSpawnData->m_fColliderComponentRotate[2] });
					spCubeColliderComponent->SetComponentScale({ spSpawnData->m_fColliderComponentScale[0], spSpawnData->m_fColliderComponentScale[1], spSpawnData->m_fColliderComponentScale[2] });
					spCubeColliderComponent->SetColliderType(EColliderType::CUBE);
				
					switch (pair.second->m_eCollisionLayerType)
					{
					case ECollisionLayerType::PLAYER:		spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::PLAYER); break;
					case ECollisionLayerType::MONSTER:		spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::MONSTER); break;
					case ECollisionLayerType::GROUND:		spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::GROUND); break;
					case ECollisionLayerType::WALL:			spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::WALL); break;
					case ECollisionLayerType::INTERACTION:	spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::INTERACTION); break;
					case ECollisionLayerType::ITEM:			spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::ITEM); break;
					default: break;
					}

					spCubeColliderComponent->SetCollisionLayer(pair.second->m_iCollisionLayer);
				}
				break;

				default: CHECKF(false, TEXT("Invalid collider type!")) break;
				}

				// 렌더 타입을 설정합니다.
				switch (pair.second->m_eRenderType)
				{
				case ERenderType::NON_ALPHA:	spActor->SetRenderType(ERenderType::NON_ALPHA);		break;
				case ERenderType::ALPHA_TEST:	spActor->SetRenderType(ERenderType::ALPHA_TEST);	break;
				case ERenderType::ALPHA_BLEND:	spActor->SetRenderType(ERenderType::ALPHA_BLEND);	break;
				case ERenderType::USER_INTERFACE:													break;
				default: break;
				}
				
				// 모빌리티를 설정합니다.
				if (pair.second->m_bMobility) { spActor->SetMobility(EMobilityType::DYNAMIC); }
				else { spActor->SetMobility(EMobilityType::DYNAMIC); }

				spActor->Initialize();
				spActor->BeginPlay();
			}
		}
		istrReadFile.close();
	}
}
