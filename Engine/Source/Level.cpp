#include "pch.h"
#include "Level.h"
#include "World.h"
#include "Actor.h"

#include "ResourceManager.h"
#include "PrefabManager.h"
#include "SpawnManager.h"
#include "CollisionManager.h"
#include "GameManager.h"

#include "RectangleMeshComponent.h"
#include "CubeMeshComponent.h"
#include "AnimationComponent.h"
#include "RectColliderComponent.h"
#include "CubeColliderComponent.h"
using namespace std;

void CLevel::Initialize()
{
	// 액터를 초기화합니다.
	for (auto& pair : m_umapActors)
	{
		pair.second->Initialize();
	}
}

void CLevel::BeginPlay()
{
	for (auto& pair : m_umapActors)
	{
		pair.second->BeginPlay();
	}
}

int32 CLevel::Update(const float& _fDeltaSeconds)
{
	for (auto& pair : m_umapActors)
	{
		int32 iResult = pair.second->Update(_fDeltaSeconds);
		if (iResult != 0) { return iResult; }
	}
	return 0;
}

int32 CLevel::LateUpdate(const float& _fDeltaSeconds)
{
	for (auto& pair : m_umapActors)
	{
		int32 iResult = pair.second->LateUpdate(_fDeltaSeconds);
		if (iResult != 0) { return iResult; }
	}
	return 0;
}

void CLevel::EndPlay()
{
	for (auto& pair : m_umapActors)
	{
		pair.second->EndPlay();
	}
}

void CLevel::Release()
{
	for (auto& pair : m_umapActors)
	{
		pair.second->Release();
		pair.second.reset();
	}
}

void CLevel::Render()
{
	for (auto& pair : m_umapActors)
	{
		pair.second->Render();
	}
}

std::shared_ptr<CActor> CLevel::FindActor(const std::wstring& _wstrActor)
{
	if (m_umapActors.find(_wstrActor) == m_umapActors.end()) { return nullptr; }
	return m_umapActors[_wstrActor];
}

void CLevel::RemoveActor(const std::wstring& _wstrActor)
{
	if (m_umapActors.find(_wstrActor) == m_umapActors.end()) { return; }

	m_umapActors[_wstrActor]->Release();
	m_umapActors.erase(_wstrActor);
}

HRESULT CLevel::LoadLevelFromFile(const std::wstring& _wstrLevel)
{
	const vector<pair<wstring, shared_ptr<PrefabData>>>& vecPrefabData = CPrefabManager::GetInstance()->GetPrefabData();
	const vector<pair<wstring, IDirect3DBaseTexture9*>>& vecD3DTextures = CResourceManager::GetInstance()->GetD3DTextures();
	const vector<pair<wstring, IDirect3DBaseTexture9*>>& vecD3DCubeTextures = CResourceManager::GetInstance()->GetD3DCubeTextures();

	const wstring& wstrDataPath = CResourceManager::GetInstance()->GetDataPath();
	const wstring& wstrPrefabData = wstrDataPath + _wstrLevel + L"_Prefab.dat";
	const wstring& wstrSpawnData = wstrDataPath + _wstrLevel + L"_Spawn.dat";

	// 프리팹 데이터 파일을 읽고 저장합니다.
	ifstream istrPrefabFile(wstrPrefabData, ios::in | ios::binary);
	if (!istrPrefabFile.is_open())
	{
		CHECKF(false, TEXT("No such prefab data file."));
		return E_FAIL;
	}

	// 프리팹 데이터를 읽습니다.
	while (!istrPrefabFile.eof())
	{
		shared_ptr<PrefabData> spPrefabData(make_shared<PrefabData>());
		istrPrefabFile.read(reinterpret_cast<char*>(spPrefabData.get()), sizeof(PrefabData));

		// 파일의 끝인 경우
		if (istrPrefabFile.eof()) { break; }

		wstring wstrPrefabName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (spPrefabData->m_chName[i] == '\0') { break; }
			wstrPrefabName += spPrefabData->m_chName[i];
		}
		CPrefabManager::GetInstance()->AddPrefabData(wstrPrefabName, spPrefabData);
	}
	istrPrefabFile.close();
	
	// 스폰 데이터를 읽습니다.
	ifstream istrSpawnFile(wstrSpawnData, ios::in | ios::binary);
	if (!istrSpawnFile.is_open())
	{
		CHECKF(false, TEXT("No such spawn data file."));
		return E_FAIL;
	}
	
	while (!istrSpawnFile.eof())
	{
		shared_ptr<SpawnData> spSpawnData(make_shared<SpawnData>());
		istrSpawnFile.read(reinterpret_cast<char*>(spSpawnData.get()), sizeof(SpawnData));

		if (istrSpawnFile.eof()) { break; }

		// 액터 이름을 변환합니다.
		wstring wstrActorName = L"";
		for (int32 i = 0; i < 64; ++i)
		{
			if (spSpawnData->m_chName[i] == '\0') { break; }
			wstrActorName += spSpawnData->m_chName[i];
		}
		wstring wstrActorName_A = wstrActorName + L"_A" + to_wstring(CSpawnManager::m_iID++);

		// 액터를 생성합니다.
		shared_ptr<CActor> spActor = CreateActor<CActor>(wstrActorName_A, L"", L"");
		for (const auto& pair : vecPrefabData)
		{
			if (pair.first != wstrActorName) { continue; }

			// 파일 이름을 변환합니다.
			wstring wstrFileName = L"";
			for (int32 i = 0; i < 64; ++i)
			{
				if (pair.second->m_chFileName[i] == '\0') { break; }
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
			}
			break;

			case EMeshType::CUBE:
			{
				shared_ptr<CCubeMeshComponent> spCubeMeshComponent = spActor->CreateActorComponent<CCubeMeshComponent>(L"CubeMeshComponent");
				spActor->SetRootComponent(spCubeMeshComponent);
				spCubeMeshComponent->SetCubeMeshInfo(wstrFileName);
			}
			break;

			default: CHECKF(false, TEXT("Invalid mesh type!")); break;
			}

			// 트랜스폼을 설정합니다.
			spActor->SetActorScale		({ spSpawnData->m_fActorScale[0],		spSpawnData->m_fActorScale[1],		spSpawnData->m_fActorScale[2] });
			spActor->SetActorRotation	({ spSpawnData->m_fActorRotate[0],		spSpawnData->m_fActorRotate[1],		spSpawnData->m_fActorRotate[2] });
			spActor->SetActorPosition	({ spSpawnData->m_fActorTranslate[0],	spSpawnData->m_fActorTranslate[1],	spSpawnData->m_fActorTranslate[2] });

			// 콜라이더 컴포넌트를 설정합니다.
			switch (pair.second->m_eColliderType)
			{
			case EColliderType::NONE: break;
			case EColliderType::RECT: break;
			case EColliderType::CUBE:
			{
				shared_ptr<CCubeColliderComponent> spCubeColliderComponent = spActor->CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
				
				// 메시 컴포넌트가 없는 경우, 콜라이더 컴포넌트가 루트 컴포넌트가 됩니다.
				if (pair.second->m_eMeshType == EMeshType::NONE)
				{
					spActor->SetRootComponent(spCubeColliderComponent);
				}

				// 메시 컴포넌트가 있는 경우
				else { spCubeColliderComponent->SetOwnerComponent(spActor->GetRootComponent()); }

				spCubeColliderComponent->SetComponentLocalPosition	({ spSpawnData->m_fColliderComponentTranslate[0],	spSpawnData->m_fColliderComponentTranslate[1],	spSpawnData->m_fColliderComponentTranslate[2] });
				spCubeColliderComponent->SetComponentRotation		({ spSpawnData->m_fColliderComponentRotate[0],		spSpawnData->m_fColliderComponentRotate[1],		spSpawnData->m_fColliderComponentRotate[2] });
				spCubeColliderComponent->SetComponentScale			({ spSpawnData->m_fColliderComponentScale[0],		spSpawnData->m_fColliderComponentScale[1],		spSpawnData->m_fColliderComponentScale[2] });
				spCubeColliderComponent->SetColliderType(EColliderType::CUBE);

				switch (pair.second->m_eCollisionLayerType)
				{
				case ECollisionLayerType::PLAYER:		spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::PLAYER);		break;
				case ECollisionLayerType::MONSTER:		spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::MONSTER);		break;
				case ECollisionLayerType::GROUND:		spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::GROUND);		break;
				case ECollisionLayerType::WALL:			spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::WALL);			break;
				case ECollisionLayerType::INTERACTION:	spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::INTERACTION);	break;
				case ECollisionLayerType::ITEM:			spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::ITEM);			break;
				case ECollisionLayerType::ITEMOBJECT:	spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::ITEMOBJECT);	break;
				case ECollisionLayerType::PROJECTILE:	spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::PROJECTILE);	break;
				default:																													break;
				}

				// TEMP: 모든 레이어가 다 켜져있는 콜라이더는 플레이어, 몬스터만 충돌을 감지하도록 변경합니다...
				if (pair.second->m_iCollisionLayer == 63) { pair.second->m_iCollisionLayer = 3; }

				spCubeColliderComponent->SetCollisionLayer(pair.second->m_iCollisionLayer);
				CCollisionManager::GetInstance()->AddColliderComponent(spCubeColliderComponent);
			}
			break;

			default: CHECKF(false, TEXT("Invalid collider type!")); break;
			}

			// 렌더 타입을 설정합니다.
			switch (pair.second->m_eRenderType)
			{
			case ERenderType::NON_ALPHA:	spActor->SetRenderType(ERenderType::NON_ALPHA);		break;
			case ERenderType::ALPHA_TEST:	spActor->SetRenderType(ERenderType::ALPHA_TEST);	break;
			case ERenderType::ALPHA_BLEND:	spActor->SetRenderType(ERenderType::ALPHA_BLEND);	break;
			case ERenderType::ORTHOGONAL:														break;
			case ERenderType::USER_INTERFACE:													break;
			default:																			break;
			}

			// 모빌리티를 설정합니다.
			if (pair.second->m_bMobility) { spActor->SetMobility(EMobilityType::DYNAMIC); }
			else { spActor->SetMobility(EMobilityType::STATIC); }
		}
	}
	istrSpawnFile.close();
	
	return S_OK;
}

void CLevel::AddNonDestroyActor(std::shared_ptr<CActor> _spActor)
{
	if (m_umapActors.find(_spActor->GetActorName()) != m_umapActors.end()) { return; }

	_spActor->SetWorld(m_wpWorld);
	_spActor->SetLevel(shared_from_this());

	m_umapActors.insert({ _spActor->GetActorName(), _spActor });
}