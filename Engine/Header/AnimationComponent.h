#pragma once
#include "MeshComponent.h"

/**
 * @brief	애니메이션 컴포넌트 클래스입니다.
 * @details 애니메이션 컴포넌트 클래스는 Actor의 상태 키 값에 따른 텍스쳐들을 보유하고, 애니메이션 루프, 상태에 따른 애니메이션 변경 등을 수행합니다.
 * @author	박동연
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
	애니메이션 관련 Methods
*******************/
public:
	// 애니메이션 정보 세팅(파일 이름, 시작 인덱스, 끝 인덱스, 상태명, 루프타입, 프레임 스피드)
	void SettingAnimationInfo(const std::wstring& _wstrTextureFileName, const uint32& _iFileBeginIndex, const uint32& _iFileEndIndex,
								 const std::wstring& _wstrState, EAnimationType _eAnimationType, const float& _fFrameSpeed);

	// 11.01 추가(상태, 시작 인덱스, 끝 인덱스)
	void AddState(const std::wstring& _wstrState, const uint32& _iBeginIndex, const uint32& _iEndIndex);

	// 매 프레임 애니메이션을 업데이트하는 함수
	virtual void UpdateAnimation(const float& _fDeltaSeconds);

	// 각 프레임당 속도를 설정할 수 있게 해주는 함수
	void SetFrameTime(const std::wstring& _wstrState, const int32& _iStartIndex, const int32& _iEndIndex, const float& _fFrameSpeed);

private:
	// m_umapTextures의 텍스처들의 시간 값들을 인덱스별로 매핑시켜주는 함수
	void SettingTextureFrameTime(const int32& _iFileIndex, const float& _fFrameSpeed);

/*******************
	애니메이션 관련 Getter/Setter
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
	특정 시점 함수 호출을 위한 함수
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
	애니메이션 관련 Data Members
********************/
protected:

	// [ 액터 이름, 프레임 실행 시간 ] - 멀티 텍스처의 각 프레임당 실행 시간을 저장하는 umap
	std::vector<float> m_vecTexturePlayTime;

	// [ 액터 상태, < 시작, 끝 > ] - AddState 함수를 통해 상태가 추가되게 됨.
	std::unordered_map <std::wstring, std::pair<int32, int32>> m_umapStateFrame;

	// [ 특정 프레임에 함수 호출 < 상태명, 프레임 > ]
	std::unordered_multimap<std::wstring , int32 /* frame */> m_ummapFrameMaps;
	std::unordered_map <std::wstring, std::function<void(void)>> m_umapFrameCallbacks;

	EAnimationType	m_eAnimationType		= EAnimationType::LOOP;	// 애니메이션 타입
	bool			m_bIsAnimate			= true;					// 애니메이션 재생 여부
	bool			m_bIsRender				= true;					// 애니메이션 출력 여부
	int32			m_iAnimationCount		= 1;					// 총 애니메이션 횟수
	int32			m_iCurAnimationCount	= 0;					// 현재 애니메이션 횟수

	std::wstring	m_wstrCurrentState = L"";	// 현재 상태(키 값)
	std::wstring	m_wstrPreState = L"";		// 이전 상태(키 값)

	int32			m_iMinFrame = 0;			// 최소 프레임
	int32			m_iCurFrame = 0;			// 현재 프레임
	int32			m_iMaxFrame = 0;			// 최대 프레임

	float			m_fFrameSpeed		= 1.0f;		// 전체적인 프레임 진행 속도(높을수록 애니메이션이 빨라짐)
	float			m_fFramePlayTime	= 0.f;		// 한 프레임마다 누적되는 (DeltaTime * FrameSpeed)값의 합
};