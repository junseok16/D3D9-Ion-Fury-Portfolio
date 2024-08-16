#pragma once
#include "MeshComponent.h"

/**
 * @brief	�ִϸ��̼� ������Ʈ Ŭ�����Դϴ�.
 * @details �ִϸ��̼� ������Ʈ Ŭ������ Actor�� ���� Ű ���� ���� �ؽ��ĵ��� �����ϰ�, �ִϸ��̼� ����, ���¿� ���� �ִϸ��̼� ���� ���� �����մϴ�.
 * @author	�ڵ���
 * @date	2023-10-17
 */

class CAnimationComponent : public CMeshComponent
{
public:
    explicit CAnimationComponent() = default;
    virtual ~CAnimationComponent() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

/*******************
	�ִϸ��̼� ���� Methods
*******************/
public:
	// �ִϸ��̼� ���� ����(���� �̸�, ���� �ε���, �� �ε���, ���¸�, ����Ÿ��, ������ ���ǵ�)
	void SettingAnimationInfo(const std::wstring& _wstrTextureFileName, const uint32& _iFileBeginIndex, const uint32& _iFileEndIndex,
								 const std::wstring& _wstrState, EAnimationType _eAnimationType, const float& _fFrameSpeed);

	// 11.01 �߰�(����, ���� �ε���, �� �ε���)
	void AddState(const std::wstring& _wstrState, const uint32& _iBeginIndex, const uint32& _iEndIndex);

	// �� ������ �ִϸ��̼��� ������Ʈ�ϴ� �Լ�
	virtual void UpdateAnimation(const float& _fDeltaSeconds);

	// �� �����Ӵ� �ӵ��� ������ �� �ְ� ���ִ� �Լ�
	void SetFrameTime(const std::wstring& _wstrState, const int32& _iStartIndex, const int32& _iEndIndex, const float& _fFrameSpeed);

private:
	// m_umapTextures�� �ؽ�ó���� �ð� ������ �ε������� ���ν����ִ� �Լ�
	void SettingTextureFrameTime(const int32& _iFileIndex, const float& _fFrameSpeed);

/*******************
	�ִϸ��̼� ���� Getter/Setter
*******************/
public:
	void SetCurrentState(const std::wstring& _wstrFileName) { m_wstrCurrentState = _wstrFileName; }
	const std::wstring& GetCurrentState() const { return m_wstrCurrentState; }

	void SetFrame(const int32& _iMinFrame, const int32& _iCurFrame, const int32& _iMaxFrame) 
	{ 
		m_iMinFrame = _iMinFrame;
		m_iCurFrame = _iCurFrame;
		m_iMaxFrame = _iMaxFrame;
	}

	void SetMinFrame(const int32& _iMinFrame) { m_iMinFrame = _iMinFrame; }
	const int32& GetMinFrame() { return m_iMinFrame; }

	void SetCurFrame(const int32& _iCurFrame) { m_iCurFrame = _iCurFrame; }
	const int32& GetCurFrame() { return m_iCurFrame; }

	void SetMaxFrame(const int32& _iMaxFrame) { m_iMaxFrame = _iMaxFrame; }
	const int32& GetMaxFrame() { return m_iMaxFrame; }
	
	void SetAnimationCount(const int32& _iAnimationCount) { m_iAnimationCount = _iAnimationCount; }
	const int32& GetAnimationCount() { return m_iAnimationCount; }

	void SetCurrentAnimationCount(const int32& _iCurrentAnimationCount) { m_iCurAnimationCount = _iCurrentAnimationCount; }
	const int32& GetCurrentAnimationCount() { return m_iCurAnimationCount; }

	void SetAnimationType(EAnimationType _eAnimationType) { m_eAnimationType = _eAnimationType; }
	EAnimationType GetAnimationType() { return m_eAnimationType; }

	std::pair<int32, int32> GetStateFrame(const std::wstring& _wstrState) { return m_umapStateFrame[_wstrState]; }

	void SetIsAnimate(bool _bIsAnimate) { m_bIsAnimate = _bIsAnimate; }
	bool GetIsAnimate() { return m_bIsAnimate; }

	void SetIsRender(bool _bIsRender) { m_bIsRender = _bIsRender; }
	bool GetIsRender() { return m_bIsRender; }

/********************
	Ư�� ���� �Լ� ȣ���� ���� �Լ�
********************/
public:
	void FrameMapping(const std::wstring& _wstrFunctionName, int32 _iFrame);

	template<typename T>
	void BindFrame(const std::wstring& _wstrFunctionName, std::shared_ptr<T> _spOwner, void(T::* function)())
	{
		std::function<void(void)> m_function = [_spOwner, function]()
			{ (_spOwner.get()->*function)(); };

		if (m_umapFrameCallbacks.find(_wstrFunctionName) != m_umapFrameCallbacks.end()) { return; }
		m_umapFrameCallbacks.insert({ _wstrFunctionName, m_function });
	}

	void FrameMappingUpdate();

/********************
	�ִϸ��̼� ���� Data Members
********************/
protected:

	// [ ���� �̸�, ������ ���� �ð� ] - ��Ƽ �ؽ�ó�� �� �����Ӵ� ���� �ð��� �����ϴ� umap
	std::vector<float> m_vecTexturePlayTime;

	// [ ���� ����, < ����, �� > ] - AddState �Լ��� ���� ���°� �߰��ǰ� ��.
	std::unordered_map <std::wstring, std::pair<int32, int32>> m_umapStateFrame;

	// [ Ư�� �����ӿ� �Լ� ȣ�� < ���¸�, ������ > ]
	std::unordered_multimap<std::wstring , int32 /* frame */> m_ummapFrameMaps;
	std::unordered_map <std::wstring, std::function<void(void)>> m_umapFrameCallbacks;

	EAnimationType	m_eAnimationType		= EAnimationType::LOOP;	// �ִϸ��̼� Ÿ��
	bool			m_bIsAnimate			= true;					// �ִϸ��̼� ��� ����
	bool			m_bIsRender				= true;					// �ִϸ��̼� ��� ����
	int32			m_iAnimationCount		= 1;					// �� �ִϸ��̼� Ƚ��
	int32			m_iCurAnimationCount	= 0;					// ���� �ִϸ��̼� Ƚ��

	std::wstring	m_wstrCurrentState = L"";	// ���� ����(Ű ��)
	std::wstring	m_wstrPreState = L"";		// ���� ����(Ű ��)

	int32			m_iMinFrame = 0;			// �ּ� ������
	int32			m_iCurFrame = 0;			// ���� ������
	int32			m_iMaxFrame = 0;			// �ִ� ������

	float			m_fFrameSpeed		= 1.0f;		// ��ü���� ������ ���� �ӵ�(�������� �ִϸ��̼��� ������)
	float			m_fFramePlayTime	= 0.f;		// �� �����Ӹ��� �����Ǵ� (DeltaTime * FrameSpeed)���� ��
};