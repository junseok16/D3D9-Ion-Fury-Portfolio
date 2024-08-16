#include "pch.h"
#include "ParticleComponent.h"

#include "DeviceManager.h"
#include "TimerManager.h"

#include "Level.h"
#include "Actor.h"
using namespace std;

void CParticleComponent::Initialize()
{
	// Primitive ����
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_ePrimitiveType = EPrimitiveType::MESH;
	m_eTextureType = ETextureType::TEXTURE;

	m_tD3DPool = D3DPOOL_DEFAULT;
	SetVertexInfo(1, sizeof(ParticleVertex), PARTICLE_FVF);

	//m_vOrigin = GetOwnerActor().lock()->GetActorWorldPosition();

	CPrimitiveComponent::Initialize();
}

void CParticleComponent::BeginPlay()
{
	CPrimitiveComponent::BeginPlay();
}

int CParticleComponent::Update(const float& _fDeltaSeconds)
{
	CParticleComponent::UpdateParticle(_fDeltaSeconds);
	return CPrimitiveComponent::Update(_fDeltaSeconds);
}

int CParticleComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CPrimitiveComponent::LateUpdate(_fDeltaSeconds);
}

void CParticleComponent::PreRender()
{
	if (m_bIsActive)
	{
		// �������� �ռ� �����ؾ� �� �ʱ� �������¸� �����Ѵ�.
		// m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, false);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, true);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSIZE, FtoDW(m_fParticleSize));
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));

		// �Ÿ��� ���� ��ƼŬ�� ũ�⸦ �����Ѵ�.
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(1.0f));
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(1.0f));
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));

		// m_pD3DDevice9->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 0, 0));

		// �ؽ�ó�� ���ĸ� �̿��Ѵ�.
		m_pD3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pD3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		
		m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_pD3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// ����Ʈ ���� �μ��� ���� ���θ� �����ϰ��� �Ѵٸ�
		// ������ Render()�Լ� ������ SetRenderState �Լ��� ���¸� �������ָ� �ȴ�.
		// m_pD3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		// m_pD3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		// m_pD3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}
}

void CParticleComponent::Render()
{
	CPrimitiveComponent::Render();

	if(m_bIsActive)
	{
		if (!m_lstParticles.empty())
		{
			PreRender();

			m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

			// �ؽ�ó�� ����ִ� ��ƼŬ Ŭ������ ���
			if (!m_vecD3DTextures.empty())
				m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[0]);

			m_pD3DDevice9->SetFVF(PARTICLE_FVF);
			m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

			// ���ؽ� ���۸� ��� ��� ó������ �����Ѵ�.
			if (m_lVbOffset >= m_lVbSize)
				m_lVbOffset = 0;

			ParticleVertex* pVertex = nullptr;

			m_pVertexBuffer->Lock(
				m_lVbOffset * m_iVertexSize,
				m_lVbBatchSize * m_iVertexSize,
				(void**)&pVertex,
				m_lVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
			);

			int32 lNumParticlesInBatch = 0;

			//
			// ��� ��ƼŬ�� �������� ������
			//
			std::list<ParticleAttribute>::iterator iter;
			for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
			{
				if (iter->isAlive)
				{
					// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� �����Ѵ�.
					pVertex->position = iter->position;
					pVertex->color = D3DCOLOR(iter->color);
					++pVertex; // ���� ����
					++lNumParticlesInBatch; // �ܰ� ī���͸� ������Ų��.

					// ���� �ܰ谡 ��� ä���� �ִ°�?
					if (lNumParticlesInBatch == m_lVbBatchSize)
					{
						// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ���� �׸���.
						m_pVertexBuffer->Unlock();

						// m_pD3DDevice9->SetIndices(m_pIndexBuffer);

						// �� �ε��� ����� ���� ������ �׳� DrawPrimitive�� �ٲ㺸�� ��
						// m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
						m_pD3DDevice9->DrawPrimitive(D3DPT_POINTLIST, m_lVbOffset, m_lVbBatchSize);


						// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä���.
						// ���� �ܰ��� ó�� ���������� �̵��Ѵ�.

						m_lVbOffset += m_lVbBatchSize;

						// (����ó��)���ؽ� ������ ��踦 �Ѵ� �޸𸮷� �������� �������� �ʴ´�.
						// ��踦 ���� ��� ó������ �����Ѵ�.
						if (m_lVbOffset > m_lVbSize)
							m_lVbOffset = 0;

						m_pVertexBuffer->Lock(
							m_lVbOffset * m_iVertexSize,
							m_lVbBatchSize * m_iVertexSize,
							(void**)&pVertex,
							m_lVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
						);

						lNumParticlesInBatch = 0; // ���� �ܰ踦 ���� ����
					}
				}
			}
			m_pVertexBuffer->Unlock();

			// (lNumParticlesInBatch == m_lVbBatchSize) ������ �������� ���Ͽ�
			// ������ �ܰ谡 ���������� �ʴ� ��찡 �߻��� �� �ִ�. �Ϻθ� ä���� �ܰ��
			// �̰����� �������ȴ�.
			if (lNumParticlesInBatch)
			{
				// m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
				m_pD3DDevice9->DrawPrimitive(D3DPT_POINTLIST, m_lVbOffset, lNumParticlesInBatch);
			}

			// ���� ���
			m_lVbOffset += m_lVbBatchSize;

			PostRender();
		}
	}
}

void CParticleComponent::PostRender()
{
	if (m_bIsActive)
	{
		// m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, false);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, false);
		m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
}

void CParticleComponent::EndPlay()
{
	CPrimitiveComponent::EndPlay();
}

void CParticleComponent::Release()
{
	CPrimitiveComponent::Release();
}

void CParticleComponent::CreateVertexBuffer()
{
	ENSURE(m_pD3DDevice9->CreateVertexBuffer
	(
		m_lVbSize * m_iVertexSize,
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, // ���� ����
		m_iVertexFormat,
		m_tD3DPool,
		&m_pVertexBuffer,
		nullptr
	));
}

void CParticleComponent::UpdateParticle(const float& _fDeltaSeconds)
{
	std::list<ParticleAttribute>::iterator iter;

	// �� ������ ���ʾ����� ��ġ������ m_vOrgin�� ���ŵ˴ϴ�.
	// m_vOrigin = m_vWorldPosition;

	switch (m_eParticleType)
	{
#pragma region ������ ��ƼŬ
	case EParticleType::STRAITGHT:
	{
		int32 iCount = 0;
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			if (iter->isAlive)
			{
				iter->age += _fDeltaSeconds;
				// iter->position += (iCount * iter->interval * iter->velocity * _fDeltaSeconds);
				if (iter->age > iter->createTime)
				{
					++iCount;
					iter->position += (iter->velocity) * _fDeltaSeconds;
				}
				
				if (iter->age > iter->lifeTime)
				{
					if (m_bIsRemove)
						iter->isAlive = false;
					else
						ResetParticles(&(*iter));
				}
			}
		}
		break;

	}
#pragma endregion
		
#pragma region �л��� ��ƼŬ
	case EParticleType::SPRAY:
	{
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			iter->age += _fDeltaSeconds;
			if (iter->age > iter->createTime)
			{
				// �Ÿ� = (v * t) + (0.5f * a * t^2);
				iter->position += (iter->velocity) * _fDeltaSeconds + 0.5f * (iter->velocity) * iter->acceleration * powf(iter->age, 2);
			}

			if (iter->age > iter->lifeTime)
			{
				if (m_bIsRemove)
					iter->isAlive = false;
				else
					ResetParticles(&(*iter));
			}
		}

		break;
	}
#pragma endregion

#pragma region ������ ��ƼŬ

	case EParticleType::ERUPTION:
	{
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			iter->age += _fDeltaSeconds;

			if (iter->age > iter->createTime)
			{
				iter->velocity.y -= iter->acceleration * powf(iter->age, 2);

				iter->position += (iter->velocity) * _fDeltaSeconds + 0.5f * (iter->velocity) * iter->acceleration * powf(iter->age, 2);
			}

			if (iter->age > iter->lifeTime)
			{
				if (m_bIsRemove)
					iter->isAlive = false;
				else
					ResetParticles(&(*iter));
			}
		}

		break;
	}

#pragma endregion

#pragma region �߶��� ��ƼŬ
	case EParticleType::FALLEN:
	{
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			iter->age += _fDeltaSeconds;

			if (iter->age > iter->createTime)
			{
				iter->velocity.y -= iter->acceleration * powf(iter->age, 2);

				iter->position += (iter->velocity) * _fDeltaSeconds + 0.5f * (iter->velocity) * iter->acceleration * powf(iter->age, 2);
			}

			if (iter->age > iter->lifeTime || iter->position.y < m_vOrigin.y - GetRandomFloat(5.0f, 10.0f))
			{
				if (m_bIsRemove)
					iter->isAlive = false;
				else
					ResetParticles(&(*iter));
			}
		}

		break;
	}
#pragma endregion

#pragma region �� ��ƼŬ
	case EParticleType::RAIN:
	{
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			iter->age += _fDeltaSeconds;

			if (iter->age > iter->createTime)
			{
				iter->position += (iter->velocity) * _fDeltaSeconds;
			}

			if (iter->age > iter->lifeTime || iter->position.y < -200.0f)
			{
				if (m_bIsRemove)
					iter->isAlive = false;
				else
					ResetParticles(&(*iter));
			}
		}

		break;
	}
#pragma endregion

#pragma region �������
	case EParticleType::SMOKE:
	{
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			iter->age += _fDeltaSeconds;

			if (iter->age > iter->createTime)
			{
				iter->position += (iter->velocity) * _fDeltaSeconds;
			}

			if (iter->age > iter->lifeTime)
			{
				if (m_bIsRemove)
					iter->isAlive = false;
				else
					ResetParticles(&(*iter));
			}
		}

		break;
	}
#pragma endregion
	}

	if (m_bIsRemove)
		RemoveDeadParticles();
}

void CParticleComponent::SetParticleMeshInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex)
{
	m_wstrTextureFileName = _wstrTextureFileName;
	m_iFileBeginIndex = _iBeginIndex;
	m_iFileEndIndex = _iEndIndex;
}

void CParticleComponent::SetParticleInfo(EParticleType _eParticleType, int32 _iParticleNum)
{
	m_eParticleType = _eParticleType;
	m_iParticleNum = _iParticleNum;
}

void CParticleComponent::SetVertexBufferOffsetInfo(uint32 _lVbSize, uint32 _lVbOffset, uint32 _lVbBatchSize)
{
	m_lVbSize = _lVbSize;
	m_lVbOffset = _lVbOffset;
	m_lVbBatchSize = _lVbBatchSize;
}

void CParticleComponent::Reset()
{
	std::list<ParticleAttribute>::iterator iter;
	for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
	{
		ResetParticles(&(*iter));
	}
}

void CParticleComponent::ResetParticles(ParticleAttribute* _tParticleAttribute)
{
	// _tParticleAttribute->position = GetOwnerActor().lock()->GetActorWorldPosition();
	_tParticleAttribute->isAlive = true;
	_tParticleAttribute->position = m_vOrigin; // ��ġ
	_tParticleAttribute->age = 0.0f; // �����ǰ� ���� ������� ����� �ð�
	_tParticleAttribute->lifeTime = m_fParticleLifeTime; // ����
	_tParticleAttribute->particleSpeed = m_fParticleSpeed; // ���� �ӵ�
	_tParticleAttribute->acceleration = m_fParticleAcceleration; // ���� ���ӵ�
	_tParticleAttribute->color = m_tColor; // ����
	_tParticleAttribute->interval = m_fParticleInterval;
	_tParticleAttribute->createTime = m_fParticleCreateTime; // ���� �ð�
	_tParticleAttribute->spreadDegreeXZ = m_fParticleSpreadDegreeXZ; // x,z ���� ����
	_tParticleAttribute->spreadDegreeY = m_fParticleSpreadDegreeY; // y ���� ����

	FVector3 vMin = FVector3{ -1.0f, -1.0f, -1.0f };
	FVector3 vMax = FVector3{ 1.0f, 1.0f, 1.0f };

	switch (m_eParticleType)
	{
#pragma region ������

	case EParticleType::STRAITGHT:
	{
		// ������ ��ƼŬ�� ���Ͱ� �ٶ󺸴� ������ ���� �߻�˴ϴ�.
		_tParticleAttribute->velocity = m_vStraightDir;
		D3DXVec3Normalize(&_tParticleAttribute->velocity, &_tParticleAttribute->velocity);
		_tParticleAttribute->position.y -= 1.0f;

		_tParticleAttribute->acceleration = m_fParticleAcceleration;

		break;
	}
#pragma endregion ������

#pragma region �л���

	// �л���
	case EParticleType::SPRAY:
	{
		// �л��� ��ƼŬ�� ��������� ������ ���͸� ���� �߻�˴ϴ�.
		GetRandomVector(&_tParticleAttribute->velocity, &vMin, &vMax);
		D3DXVec3Normalize(&_tParticleAttribute->velocity, &_tParticleAttribute->velocity);
		_tParticleAttribute->velocity *= _tParticleAttribute->particleSpeed;

		_tParticleAttribute->velocity.x *= GetRandomFloat(-1.0f, 1.0f) * m_fParticleSpreadDegreeXZ;
		_tParticleAttribute->velocity.y *= GetRandomFloat(-1.0f, 1.0f) * m_fParticleSpreadDegreeY;
		_tParticleAttribute->velocity.z *= GetRandomFloat(-1.0f, 1.0f) * m_fParticleSpreadDegreeXZ;

		if (m_bIsRandom)
			_tParticleAttribute->createTime = GetRandomFloat(0.0f, _tParticleAttribute->createTime);

		break;
	}

#pragma endregion �л���

#pragma region ������

	// ������
	case EParticleType::ERUPTION:
	{
		// ������ ��ƼŬ�� ȭ���� ����Ǵ� ���� ��ƼŬ�� �߻��մϴ�.
		vMin.y = 0.0f;
		vMax.y = 5.0f;

		GetRandomVector(&_tParticleAttribute->velocity, &vMin, &vMax);
		D3DXVec3Normalize(&_tParticleAttribute->velocity, &_tParticleAttribute->velocity);

		_tParticleAttribute->velocity *= _tParticleAttribute->particleSpeed;
		_tParticleAttribute->acceleration = m_fParticleAcceleration;

		_tParticleAttribute->velocity.x *= GetRandomFloat(-1.0f, 1.0f) * m_fParticleSpreadDegreeXZ;
		_tParticleAttribute->velocity.y *= GetRandomFloat( 0.0f, 1.0f) * m_fParticleSpreadDegreeY;
		_tParticleAttribute->velocity.z *= GetRandomFloat(-1.0f, 1.0f) * m_fParticleSpreadDegreeXZ;

		if (m_bIsRandom)
			_tParticleAttribute->createTime = GetRandomFloat(0.0f, _tParticleAttribute->createTime);

		break;
	}

#pragma endregion ������

#pragma region �߶���

	// �߶���
	case EParticleType::FALLEN:
	{
		// �߶��� ��ƼŬ�� �Ʒ��� �������ϴ�.(x, z������ �������� ����)
		_tParticleAttribute->velocity.x = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;
		_tParticleAttribute->velocity.y = -GetRandomFloat(1.0f, 0.0f) * _tParticleAttribute->spreadDegreeY;
		_tParticleAttribute->velocity.z = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;

		if (m_bIsRandom)
			_tParticleAttribute->createTime = GetRandomFloat(0.0f, _tParticleAttribute->createTime);

		break;
	}

#pragma endregion �߶���

#pragma region RAIN��

	// ��
	case EParticleType::RAIN:
	{
		_tParticleAttribute->position.x = m_vOrigin.x + GetRandomFloat(-300.0f, 300.0f);
		_tParticleAttribute->position.z = m_vOrigin.z + GetRandomFloat(-300.0f, 300.0f);

		// �� ��ƼŬ�� ������ ��ġ�� ������ ������ �Ʒ��� �������ϴ�.
		_tParticleAttribute->velocity.x = GetRandomFloat(0.0f, 1.0f) * _tParticleAttribute->particleSpeed;
		_tParticleAttribute->velocity.y = -GetRandomFloat(0.0f, 1.0f) * _tParticleAttribute->particleSpeed;
		_tParticleAttribute->velocity.z = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->particleSpeed;

		break;
	}

#pragma endregion RAIN��

#pragma region �������

	case EParticleType::SMOKE:
	{
		_tParticleAttribute->position.x = m_vOrigin.x + GetRandomFloat(-0.1f, 0.1f);
		_tParticleAttribute->position.z = m_vOrigin.z + GetRandomFloat(-0.1f, 0.1f);

		// ����� ��ƼŬ�� ������ �ֺ����� ���������ϴ�
		_tParticleAttribute->velocity.x = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;
		_tParticleAttribute->velocity.y = GetRandomFloat(0.0f, 0.2f) * _tParticleAttribute->spreadDegreeY;
		_tParticleAttribute->velocity.z = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;

		if (m_bIsRandom)
			_tParticleAttribute->createTime = GetRandomFloat(0.0f, _tParticleAttribute->createTime);

		break;
	}

#pragma endregion �������
	}
}

void CParticleComponent::AddParticle()
{
	ParticleAttribute tAttribute;

	for (int32 i = 0; i < m_iParticleNum; ++i)
	{
		ResetParticles(&tAttribute);
		m_lstParticles.push_back(tAttribute);
	}
}

void CParticleComponent::RemoveDeadParticles()
{
	std::list<ParticleAttribute>::iterator iter;

	iter = m_lstParticles.begin();

	while (iter != m_lstParticles.end())
	{
		if (iter->isAlive == false)
		{
			iter = m_lstParticles.erase(iter);
		}
		else
			++iter;
	}
}

float CParticleComponent::GetRandomFloat(float _fLowBound, float _fHighBound)
{
	if (_fLowBound >= _fHighBound)
		return _fLowBound;

	// [ 0, 1 ] ������ ���� float�� ��´�.
	float fResult = (rand() % 10000) * 0.0001f;

	// [ fLowBound, fHighBound ] ������ float�� �����Ѵ�.
	return (fResult * (_fHighBound - _fLowBound)) + _fLowBound;
}

void CParticleComponent::GetRandomVector(FVector3* _vOut, FVector3* _vMin, FVector3* _vMax)
{
	_vOut->x = GetRandomFloat(_vMin->x, _vMax->x);
	_vOut->y = GetRandomFloat(_vMin->y, _vMax->y);
	_vOut->z = GetRandomFloat(_vMin->z, _vMax->z);
}

D3DCOLOR CParticleComponent::ConvertD3DXColorToD3DColor(const D3DXCOLOR& d3dxColor)
{
	// Convert [0, 1] range to [0, 255] range
	BYTE r = static_cast<int>(d3dxColor.r * 255.0f);
	BYTE g = static_cast<int>(d3dxColor.g * 255.0f);
	BYTE b = static_cast<int>(d3dxColor.b * 255.0f);
	BYTE a = static_cast<int>(d3dxColor.a * 255.0f);

	// Create D3DCOLOR
	return D3DCOLOR_ARGB(a, r, g, b);
}