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
		// ���� ���(World matrix, W)�� �����մϴ�.
		m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

		// ��Ʈ�� �ҽ��� ���ؽ� ���ۿ� �����Ͽ� ������ ���������ο� �����ϴ�.
		m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

		// ���ؽ� ������ �����մϴ�.
		m_pD3DDevice9->SetFVF(m_iVertexFormat);

		// �ε��� ���۸� �����մϴ�.
		m_pD3DDevice9->SetIndices(m_pIndexBuffer);

		// �ؽ�ó ����
		m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[m_iCurFrame]);

		// �ε��� ������ Ȱ���� �⺻ ������ �׸��ϴ�.
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

	// ���� FramePlayTime�� ���ε� FramePlayTime���� Ŀ���ٸ�
	if (m_fFramePlayTime > m_vecTexturePlayTime[m_iCurFrame])
	{
		// ���� �������� 1 ����
		++m_iCurFrame;
		m_fFramePlayTime = 0.f;

		// �ٵ� ���� ���� �������� ������ �ִ� �����Ӻ��� Ŀ���ٸ�
		if (m_iCurFrame > m_umapStateFrame[m_wstrCurrentState].second)
			// if (m_iCurFrame >= m_iMaxFrame)
		{
			// ���� �������� �ּ� ���������� �ʱ�ȭ
			m_iCurFrame = m_umapStateFrame[m_wstrCurrentState].first;
			// m_iCurFrame = m_iMinFrame;

			// (���̵� ���°� �ƴ� ���)���� �ִϸ��̼� ���� Ƚ�� 1 ����
			if (L"Idle" != m_wstrCurrentState)
				++m_iCurAnimationCount;

			// �ִϸ��̼� ���� Ÿ���� �ƴ� ���(������ ��� ���˾Ƽ� ��� ���ϴ�)
			if (EAnimationType::LOOP != m_eAnimationType)
			{
				// �ٵ� ���� ���� �ִϸ��̼� Ƚ���� ������ Ƚ������ Ŀ���ٸ�
				if (m_iCurAnimationCount > m_iAnimationCount)
				{
					// ���� �ִϸ��̼� Ƚ���� 0���� �ʱ�ȭ
					m_iCurAnimationCount = 0;
					// �ִϸ��̼� ��Ȱ��ȭ(�ٽ� Ȱ��ȭ �Ϸ��� SetIsAnimate �Լ��� True�� ȣ�����־�� ��)
					SetIsAnimate(false);
					SetIsRender(false);
				}
			}
		}
	}

	m_wstrPreState = m_wstrCurrentState;
}