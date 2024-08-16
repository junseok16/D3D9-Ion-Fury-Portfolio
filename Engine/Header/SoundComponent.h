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
	// (Update,LateUpdate) �Ÿ��� �ڵ������� �Ҹ��� �����Ǵ� �Լ�, �Ÿ� �˰��� �𵨸� �������ָ� �ȴ�.
	void PlaySoundByDistance(std::string _strSoundKey, ESoundType _eSoundType);

	// ���� 0&~100% (Initialize, BeginPlay) ���������� ����� �Ǵ� BGM. ��, ���� �� ���� ���� �Լ��� ������ �Ÿ��� �Ҹ� ������ �ڵ������� �ȵǹǷ� �ʱ� ���� ������ ����� �Ѵ�
	void PlayBGMByDistance(std::string _strSoundKey, float _fVolume);

	void PlayPlayerSound(std::string _strSoundKey, float _fVolume, ESoundType _eSoundType);

	// Ư�� ���� Ÿ�� ������ ������ �����մϴ�. ������ 0& ~ 100% �Դϴ�.
	void SetChannelVolumeEx(ESoundType _eSoundType, float _fVolume);

	// Ư�� ���� Ÿ���� ������ ���ϴ�.
	void StopSoundEx(ESoundType _eSoundType);

	// ��� ������ ������ ���ϴ�.
	void StopAllEx();

	// ī�޶�, �Ÿ� �˰��� ��, �ּ� �ݰ�, �ִ� �ݰ�, �ּ� ����, �ִ� ���� ����
	void SetSoundComponentInfo(std::weak_ptr<CCameraComponent> _wpCurCameraComponent, EDistanceModel _eDisModel, float _fMinRadius, float _fMaxRadius, float _fMinVolume, float _fMaxVolume);


private:
	// �Ÿ����� ���� ������ �������ִ� �Լ�;
	void UpdateSoundVolumeByDistance();

	// � �Ÿ��� ���� �𵨷� ������ �������;
	void CalculateAttenuation();

	// Ȥ�� ���߿� �� �ٸ� ī�޶� ���������(�����Ŵ��� ó��) ���� �� �ֱ⿡, ���뼺�� ���� �Ű������� ���� ������ ��;
	void CalculateTwoVectorDistance(std::weak_ptr<CCameraComponent> _wpCameraComponent);


private:
	float m_fDis = 0.f;	// ī�޶�� Actor�� �Ÿ�;
	float m_fMinRadius = 0.f;	// ������ ����(Actor)���κ��� m_fMinRadius���� �ݰ� �ȿ� ������ ������ 100%�Դϴ�;
	float m_fMaxRadius = 0.f;	// ������ ����(Actor)���κ��� m_fMaxRadius���� �ݰ� �ۿ� ������ ������ 0%�Դϴ�;
	float m_fVolume = 1.f;	// ī�޶�� Actor�� �Ÿ��� ���� ����;
	float m_fMinVolume = 0.f;	// Actor�� �� �� �ִ� �ּ� ���� ũ��;
	float m_fMaxVolume = 0.f;	// Actor�� �� �� �ִ� �ִ� ���� ũ��;
	FVector3 m_vDistance{ 0.0f, 0.0f, 0.0f };				// �Ÿ� ���� �����ؼ� ������ ��� ���� ����;
	EDistanceModel m_eDisModel = EDistanceModel::ENUM_END;  // �Ÿ��� ���� ��;
	std::weak_ptr<CCameraComponent> m_wpCurCameraComponent; // �Ÿ��� ���ϱ� ���� ī�޶� ��ũ ������;
};

