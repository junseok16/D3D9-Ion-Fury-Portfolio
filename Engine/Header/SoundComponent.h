#pragma once

#include "ActorComponent.h"

class CCameraComponent;

class CSoundComponent : public CActorComponent
{
public:
	explicit CSoundComponent() = default;
	virtual ~CSoundComponent() = default;

/********************
	Framework
********************/
public:
	virtual void  Initialize() override;
	virtual void  BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void  Render() override;
	virtual void  EndPlay() override;
	virtual void  Release() override;

public:
	// (Update,LateUpdate) 거리별 자동적으로 소리가 조절되는 함수, 거리 알고리즘 모델만 선택해주면 된다.
	void PlaySoundByDistance(std::string _strSoundKey, ESoundType _eSoundType);

	// 볼륨 0&~100% (Initialize, BeginPlay) 지속적으로 재생이 되는 BGM. 단, 주의 할 점은 내부 함수적 이유에 거리별 소리 조절은 자동적으로 안되므로 초기 볼륨 설정을 해줘야 한다
	void PlayBGMByDistance(std::string _strSoundKey, float _fVolume);

	void PlayPlayerSound(std::string _strSoundKey, float _fVolume, ESoundType _eSoundType);

	// 특정 사운드 타입 음원의 볼륨을 조절합니다. 볼륨은 0& ~ 100% 입니다.
	void SetChannelVolumeEx(ESoundType _eSoundType, float _fVolume);

	// 특정 사운드 타입의 음원을 끕니다.
	void StopSoundEx(ESoundType _eSoundType);

	// 모든 사운드의 음원을 끕니다.
	void StopAllEx();

	// 카메라, 거리 알고리즘 모델, 최소 반경, 최대 반경, 최소 볼륨, 최대 볼륨 설정
	void SetSoundComponentInfo(std::weak_ptr<CCameraComponent> _wpCurCameraComponent, EDistanceModel _eDisModel, float _fMinRadius, float _fMaxRadius, float _fMinVolume, float _fMaxVolume);


private:
	// 거리값에 따라 볼륨만 조절해주는 함수;
	void UpdateSoundVolumeByDistance();

	// 어떤 거리별 감쇠 모델로 음성을 출력할지;
	void CalculateAttenuation();

	// 혹시 나중에 또 다른 카메라를 멤버변수에(랜더매니저 처럼) 만들 수 있기에, 범용성을 위해 매개변수를 받은 쪽으로 함;
	void CalculateTwoVectorDistance(std::weak_ptr<CCameraComponent> _wpCameraComponent);


private:
	float m_fDis = 0.f;	// 카메라와 Actor의 거리;
	float m_fMinRadius = 0.f;	// 사운드의 원점(Actor)으로부터 m_fMinRadius까지 반경 안에 있을시 볼륨은 100%입니다;
	float m_fMaxRadius = 0.f;	// 사운드의 원점(Actor)으로부터 m_fMaxRadius까지 반경 밖에 있을시 볼륨은 0%입니다;
	float m_fVolume = 1.f;	// 카메라와 Actor의 거리에 따른 볼륨;
	float m_fMinVolume = 0.f;	// Actor가 낼 수 있는 최소 볼륨 크기;
	float m_fMaxVolume = 0.f;	// Actor가 낼 수 있는 최대 볼륨 크기;
	FVector3 m_vDistance{ 0.0f, 0.0f, 0.0f };				// 거리 값을 측정해서 정보를 담기 위한 벡터;
	EDistanceModel m_eDisModel = EDistanceModel::ENUM_END;  // 거리별 감쇠 모델;
	std::weak_ptr<CCameraComponent> m_wpCurCameraComponent; // 거리를 구하기 위한 카메라 위크 포인터;
};

