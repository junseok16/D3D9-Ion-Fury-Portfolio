#include "pch.h"
#include "PlayerActor.h"

#include "DeviceManager.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "Level.h"
#include "Creature.h"
#include "Monster.h"
#include "WeaponActor.h"
#include "ItemObjectActor.h"
#include "PlayerEffectActor.h"

#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "SkyboxComponent.h"
#include "CubeColliderComponent.h"
#include "PhysicsComponent.h"
#include "SpotLightComponent.h"
#include "SoundComponent.h"

using namespace std;

void CPlayerActor::Initialize()
{
	CameraSetting();
	LightSetting();
	ColliderSetting();
	EffectSetting();
	PhysicsSetting();
	StatusSetting();
	SoundSetting();

	// 임시코드
	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CActor::Initialize();
}

void CPlayerActor::BeginPlay()
{
	m_wpSpotLightComponent.lock()->SetSpotLightInfo({ 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, 100.f, 0.5f, 15.f, 30.f, 1);
	SetCurrentWeapon(m_vecWeapons[0]);
	m_vecWeapons[0].lock()->SetIsEnable(true);

	CInputManager::GetInstance()->SetCursorInCenter(true);
	ShowCursor(FALSE);

	m_wpSoundComponent.lock()->SetSoundComponentInfo(CRenderManager::GetInstance()->GetCurRenderCamera(), EDistanceModel::Linear, 1.0f, 10.0f, 0.0f, 100.0f);

	// 11.20 브금 재생을 위해 추가 -동연-
	if (L"Stage1" == GetLevel().lock()->GetLevelName())
	{
		m_wpSoundComponent.lock()->PlayBGMByDistance("Stage1", 80.0f);
	}
	else if (L"Stage2" == GetLevel().lock()->GetLevelName())
	{
		m_wpSoundComponent.lock()->PlayBGMByDistance("Stage2", 80.0f);
	}
	else if (L"Stage3" == GetLevel().lock()->GetLevelName())
	{
		m_wpSoundComponent.lock()->PlayBGMByDistance("Stage3", 80.0f);
	}
	else if (L"Stage4" == GetLevel().lock()->GetLevelName())
	{
		m_wpSoundComponent.lock()->PlayBGMByDistance("Stage4", 80.0f);
	}

	ChangeWeapon(1);
	CActor::BeginPlay();
}

int32 CPlayerActor::Update(const float& _fDeltaSeconds)
{	
	KeyInput(_fDeltaSeconds);

	UpdateFSM(_fDeltaSeconds);
	UpdateSkillCoolTime(_fDeltaSeconds);
	UpdateSkillState();
	ReduceExcessHp();

	m_wpSpotLightComponent.lock()->SetLightPosition(GetActorPosition(), GetForwardVector(), 1);
	ResetCurBullet();

	return CActor::Update(_fDeltaSeconds);
}

int32 CPlayerActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CPlayerActor::Render()
{
	CActor::Render();
}

void CPlayerActor::EndPlay()
{
	CActor::EndPlay();
}

void CPlayerActor::Release()
{
	CActor::Release();
}

void CPlayerActor::UpdateMouseMovement()
{
	int32 iDeltaY = 0;
	if (iDeltaY = CInputManager::GetInstance()->GetMouseDeltaY())
	{
		FVector3 vRightVector = GetRightVector();
		FMatrix matMouseRotateMatrix = GetMouseRotateMatrix();
		FMatrix matRotateMatrix;

		D3DXMatrixRotationAxis(&matRotateMatrix, &vRightVector, D3DXToRadian(iDeltaY / 10.0f));
		D3DXMatrixMultiply(&matMouseRotateMatrix, &matMouseRotateMatrix, &matRotateMatrix);
		SetMouseRotateMatrix(matMouseRotateMatrix);
	}

	int32 iDeltaX = 0;
	if (iDeltaX = CInputManager::GetInstance()->GetMouseDeltaX())
	{
		FVector3 vUpVector = { 0.0f, 1.0f, 0.0f };
		FMatrix matMouseRotateMatrix = GetMouseRotateMatrix();
		FMatrix matRotateMatrix;

		D3DXMatrixRotationAxis(&matRotateMatrix, &vUpVector, D3DXToRadian(iDeltaX / 10.0f));
		D3DXMatrixMultiply(&matMouseRotateMatrix, &matMouseRotateMatrix, &matRotateMatrix);
		SetMouseRotateMatrix(matMouseRotateMatrix);
	}
}

void CPlayerActor::UpdateFSM(const float& _fDeltaSeconds)
{
	if (L"Player_Jump_" == m_wstrAnimationState)
	{
		m_wpPhysicsComponent.lock()->SetGravityValue(39.2f);
		float fGravity = m_wpPhysicsComponent.lock()->GetGravityValue();
		float fDistance = m_fJumpSpeed * _fDeltaSeconds;
		m_fJumpTime += _fDeltaSeconds;

		if (0.f < m_fJumpSpeed)
			m_fJumpSpeed -= fGravity * powf(m_fJumpTime, 2); // 약간 임시

		FVector3 vUp = { 0.0f, 1.0f, 0.0f };
		SetActorPosition(GetActorPosition() + fDistance * vUp);

		if (1.00f < m_fJumpTime)
		{
			m_wstrAnimationState = L"Player_Idle_";
			m_fJumpSpeed = 100.0f;
			m_fJumpTime = 0.0f;
			SetIsOnAir(false);
		}
	}
}

void CPlayerActor::UpdateSkillState()
{
	// 리콜
	if (m_bRecallLock)
	{
		m_vecEffects[0].lock()->SetIsRecall(true);
		Recall();
	}
	else
	{
		m_vecEffects[0].lock()->SetIsRecall(false);

		UpdateMouseMovement();
		SavePlayerInfo();
	}

	// 블링크
	if (m_bBlinkLock)
	{
		m_vecEffects[0].lock()->SetIsBlink(true);
		Blink();
	}
	else
	{
		m_vecEffects[0].lock()->SetIsBlink(false);
	}

	// 싼데비스탄
	if (m_bIsSandevistan)
	{
		m_vecEffects[0].lock()->SetIsSandevistan(true);
	}
	else
	{
		m_vecEffects[0].lock()->SetIsSandevistan(false);
	}
}

void CPlayerActor::UpdateSkillCoolTime(const float& _fDeltaSeconds)
{
	// 점멸
	if (m_iBlinkCurCount < m_iBlinkMaxCount)
	{
		m_fBlinkCoolRecovery += _fDeltaSeconds;

		if (m_fBlinkCoolTime < m_fBlinkCoolRecovery)
		{
			++m_iBlinkCurCount;
			m_fBlinkCoolRecovery = 0.0f;
		}
	}
	// 시간역행
	if (m_iRecallCurCount < m_iRecallMaxCount)
	{
		m_fRecallCoolRecovery += _fDeltaSeconds;

		if (m_fRecallCoolTime < m_fRecallCoolRecovery)
		{
			++m_iRecallCurCount;
			m_fRecallCoolRecovery = 0.0f;
		}
	}
}

void CPlayerActor::AddWeapon(std::weak_ptr<CWeaponActor> _wpWeaponActor)
{
	CHECK(!_wpWeaponActor.expired());

	_wpWeaponActor.lock()->SetOwnerActor(dynamic_pointer_cast<CActor>(shared_from_this()));
	m_vecWeapons.push_back(_wpWeaponActor.lock());
}

void CPlayerActor::AddEffect(std::weak_ptr<CPlayerEffectActor> _wpEffectActor)
{
	CHECK(!_wpEffectActor.expired());

	// 이펙트 UI는 플레이어를 따라다니면 안됨
	// _wpWeaponActor.lock()->SetOwnerActor(dynamic_pointer_cast<CActor>(shared_from_this()));
	m_vecEffects.push_back(_wpEffectActor.lock());
}

void CPlayerActor::EffectSetting()
{

}

void CPlayerActor::ColliderSetting()
{
	// 큐브 콜라이더
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::INTERACTION);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PROJECTILE);

	m_wpCubeColliderComponent.lock()->SetOwnerActor(dynamic_pointer_cast<CActor>(shared_from_this()));
	m_wpCubeColliderComponent.lock()->SetIsRootComponent(true);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

void CPlayerActor::PhysicsSetting()
{
	m_wpPhysicsComponent = CreateActorComponent<CPhysicsComponent>(L"PhysicsComponent");
	m_wpPhysicsComponent.lock()->SetGravityValue(39.2f);
}

void CPlayerActor::StatusSetting()
{
	SetCurHp(90.f);
	SetCurArmor(0.f);
	SetMaxArmor(49.f);
	m_fSpeed = 45.0f;
	m_fJumpSpeed = 75.0f;
}

void CPlayerActor::CameraSetting()
{
	m_wpCameraComponent = CreateActorComponent<CCameraComponent>(L"CameraActor_CameraComponent");
	SetRootComponent(m_wpCameraComponent);
	m_wpCameraComponent.lock()->SetCurRenderCamera();
	m_wpCameraComponent.lock()->SetCameraMoveRatioX(100.0f);
	m_wpCameraComponent.lock()->SetCameraMoveRatioY(75.0f);
	m_wpCameraComponent.lock()->SetCameraMoveDistanceX(0.5f);
	m_wpCameraComponent.lock()->SetCameraMoveDistanceY(1.0f);
}

void CPlayerActor::LightSetting()
{
	m_wpSpotLightComponent = CreateActorComponent<CSpotLightComponent>(L"LightComponent");
	SetRootComponent(m_wpSpotLightComponent);
}

void CPlayerActor::SoundSetting()
{
	// 사운드: 총알 발사
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
	m_wpSoundComponent.lock()->SetOwnerComponent(m_wpCameraComponent);
}

void CPlayerActor::SetBillboard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent)
{
	// 뷰 행렬
	FMatrix matView;
	matView = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetCurCamera().lock()->GetPersViewMatrix();

	// 뷰 행렬에서 빌보드 행렬 만들기(x, y, z축에 따라 다르게 / 지금은 y축만 / 비행기 게임에서는 z, x축도 사용)
	FMatrix matBill;
	D3DXMatrixIdentity(&matBill);
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 월드 행렬
	FMatrix matWorld;
	matWorld = _wpPrimitiveComponent.lock()->GetWorldMatrix();

	// 크기 변환 벡터
	FVector3 vScale = _wpPrimitiveComponent.lock()->GetComponentScale();

	// 크기 변환의 역행렬
	FMatrix matScaleInverse;
	D3DXMatrixScaling(&matScaleInverse, vScale.x, vScale.y, vScale.z);
	D3DXMatrixInverse(&matScaleInverse, 0, &matScaleInverse);

	// 월드행렬에 크기 변환의 역행렬 곱하기
	::D3DXMatrixMultiply(&matWorld, &matScaleInverse, &matWorld);

	// 빌보드 행렬 곱하기
	::D3DXMatrixMultiply(&matWorld, &matBill, &matWorld);

	// 다시 크기 변환 곱하기
	FMatrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	::D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);

	_wpPrimitiveComponent.lock()->SetWorldMatrix(matWorld);
}

void CPlayerActor::KeyInput(const float& _fDeltaSeconds)
{
#pragma region 이동
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_W))
	{
		MoveForward(1, _fDeltaSeconds);
		//m_wpCameraComponent.lock()->SetCameraMove(true);
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_S))
	{
		MoveForward(-1, _fDeltaSeconds);
		//m_wpCameraComponent.lock()->SetCameraMove(true);
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_D))
	{
		MoveRight(1, _fDeltaSeconds);
		//m_wpCameraComponent.lock()->SetCameraMove(true);
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_A))
	{
		MoveRight(-1, _fDeltaSeconds);
		//m_wpCameraComponent.lock()->SetCameraMove(true);
	}

	if (CInputManager::GetInstance()->IsKeyReleased(DIK_A) && CInputManager::GetInstance()->IsKeyReleased(DIK_S) &&
		CInputManager::GetInstance()->IsKeyReleased(DIK_D) && CInputManager::GetInstance()->IsKeyReleased(DIK_W))
	{
		//m_wpCameraComponent.lock()->SetCameraMove(false);
	}

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_SPACE))
	{
		Jump();
	}

#pragma endregion

#pragma region 공격
	if (CInputManager::GetInstance()->IsMouseDown(EMouseButtonType::LEFT_BUTTON) && m_wpCurrentWeapon.lock()->GetWeaponType() == EWeaponType::ELECTRIFRYER)
	{
		Attack1();
	}
	if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::LEFT_BUTTON) && m_wpCurrentWeapon.lock()->GetWeaponType() != EWeaponType::ELECTRIFRYER)
	{
		Attack1();
	}
	if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::RIGHT_BUTTON))
	{
		Attack2();
	}
#pragma endregion
	
#pragma region 무기
	if (CInputManager::GetInstance()->IsKeyDown(DIK_1))
	{
		ChangeWeapon(1);
	}
	if (CInputManager::GetInstance()->IsKeyDown(DIK_2))
	{
		ChangeWeapon(2);
	}
	if (CInputManager::GetInstance()->IsKeyDown(DIK_3) && m_bDisperser)
	{
		ChangeWeapon(3);
	}
	if (CInputManager::GetInstance()->IsKeyDown(DIK_4) && m_bPenetrator)
	{
		ChangeWeapon(4);
	}
	if (CInputManager::GetInstance()->IsKeyDown(DIK_5) && m_bChainGun)
	{
		ChangeWeapon(5);
	}
#pragma endregion

#pragma region 재장전
	if (CInputManager::GetInstance()->IsKeyDown(DIK_R))
	{
		Reload();
	}
#pragma endregion

#pragma region 스킬
	// 시간 역행
	if (CInputManager::GetInstance()->IsKeyDown(DIK_E) && /*m_bRecallEnable &&*/ (0 < m_iRecallCurCount))
	{
		RecallOn();
		// --m_iRecallCurCount;
	}
	// 점멸
	if (CInputManager::GetInstance()->IsKeyDown(DIK_LSHIFT) /*&& m_bBlinkEnable*/ && (0 < m_iBlinkCurCount))
	{
		BlinkOn();
		--m_iBlinkCurCount;
	}
	// 손전등
	if (CInputManager::GetInstance()->IsKeyDown(DIK_V))
	{
		LightOnOff();
	}
	// 싼데비스탄
	if (CInputManager::GetInstance()->IsKeyDown(DIK_Q)/* && m_bSandevistanEnable*/)
	{
		Sandevistan();
	}
#pragma endregion
}

int32 CPlayerActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (ECollisionLayerType::GROUND == _wpDstCollider.lock()->GetCollisionLayerType())
	{
		m_bIsCollided = true;
		m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);

		CCollisionManager::BlockCubeToCube
		(
			dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
			dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
			m_wpPhysicsComponent.lock()->GetGravityValue()
		);
	}
	if (ECollisionLayerType::WALL == _wpDstCollider.lock()->GetCollisionLayerType())
	{
		m_bWallCol = true;

		CCollisionManager::BlockCubeToCube
		(
			dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
			dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
			m_fSpeed
		);
	}

	return 0;
}

void CPlayerActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	// 큐브 충돌
	if (EColliderType::CUBE == _wpSrcCollider.lock()->GetColliderType() &&
		EColliderType::CUBE == _wpDstCollider.lock()->GetColliderType())
	{
		if (ECollisionLayerType::GROUND == _wpDstCollider.lock()->GetCollisionLayerType())
		{
			m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
			CCollisionManager::BlockCubeToCube
			(
				dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
				dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
				m_wpPhysicsComponent.lock()->GetGravityValue()
			);
		}
		if (ECollisionLayerType::WALL == _wpDstCollider.lock()->GetCollisionLayerType())
		{
			CCollisionManager::BlockCubeToCube
			(
				dynamic_pointer_cast<CCubeColliderComponent>(_wpSrcCollider.lock()),
				dynamic_pointer_cast<CCubeColliderComponent>(_wpDstCollider.lock()),
				m_fSpeed
			);
		}
	}
}

void CPlayerActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (ECollisionLayerType::GROUND == _wpDstCollider.lock()->GetCollisionLayerType())
	{
		m_bIsCollided = false;
	}
	if (ECollisionLayerType::WALL == _wpDstCollider.lock()->GetCollisionLayerType())
	{
		m_bWallCol = false;
	}
	m_wpPhysicsComponent.lock()->SetGravityValue(39.2f);
}

void CPlayerActor::MoveForward(int32 _iAxisValue, const float& _fDeltaSeconds)
{
	FVector3 vForward = GetForwardVector();
	vForward.y -= vForward.y;
	D3DXVec3Normalize(&vForward, &vForward);
	SetActorPosition(GetActorPosition() + vForward * (float)_iAxisValue * _fDeltaSeconds * m_fSpeed);
	ShakeWeapon(_fDeltaSeconds);
}

void CPlayerActor::MoveRight(int32 _iAxisValue, const float& _fDeltaSeconds)
{
	FVector3 vRight = GetRightVector();
	vRight.y -= vRight.y;
	D3DXVec3Normalize(&vRight, &vRight);
	SetActorPosition(GetActorPosition() + vRight * (float)_iAxisValue * _fDeltaSeconds * m_fSpeed);
}

void CPlayerActor::Jump()
{
	if (L"Player_Jump_" != m_wstrAnimationState)
	{
		m_wstrAnimationState = L"Player_Jump_";
		m_wpPhysicsComponent.lock()->SetGravityValue(39.2f);
	}
}

void CPlayerActor::Crouch()
{
	float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	FVector3 vUp = GetUpVector();
	D3DXVec3Normalize(&vUp, &vUp);
	SetActorPosition(GetActorPosition() - vUp * m_fJumpSpeed * fInnerDeltaSeconds);
}

void CPlayerActor::Attack1()
{
	CHECK(!m_vecWeapons.empty());
	CHECK(!m_vecWeapons[m_iCurWeaponNumber].expired());

	//m_wpSoundComponent.lock()->PlayPlayerSound("Player_Hitted1", 50.0f, ESoundType::DAMAGE);

	std::weak_ptr<CAnimationComponent> wpWeaponAnimation = (m_vecWeapons[m_iCurWeaponNumber].lock()->GetAnimationComponent());

	if (m_wpCurrentWeapon.lock()->GetWeaponType() == EWeaponType::ELECTRIFRYER ||
		m_wpCurrentWeapon.lock()->GetBulletLoaded() > 0 && 
		m_wpCurrentWeapon.lock()->GetActivate())
	{
		wpWeaponAnimation.lock()->SetCurrentState(L"Attack1");
	}
}

void CPlayerActor::Attack2()
{
	CHECK(!m_vecWeapons.empty());
	CHECK(!m_vecWeapons[m_iCurWeaponNumber].expired());

	std::weak_ptr<CAnimationComponent> wpWeaponAnimation = (m_vecWeapons[m_iCurWeaponNumber].lock()->GetAnimationComponent());

	if (m_wpCurrentWeapon.lock()->GetWeaponType() == EWeaponType::ELECTRIFRYER ||
		m_wpCurrentWeapon.lock()->GetBulletLoaded() > 0 &&
		m_wpCurrentWeapon.lock()->GetActivate())
	{
		wpWeaponAnimation.lock()->SetCurrentState(L"Attack2");
	}
}

void CPlayerActor::Reload()
{
	CHECK(!m_vecWeapons.empty());
	CHECK(!m_vecWeapons[m_iCurWeaponNumber].expired());

	std::shared_ptr<CAnimationComponent> spWeaponAnimation = (m_vecWeapons[m_iCurWeaponNumber].lock()->GetAnimationComponent()).lock();

	switch (m_wpCurrentWeapon.lock()->GetWeaponType())
	{
	case EWeaponType::ELECTRIFRYER:
	case EWeaponType::CHAINGUN:

		break;

	default:
		if(m_wpCurrentWeapon.lock()->GetBulletLoaded() < m_wpCurrentWeapon.lock()->GetMagazine() &&
			m_wpCurrentWeapon.lock()->GetBulletHolding() > 0)
		{
			spWeaponAnimation->SetCurrentState(L"Reload");
			m_wpCurrentWeapon.lock()->SetActivate(false);
		}

		break;
	}
}

void CPlayerActor::GetDamaged(const float& _fDamage)
{
	// 이펙트 액터에 맞았다고 알림
	m_vecEffects[0].lock()->SetIsHitted(true);

	// 피격 사운드 재생
	switch (m_ePlayerHittedSound)
	{
	case EPlayerHittedSound::NUM_1:
	{
		m_wpSoundComponent.lock()->PlayPlayerSound("Player_Hitted1", 50.0f, ESoundType::DAMAGE);
		m_ePlayerHittedSound = EPlayerHittedSound::NUM_2;
		break;
	}
	case EPlayerHittedSound::NUM_2:
	{
		m_wpSoundComponent.lock()->PlayPlayerSound("Player_Hitted2", 50.0f, ESoundType::DAMAGE);
		m_ePlayerHittedSound = EPlayerHittedSound::NUM_3;
		break;
	}
	case EPlayerHittedSound::NUM_3:
	{
		m_wpSoundComponent.lock()->PlayPlayerSound("Player_Hitted3", 50.0f, ESoundType::DAMAGE);
		m_ePlayerHittedSound = EPlayerHittedSound::NUM_1;
		break;
	}
	}

	float fOverDamage = 0;

	if (m_fCurArmor > 0)
	{
		m_fCurArmor -= _fDamage;

		if (m_fCurArmor < 0)
		{
			fOverDamage = m_fCurArmor;
			m_fCurArmor = 0;

			if (m_fCurHp > fOverDamage)
			{
				m_fCurHp -= fOverDamage;
				fOverDamage = 0;
			}
		}
		return;
	}

	else if (m_fCurArmor <= 0 && m_fCurHp > _fDamage)
	{
		m_fCurHp -= _fDamage;
		return;
	}

	m_fCurHp = 0.0f;
}

void CPlayerActor::ChangeWeapon(int32 _iWeaponNumber)
{
	CHECK(!m_vecWeapons.empty());
	CHECK(!m_vecWeapons[_iWeaponNumber - 1].expired());

	for (auto& iter : m_vecWeapons)
		iter.lock()->SetIsEnable(false);

	m_wpCurrentWeapon = m_vecWeapons[_iWeaponNumber - 1];
	m_wpCurrentWeapon.lock()->SetIsEnable(true);
	m_wpCurrentWeapon.lock()->SetActivate(true);
	m_iCurWeaponNumber = _iWeaponNumber - 1;
}

void CPlayerActor::UseRecoveryKit()
{
	SetCurHpPlus(25.f);
}

void CPlayerActor::UseRadar()
{
}

void CPlayerActor::ReduceExcessHp()				// 초과 체력 줄이기
{
	if (m_fCurHp > m_fMaxHp && !m_bIsButton)		// 현재 체력이 최대체력을 넘어서고 버튼이 false라면
	{
		m_bIsButton = true;							// 버튼 true
	}

	if (m_bIsButton)								// 버튼이 true면 델타 세컨드 더해주기 시작
	{
		m_fStandard += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	}

	if (5.f <= m_fStandard && m_bIsButton)			// 더해준 델타 세컨드가 5가 넘는다면 체력을 1 빼고 기준 초기화
	{
		SetCurHpMinus(1);
		m_fStandard = 0.f;
	}

	if (m_fCurHp <= m_fMaxHp && m_bIsButton)		// 현재 체력이 최대 체력보다 작거나 같고, 버튼이 true라면 0 초기화 시켜주고 버튼 false로
	{
		m_fStandard = 0.f;
		m_bIsButton = false;
	}
}

void CPlayerActor::ColRecoveryItem(ERecoveryType eRecType, float fRecNum)
{
	switch (eRecType)
	{
	case ERecoveryType::HEALTHPACK:		// 회복타입 헬스팩
		SetCurHpPlus(fRecNum);			// 회복량만큼 회복
		if (m_fCurHp > m_fMaxHp)		// 회복한 현재 체력이 맥스보다 크다면
		{
			SetCurHpMax();				// 맥스로
		}
		break;

	case ERecoveryType::SYRINGE:		// 회복타입 주사기
		SetCurHpPlus(fRecNum);
		break;

	case ERecoveryType::ARMOR:			// 회복타입 아머
		if (m_fMaxArmor >= fRecNum)		// 만약 최대 아머가 매개변수보다 크다면
		{
			if (m_fCurArmor < fRecNum)	// 만약 현재 아머가 매개변수보다 작다면
			{
				SetCurArmor(fRecNum);	// 매개변수만큼으로 조정
				break;
			}
		}
		else
		{
			SetMaxArmor(fRecNum + 49.f);		// 맥스 아머가 더 작다면
			SetCurArmor(fRecNum);
		}
		break;

	case ERecoveryType::ARMORPIECE:		// 아머 조각이라면
		if(m_fCurArmor < m_fMaxArmor)	// 현재 아머가 최대 아머보다 작다면
		{
			SetCurArmorPlus(fRecNum);
		}
		break;
	}
}

void CPlayerActor::ColCardKeyItem(ERecoveryType eRecType)
{
	switch (eRecType)
	{
	case ERecoveryType::CARDKEY:			// 회복타입 아머
		m_iCardKeyNum++;
		break;
	}
}

void CPlayerActor::ResetCurBullet()		// 무기와 총알 기록 갱신
{
	m_wpPreWeapon = m_wpCurrentWeapon.lock()->GetWeaponType();
	m_iBullet = m_wpCurrentWeapon.lock()->GetCurBullet();
}

shared_ptr<CCubeColliderActor> CPlayerActor::HitScan()
{
	FVector3 vFoward = GetForwardVector();
	FVector3 vActorPos = GetActorPosition();

	std::weak_ptr<CActor> wpHitedActor = CCollisionManager::IntersectRayToCollider(vActorPos, vFoward, dynamic_pointer_cast<CActor>(shared_from_this()));
	if (wpHitedActor.expired()) return nullptr;

	std::weak_ptr<CCubeColliderActor> wpHitedCubeActor = dynamic_pointer_cast<CCubeColliderActor>(wpHitedActor.lock());
	if (wpHitedCubeActor.expired()) return nullptr;

	return wpHitedCubeActor.lock();
}

void CPlayerActor::SavePlayerInfo()
{
	float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

	m_fRecallSaveSec += fInnerDeltaSeconds;

	m_tPlayerInfo = { GetActorPosition(), GetMouseRotateMatrix(), GetCurHp() };
	m_lstPlayerInfo.push_front(m_tPlayerInfo);

	if (m_fRecallSaveSec >= 3.f)
		m_lstPlayerInfo.pop_back();
}

void CPlayerActor::Recall()
{
	m_fRecallSaveSec = 0.f;

	if (m_iRecallCount == 0)
	{
		m_lstIter = m_lstPlayerInfo.begin();
		m_iRecallCount++;
	}

	if (m_lstIter != m_lstPlayerInfo.end())
	{
		SetActorPosition(m_lstIter->position);
		SetMouseRotateMatrix(m_lstIter->forword);

		if (m_fCurHp < m_lstIter->Hp)
		{
			SetCurHp(m_lstIter->Hp);
		}
		m_lstIter++;
	}
	else if (m_lstIter == m_lstPlayerInfo.end())
	{
		switch (m_eRecallVoice)
		{
		case ERecallVoiceType::DEJAVU:
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Tracer_EndRecall_0", 50.0f, ESoundType::VOICE);
			// CSoundManager::GetInstance()->PlaySoundEx("Tracer_EndRecall_0", ESoundType::VOICE, 100.0f);
			m_eRecallVoice = ERecallVoiceType::COMBACK;
			break;
		}

		case ERecallVoiceType::COMBACK:
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Tracer_EndRecall_1", 50.0f, ESoundType::VOICE);
			// CSoundManager::GetInstance()->PlaySoundEx("Tracer_EndRecall_1", ESoundType::VOICE, 100.0f);
			m_eRecallVoice = ERecallVoiceType::REFIGHT;
			break;
		}
		case ERecallVoiceType::REFIGHT:
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Tracer_EndRecall_2", 50.0f, ESoundType::VOICE);
			// CSoundManager::GetInstance()->PlaySoundEx("Tracer_EndRecall_2", ESoundType::VOICE, 100.0f);
			m_eRecallVoice = ERecallVoiceType::DEJAVU;
			break;
		}
		}

		--m_iRecallCurCount;
		m_bRecallLock = false;
		m_lstPlayerInfo.clear();
	}
}

void CPlayerActor::Blink()
{
	if (!m_bBlinkSound)
	{
		m_wpSoundComponent.lock()->PlayPlayerSound("Tracer_Blink", 50.0f, ESoundType::EFFECT);
		m_bBlinkSound = true;
	}

	float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

	m_fBlinkSec += fInnerDeltaSeconds;

	FVector3 vForward = GetForwardVector();
	FVector3 vRight = GetRightVector();

	float fBlinkSpeed = 300.f;

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_W))
	{
		m_fForward = 1.f;
		if (CInputManager::GetInstance()->IsKeyPressed(DIK_A) || CInputManager::GetInstance()->IsKeyPressed(DIK_D))
		{
			fBlinkSpeed = 150.f;
		}
		else
			fBlinkSpeed = 300.f;
		int a = 0;
	}
	else if (CInputManager::GetInstance()->IsKeyPressed(DIK_S))
	{
		m_fForward = -1.f;

		if (CInputManager::GetInstance()->IsKeyPressed(DIK_A) || CInputManager::GetInstance()->IsKeyPressed(DIK_D))
		{
			fBlinkSpeed = 150.f;
		}
		else
			fBlinkSpeed = 300.f;
	}
	else
		m_fForward *= 0.f;

	if (CInputManager::GetInstance()->IsKeyPressed(DIK_D))
	{
		m_fRight = 1.f;
		if (CInputManager::GetInstance()->IsKeyPressed(DIK_W) || CInputManager::GetInstance()->IsKeyPressed(DIK_S))
		{
			fBlinkSpeed = 150.f;
		}
		else
			fBlinkSpeed = 300.f;
	}

	else if (CInputManager::GetInstance()->IsKeyPressed(DIK_A))
	{
		m_fRight = -1.f;
		if (CInputManager::GetInstance()->IsKeyPressed(DIK_W) || CInputManager::GetInstance()->IsKeyPressed(DIK_S))
		{
			fBlinkSpeed = 150.f;
		}
		else
			fBlinkSpeed = 300.f;
	}
	else m_fRight *= 0.0f;

	/*if(m_bWallCol)
	{
		m_fForward = 0.f; m_fRight = 0.f;
	}*/

	if (m_fBlinkSec < 0.15f)
	{
		vForward.y -= vForward.y;
		vRight.y -= vRight.y;

		D3DXVec3Normalize(&vForward, &vForward);
		D3DXVec3Normalize(&vRight, &vRight);
		SetActorPosition(GetActorPosition() + vForward * m_fForward * fInnerDeltaSeconds * fBlinkSpeed ); 
		SetActorPosition(GetActorPosition() + vRight * m_fRight * fInnerDeltaSeconds * fBlinkSpeed );
	}
	else
	{
		// 블링크 off
		m_bBlinkLock = false;
		m_bBlinkSound = false;
	}
}

void CPlayerActor::ShakeWeapon(float _fDeltaTime)
{
	FVector3 vPos = { 0.f, 0.f, 0.f };
	float fShake = 0.f;
	float fRadian = 0.f;

	m_fShakeTime += _fDeltaTime * 10.f;

	fShake = sinf(m_fShakeTime);

	fRadian = fShake * (3.14159f / 18.f);

	vPos = m_wpCurrentWeapon.lock()->GetActorPosition();
	vPos += { 10.f * fRadian, 0.f, 0.f };

	m_wpCurrentWeapon.lock()->SetActorPosition(vPos);
}

void CPlayerActor::LightOnOff()
{
	if (m_bIsLightEnable == TRUE)
	{
		m_bIsLightEnable = FALSE;
	}
	else
	{
		m_bIsLightEnable = TRUE;
	}
	m_wpSpotLightComponent.lock()->SetLightOnOff(1, m_bIsLightEnable);
}

void CPlayerActor::Sandevistan()
{
	std::unordered_map<std::wstring, std::shared_ptr<CActor>> umapActors = GetLevel().lock()->GetUmapActors();

	// 싼데비스탄 사용시 플레이어와 무기를 제외하고 전부 느려짐
	if (!m_bIsSandevistan)
	{
		m_wpSoundComponent.lock()->PlayPlayerSound("Player_Sandevistan", 100.0f, ESoundType::EFFECT);
		m_bIsSandevistan = true;
		for (auto& iter : umapActors)
		{
			if (iter.second->GetActorTag().find(L"Player") != iter.second->GetActorTag().end() ||
				iter.second->GetActorTag().find(L"Weapon") != iter.second->GetActorTag().end())
				continue;

			(iter.second)->SetIsTimeSlipped(true);
			/*if (iter.second->GetActorLayer().find(L"Monster") != iter.second->GetActorLayer().end())
			{
				dynamic_pointer_cast<CMonster>(iter.second)->SetIsTimeSlipped(true);
			}*/
		}
	}
	else
	{
		m_bIsSandevistan = false;
		for (auto& iter : umapActors)
		{
			if (iter.second->GetActorTag().find(L"Player") != iter.second->GetActorTag().end() ||
				iter.second->GetActorTag().find(L"Weapon") != iter.second->GetActorTag().end())
				continue;

			(iter.second)->SetIsTimeSlipped(false);
			/*if (iter.second->GetActorLayer().find(L"Monster") != iter.second->GetActorLayer().end())
			{
				dynamic_pointer_cast<CMonster>(iter.second)->SetIsTimeSlipped(false);
			}*/
		}
	}
}