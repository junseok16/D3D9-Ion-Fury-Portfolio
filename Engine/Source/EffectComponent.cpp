#include "pch.h"
#include "EffectComponent.h"

void CEffectComponent::Initialize()
{
	m_iAnimationCount = 0;
	m_eAnimationType = EAnimationType::DESIGNATED_TIME;

	CAnimationComponent::Initialize();
}

void CEffectComponent::BeginPlay()
{
	CAnimationComponent::BeginPlay();
}

int32 CEffectComponent::Update(const float& _fDeltaSeconds)
{
	return CAnimationComponent::Update(_fDeltaSeconds);
}

int32 CEffectComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CAnimationComponent::LateUpdate(_fDeltaSeconds);
}

void CEffectComponent::Render()
{
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

void CEffectComponent::EndPlay()
{
	CAnimationComponent::EndPlay();
}

void CEffectComponent::Release()
{
	CAnimationComponent::Release();
}

void CEffectComponent::UpdateAnimation(const float& _fDeltaSeconds)
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
		if (m_iCurFrame > m_umapStateFrame[m_wstrCurrentState].second)
			// if (m_iCurFrame >= m_iMaxFrame)
		{
			// 현재 프레임을 최소 프레임으로 초기화
			m_iCurFrame = m_umapStateFrame[m_wstrCurrentState].first;
			// m_iCurFrame = m_iMinFrame;

			// (아이들 상태가 아닌 경우)현재 애니메이션 진행 횟수 1 증가
			if (L"Idle" != m_wstrCurrentState)
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
					SetIsRender(false);
				}
			}
		}
	}

	m_wstrPreState = m_wstrCurrentState;
}