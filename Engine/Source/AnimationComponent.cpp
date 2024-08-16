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

void CAnimationComponent::EndPlay()
{
	CMeshComponent::EndPlay();
}

void CAnimationComponent::Release()
{
	CMeshComponent::Release();
}

// �ʱ�ȭ�� �ִϸ��̼� ������ ���� �ؾ��մϴ�.
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

	// ���� FramePlayTime�� ���ε� FramePlayTime���� Ŀ���ٸ�
	if (m_fFramePlayTime > m_vecTexturePlayTime[m_iCurFrame])
	{
		// ���� �������� 1 ����
		++m_iCurFrame;
		m_fFramePlayTime = 0.f;

		// �ٵ� ���� ���� �������� ������ �ִ� �����Ӻ��� Ŀ���ٸ�
		if(m_iCurFrame > m_umapStateFrame[m_wstrCurrentState].second)
		// if (m_iCurFrame >= m_iMaxFrame)
		{
			// ���� ���°� �ƴ� ��� ���� �������� �ּ� ���������� �ʱ�ȭ
			if(L"Dead" != m_wstrCurrentState)
				m_iCurFrame = m_umapStateFrame[m_wstrCurrentState].first;
			// m_iCurFrame = m_iMinFrame;

			// (���̵� ���°� �ƴ� ���)���� �ִϸ��̼� ���� Ƚ�� 1 ����
			if(L"Idle" != m_wstrCurrentState)
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
				}
			}
		}
	}

	m_wstrPreState = m_wstrCurrentState;
}

// SetFrameTime(���� Ű ��, ���� ������, �� ������, ������ �ӵ�)
void CAnimationComponent::SetFrameTime(const std::wstring& _wstrState, const int32& _iStartIndex, const int32& _iEndIndex, const float& _fFrameSpeed)
{
	// ����ó�� ����
	if (_iStartIndex > m_vecTexturePlayTime.size() || _iEndIndex > m_vecTexturePlayTime.size())
		return;

	for (int32 iIndex = _iStartIndex; iIndex <= _iEndIndex; ++iIndex)
		m_vecTexturePlayTime[iIndex] = _fFrameSpeed;
}

// [private] SettingTextureFrameTime(�ؽ�ó ���� �ε��� ��, ������ �ӵ�)
void CAnimationComponent::SettingTextureFrameTime(const int32& _iFileIndex, const float& _fFrameSpeed)
{
	m_vecTexturePlayTime.reserve(_iFileIndex + 1);

	for (int32 iIndex = 0; iIndex <= _iFileIndex; ++iIndex)
		m_vecTexturePlayTime.push_back(_fFrameSpeed);
}

// FrameMapping(������ �Լ� �̸�, ������ ������)
void CAnimationComponent::FrameMapping(const std::wstring& _wstrFunctionName, int32 _iFrame)
{
	m_ummapFrameMaps.insert({ _wstrFunctionName, _iFrame });
}

// �� �����Ӹ��� [ ���� ������ <-> ���ε� ������ ]�� ���Ͽ� ���� �� ���ε� �Լ��� ȣ���մϴ�.
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