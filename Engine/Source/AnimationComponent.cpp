#include "pch.h"
#include "AnimationComponent.h"

#include "DeviceManager.h"
#include "TimerManager.h"
using namespace std;

void CAnimationComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::TEXTURE;

	SetVertexInfo(4, sizeof(TextureVertex), TEXTURE_FVF);
	SetIndexInfo(2, sizeof(TextureIndex), D3DFMT_INDEX32);

	m_vecTextureVertices.reserve(4);
	m_vecTextureVertices.resize(4);
	m_vecTextureVertices[0] = { { -0.5f, +0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 0.0f, 0.0f } };
	m_vecTextureVertices[1] = { { +0.5f, +0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.0f, 0.0f } };
	m_vecTextureVertices[2] = { { +0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.0f, 1.0f } };
	m_vecTextureVertices[3] = { { -0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 0.0f, 1.0f } };

	m_vecTextureIndices.reserve(2);
	m_vecTextureIndices.resize(2);
	m_vecTextureIndices[0] = { 0, 1, 2 };
	m_vecTextureIndices[1] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(4);
	m_vecVertexWorldPos.resize(4);

	m_vecVertexIndices.reserve(2);

	SettingTextureFrameTime(m_iFileEndIndex, 0.05f);

	CMeshComponent::Initialize();
}

void CAnimationComponent::BeginPlay()
{
	CMeshComponent::BeginPlay();
}

int32 CAnimationComponent::Update(const float& _fDeltaSeconds)
{
	if (m_bIsAnimate)
	{
		UpdateAnimation(_fDeltaSeconds);
		FrameMappingUpdate();
	}
	return CMeshComponent::Update(_fDeltaSeconds);
}

int32 CAnimationComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CMeshComponent::LateUpdate(_fDeltaSeconds);
}

void CAnimationComponent::Render()
{
	CMeshComponent::Render();

	if (m_bIsRender)
	{
		// 월드 행렬(World matrix, W)을 설정합니다.
		m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

		// 스트림 소스를 버텍스 버퍼에 연결하여 렌더링 파이프라인에 보냅니다.
		m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

		// 버텍스 포맷을 설정합니다.
		m_pD3DDevice9->SetFVF(m_iVertexFormat);

		// 인덱스 버퍼를 설정합니다.
		m_pD3DDevice9->SetIndices(m_pIndexBuffer);

		// 텍스처 지정
		m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[m_iCurFrame]);

		// 인덱스 정보를 활용해 기본 도형을 그립니다.
		m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
	}
}

void CAnimationComponent::EndPlay()
{
	CMeshComponent::EndPlay();
}

void CAnimationComponent::Release()
{
	CMeshComponent::Release();
}

// 초기화시 애니메이션 정보를 세팅 해야합니다.
void CAnimationComponent::SettingAnimationInfo(const std::wstring& _wstrTextureFileName, const uint32& _iFileBeginIndex, const uint32& _iFileEndIndex,
											   const std::wstring& _wstrState, EAnimationType _eAnimationType, const float& _fFrameSpeed)
{
	m_wstrTextureFileName	= _wstrTextureFileName;
	m_iFileBeginIndex		= _iFileBeginIndex;
	m_iFileEndIndex			= _iFileEndIndex;

	m_eAnimationType	= _eAnimationType;
	m_wstrCurrentState	= _wstrState;
	m_fFrameSpeed		= _fFrameSpeed;
}

void CAnimationComponent::AddState(const std::wstring& _wstrState, const uint32& _iBeginIndex, const uint32& _iEndIndex)
{
	m_umapStateFrame.insert({ _wstrState, std::make_pair(_iBeginIndex, _iEndIndex) });
}

void CAnimationComponent::UpdateAnimation(const float& _fDeltaSeconds)
{
	m_fFramePlayTime += m_fFrameSpeed * _fDeltaSeconds;

	if (m_wstrPreState != m_wstrCurrentState)
		m_iCurFrame = m_umapStateFrame[m_wstrCurrentState].first;

	// 만약 FramePlayTime이 매핑된 FramePlayTime보다 커졌다면
	if (m_fFramePlayTime > m_vecTexturePlayTime[m_iCurFrame])
	{
		// 현재 프레임을 1 증가
		++m_iCurFrame;
		m_fFramePlayTime = 0.f;

		// 근데 만약 현재 프레임이 지정된 최대 프레임보다 커졌다면
		if(m_iCurFrame > m_umapStateFrame[m_wstrCurrentState].second)
		// if (m_iCurFrame >= m_iMaxFrame)
		{
			// 데드 상태가 아닌 경우 현재 프레임을 최소 프레임으로 초기화
			if(L"Dead" != m_wstrCurrentState)
				m_iCurFrame = m_umapStateFrame[m_wstrCurrentState].first;
			// m_iCurFrame = m_iMinFrame;

			// (아이들 상태가 아닌 경우)현재 애니메이션 진행 횟수 1 증가
			if(L"Idle" != m_wstrCurrentState)
				++m_iCurAnimationCount;

			// 애니메이션 루프 타입이 아닌 경우(루프인 경우 지알아서 계속 돕니당)
			if (EAnimationType::LOOP != m_eAnimationType)
			{
				// 근데 만약 현재 애니메이션 횟수가 지정된 횟수보다 커졌다면
				if (m_iCurAnimationCount > m_iAnimationCount)
				{
					// 현재 애니메이션 횟수를 0으로 초기화
					m_iCurAnimationCount = 0;
					// 애니메이션 비활성화(다시 활성화 하려면 SetIsAnimate 함수를 True로 호출해주어야 함)
					SetIsAnimate(false);
				}
			}
		}
	}

	m_wstrPreState = m_wstrCurrentState;
}

// SetFrameTime(상태 키 값, 시작 프레임, 끝 프레임, 프레임 속도)
void CAnimationComponent::SetFrameTime(const std::wstring& _wstrState, const int32& _iStartIndex, const int32& _iEndIndex, const float& _fFrameSpeed)
{
	// 예외처리 구문
	if (_iStartIndex > m_vecTexturePlayTime.size() || _iEndIndex > m_vecTexturePlayTime.size())
		return;

	for (int32 iIndex = _iStartIndex; iIndex <= _iEndIndex; ++iIndex)
		m_vecTexturePlayTime[iIndex] = _fFrameSpeed;
}

// [private] SettingTextureFrameTime(텍스처 파일 인덱스 수, 프레임 속도)
void CAnimationComponent::SettingTextureFrameTime(const int32& _iFileIndex, const float& _fFrameSpeed)
{
	m_vecTexturePlayTime.reserve(_iFileIndex + 1);

	for (int32 iIndex = 0; iIndex <= _iFileIndex; ++iIndex)
		m_vecTexturePlayTime.push_back(_fFrameSpeed);
}

// FrameMapping(매핑할 함수 이름, 매핑할 프레임)
void CAnimationComponent::FrameMapping(const std::wstring& _wstrFunctionName, int32 _iFrame)
{
	m_ummapFrameMaps.insert({ _wstrFunctionName, _iFrame });
}

// 매 프레임마다 [ 현재 프레임 <-> 매핑된 프레임 ]을 비교하여 같을 시 매핑된 함수를 호출합니다.
void CAnimationComponent::FrameMappingUpdate()
{
	for (const auto& lstFrameMaps : m_ummapFrameMaps)
	{
		int32 iFrame = lstFrameMaps.second;
		if (m_iCurFrame == iFrame)
		{
			m_umapFrameCallbacks[lstFrameMaps.first]();
		}
	}
}