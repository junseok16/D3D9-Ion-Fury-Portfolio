#include "pch.h"
#include "SoundComponent.h"

#include "SoundManager.h"
#include "CameraComponent.h"
#include "Actor.h"

using namespace std;

void CSoundComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CSoundComponent::BeginPlay()
{
	CActorComponent::BeginPlay();
}

int32 CSoundComponent::Update(const float& _fDeltaSeconds)
{
	UpdateSoundVolumeByDistance();
	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CSoundComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CSoundComponent::Render()
{
	CActorComponent::Render();
}

void CSoundComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CSoundComponent::Release()
{
	CActorComponent::Release();
}

void CSoundComponent::SetSoundComponentInfo(std::weak_ptr<CCameraComponent> _wpCurCameraComponent, EDistanceModel _eDisModel, float _fMinRadius, float _fMaxRadius, float _fMinVolume, float _fMaxVolume)
{
	m_wpCurCameraComponent = _wpCurCameraComponent;
	m_eDisModel = _eDisModel;
	m_fMinRadius = _fMinRadius;
	m_fMaxRadius = _fMaxRadius;

	// fmod 사운드 볼륨의 범위는 0~1이기 때문에;
	m_fMinVolume = _fMinVolume * 0.01f;
	m_fMaxVolume = _fMaxVolume * 0.01f;
}

void CSoundComponent::PlaySoundByDistance(std::string _strSoundKey, ESoundType _eSoundType)
{
	CSoundManager::GetInstance()->PlaySoundEx(_strSoundKey, _eSoundType, m_fVolume);
}

void CSoundComponent::PlayBGMByDistance(std::string _strSoundKey, float _fVolume)
{
	// fmod 사운드 볼륨의 범위는 0~1이기 때문에;
	float fVolume = _fVolume * 0.01f;
	CSoundManager::GetInstance()->PlayBGMLoop(_strSoundKey, fVolume);
}

void CSoundComponent::PlayPlayerSound(std::string _strSoundKey, float _fVolume, ESoundType _eSoundType)
{
	float fVolume = _fVolume * 0.01f;
	CSoundManager::GetInstance()->PlaySoundEx(_strSoundKey, _eSoundType, fVolume);
}

void CSoundComponent::SetChannelVolumeEx(ESoundType _eSoundType, float _fVolume)
{
	// fmod 사운드 볼륨의 범위는 0~1이기 때문에;
	float fVolume = _fVolume * 0.01f;
	CSoundManager::GetInstance()->SetChannelVolume(_eSoundType, fVolume);
}

void CSoundComponent::StopSoundEx(ESoundType _eSoundType)
{
	CSoundManager::GetInstance()->StopSound(_eSoundType);
}

void CSoundComponent::StopAllEx()
{
	CSoundManager::GetInstance()->StopAll();
}

void CSoundComponent::UpdateSoundVolumeByDistance()
{
	CalculateTwoVectorDistance(m_wpCurCameraComponent);
	CalculateAttenuation();
}

void CSoundComponent::CalculateAttenuation()
{
	// 방어코드
	if (m_eDisModel == EDistanceModel::ENUM_END) { return; }

	// 최소반경 안에 있을 경어 소리 크기를 최대로 하고, 최대반경 밖에 있을 경우 소리 크기를 최소로 함
	if (m_fDis <= m_fMinRadius) { m_fVolume = m_fMaxVolume; }
	else if (m_fDis >= m_fMaxRadius) { m_fVolume = m_fMinRadius; }

	switch (m_eDisModel)
	{
	case EDistanceModel::Linear:
		m_fVolume = -1.f / (m_fMaxRadius - m_fMinRadius) * m_fDis + m_fMaxVolume;
		break;

	case EDistanceModel::Logarithmic:
		m_fVolume = pow(10.f, (-3.f * m_fDis) / (m_fMaxRadius - m_fMinRadius));
		break;

	case EDistanceModel::LogReverse:
		m_fVolume = log(-m_fDis + (m_fMaxRadius - m_fMinRadius + 1.f));
		break;

	case EDistanceModel::Inverse:
		m_fVolume = (m_fMaxRadius / m_fMinRadius) * (0.02f / (m_fDis / m_fMaxRadius));
		break;

	default:
		break;
	}

	if (m_fVolume >= m_fMaxVolume) { m_fVolume = m_fMaxVolume; }
	if (m_fVolume <= m_fMinVolume) { m_fVolume = m_fMinVolume; }
}

void CSoundComponent::CalculateTwoVectorDistance(std::weak_ptr<CCameraComponent> _wpCameraComponent)
{
	m_vDistance.x = fabs(_wpCameraComponent.lock()->GetOwnerActor().lock()->GetActorPosition().x - GetOwnerActor().lock()->GetActorPosition().x);
	m_vDistance.y = fabs(_wpCameraComponent.lock()->GetOwnerActor().lock()->GetActorPosition().y - GetOwnerActor().lock()->GetActorPosition().y);
	m_vDistance.z = fabs(_wpCameraComponent.lock()->GetOwnerActor().lock()->GetActorPosition().z - GetOwnerActor().lock()->GetActorPosition().z);
	m_fDis = m_vDistance.x + m_vDistance.y + m_vDistance.z;
}

