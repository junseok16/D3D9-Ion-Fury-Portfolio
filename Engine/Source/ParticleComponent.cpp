#include "pch.h"
#include "ParticleComponent.h"

#include "DeviceManager.h"
#include "TimerManager.h"

#include "Level.h"
#include "Actor.h"
using namespace std;

void CParticleComponent::Initialize()
{
	// Primitive 세팅
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
		// 렌더링에 앞서 지정해야 할 초기 렌더상태를 지정한다.
		// m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, false);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALEENABLE, true);
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSIZE, FtoDW(m_fParticleSize));
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));

		// 거리에 따른 파티클의 크기를 제어한다.
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(1.0f));
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(1.0f));
		m_pD3DDevice9->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));

		// m_pD3DDevice9->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 0, 0));

		// 텍스처의 알파를 이용한다.
		m_pD3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pD3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		
		m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_pD3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// 디폴트 블렌드 인수와 쓰기 여부를 변경하고자 한다면
		// 엑터의 Render()함수 이전에 SetRenderState 함수로 상태를 변경해주면 된다.
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

			// 텍스처를 들고있는 파티클 클래스인 경우
			if (!m_vecD3DTextures.empty())
				m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[0]);

			m_pD3DDevice9->SetFVF(PARTICLE_FVF);
			m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

			// 버텍스 버퍼를 벗어날 경우 처음부터 시작한다.
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
			// 모든 파티클이 렌더링될 때까지
			//
			std::list<ParticleAttribute>::iterator iter;
			for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
			{
				if (iter->isAlive)
				{
					// 한 단계의 생존한 파티클을 다음 버텍스 버퍼 세그먼트로 복사한다.
					pVertex->position = iter->position;
					pVertex->color = D3DCOLOR(iter->color);
					++pVertex; // 다음 원소
					++lNumParticlesInBatch; // 단계 카운터를 증가시킨다.

					// 현재 단계가 모두 채워져 있는가?
					if (lNumParticlesInBatch == m_lVbBatchSize)
					{
						// 버텍스 버퍼로 복사된 마지막 단계의 파티클들을 그린다.
						m_pVertexBuffer->Unlock();

						// m_pD3DDevice9->SetIndices(m_pIndexBuffer);

						// ※ 인덱스 방식이 되지 않으면 그냥 DrawPrimitive로 바꿔보자 ※
						// m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
						m_pD3DDevice9->DrawPrimitive(D3DPT_POINTLIST, m_lVbOffset, m_lVbBatchSize);


						// 단계가 그려지는 동안 다음 단계를 파티클로 채운다.
						// 다음 단계의 처음 오프셋으로 이동한다.

						m_lVbOffset += m_lVbBatchSize;

						// (예외처리)버텍스 버퍼의 경계를 넘는 메모리로 오프셋을 설정하지 않는다.
						// 경계를 넘을 경우 처음부터 시작한다.
						if (m_lVbOffset > m_lVbSize)
							m_lVbOffset = 0;

						m_pVertexBuffer->Lock(
							m_lVbOffset * m_iVertexSize,
							m_lVbBatchSize * m_iVertexSize,
							(void**)&pVertex,
							m_lVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
						);

						lNumParticlesInBatch = 0; // 다음 단계를 위한 리셋
					}
				}
			}
			m_pVertexBuffer->Unlock();

			// (lNumParticlesInBatch == m_lVbBatchSize) 조건이 만족되지 못하여
			// 마지막 단계가 렌더링되지 않는 경우가 발생할 수 있다. 일부만 채워진 단계는
			// 이곳에서 렌더링된다.
			if (lNumParticlesInBatch)
			{
				// m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
				m_pD3DDevice9->DrawPrimitive(D3DPT_POINTLIST, m_lVbOffset, lNumParticlesInBatch);
			}

			// 다음 블록
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
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, // 동적 버퍼
		m_iVertexFormat,
		m_tD3DPool,
		&m_pVertexBuffer,
		nullptr
	));
}

void CParticleComponent::UpdateParticle(const float& _fDeltaSeconds)
{
	std::list<ParticleAttribute>::iterator iter;

	// 매 프레임 오너액터의 위치정보로 m_vOrgin이 갱신됩니다.
	// m_vOrigin = m_vWorldPosition;

	switch (m_eParticleType)
	{
#pragma region 직선형 파티클
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
		
#pragma region 분사형 파티클
	case EParticleType::SPRAY:
	{
		for (iter = m_lstParticles.begin(); iter != m_lstParticles.end(); ++iter)
		{
			iter->age += _fDeltaSeconds;
			if (iter->age > iter->createTime)
			{
				// 거리 = (v * t) + (0.5f * a * t^2);
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

#pragma region 분출형 파티클

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

#pragma region 추락형 파티클
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

#pragma region 비 파티클
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

#pragma region 스모그형
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
	_tParticleAttribute->position = m_vOrigin; // 위치
	_tParticleAttribute->age = 0.0f; // 생성되고 나서 현재까지 진행된 시간
	_tParticleAttribute->lifeTime = m_fParticleLifeTime; // 수명
	_tParticleAttribute->particleSpeed = m_fParticleSpeed; // 진행 속도
	_tParticleAttribute->acceleration = m_fParticleAcceleration; // 진행 가속도
	_tParticleAttribute->color = m_tColor; // 색상
	_tParticleAttribute->interval = m_fParticleInterval;
	_tParticleAttribute->createTime = m_fParticleCreateTime; // 생성 시간
	_tParticleAttribute->spreadDegreeXZ = m_fParticleSpreadDegreeXZ; // x,z 퍼짐 정도
	_tParticleAttribute->spreadDegreeY = m_fParticleSpreadDegreeY; // y 퍼짐 정도

	FVector3 vMin = FVector3{ -1.0f, -1.0f, -1.0f };
	FVector3 vMax = FVector3{ 1.0f, 1.0f, 1.0f };

	switch (m_eParticleType)
	{
#pragma region 직선형

	case EParticleType::STRAITGHT:
	{
		// 직선형 파티클은 액터가 바라보는 방향을 향해 발사됩니다.
		_tParticleAttribute->velocity = m_vStraightDir;
		D3DXVec3Normalize(&_tParticleAttribute->velocity, &_tParticleAttribute->velocity);
		_tParticleAttribute->position.y -= 1.0f;

		_tParticleAttribute->acceleration = m_fParticleAcceleration;

		break;
	}
#pragma endregion 직선형

#pragma region 분사형

	// 분사형
	case EParticleType::SPRAY:
	{
		// 분사형 파티클은 진행방향이 랜덤인 벡터를 향해 발사됩니다.
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

#pragma endregion 분사형

#pragma region 분출형

	// 분출형
	case EParticleType::ERUPTION:
	{
		// 분출형 파티클은 화산이 분출되는 듯한 파티클을 발사합니다.
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

#pragma endregion 분출형

#pragma region 추락형

	// 추락형
	case EParticleType::FALLEN:
	{
		// 추락형 파티클은 아래로 떨어집니다.(x, z방향은 랜덤으로 결정)
		_tParticleAttribute->velocity.x = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;
		_tParticleAttribute->velocity.y = -GetRandomFloat(1.0f, 0.0f) * _tParticleAttribute->spreadDegreeY;
		_tParticleAttribute->velocity.z = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;

		if (m_bIsRandom)
			_tParticleAttribute->createTime = GetRandomFloat(0.0f, _tParticleAttribute->createTime);

		break;
	}

#pragma endregion 추락형

#pragma region RAIN형

	// 비
	case EParticleType::RAIN:
	{
		_tParticleAttribute->position.x = m_vOrigin.x + GetRandomFloat(-300.0f, 300.0f);
		_tParticleAttribute->position.z = m_vOrigin.z + GetRandomFloat(-300.0f, 300.0f);

		// 비 파티클은 랜덤한 위치와 방향을 가지고 아래로 떨어집니다.
		_tParticleAttribute->velocity.x = GetRandomFloat(0.0f, 1.0f) * _tParticleAttribute->particleSpeed;
		_tParticleAttribute->velocity.y = -GetRandomFloat(0.0f, 1.0f) * _tParticleAttribute->particleSpeed;
		_tParticleAttribute->velocity.z = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->particleSpeed;

		break;
	}

#pragma endregion RAIN형

#pragma region 스모그형

	case EParticleType::SMOKE:
	{
		_tParticleAttribute->position.x = m_vOrigin.x + GetRandomFloat(-0.1f, 0.1f);
		_tParticleAttribute->position.z = m_vOrigin.z + GetRandomFloat(-0.1f, 0.1f);

		// 스모그 파티클은 서서히 주변으로 퍼져나갑니다
		_tParticleAttribute->velocity.x = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;
		_tParticleAttribute->velocity.y = GetRandomFloat(0.0f, 0.2f) * _tParticleAttribute->spreadDegreeY;
		_tParticleAttribute->velocity.z = GetRandomFloat(-1.0f, 1.0f) * _tParticleAttribute->spreadDegreeXZ;

		if (m_bIsRandom)
			_tParticleAttribute->createTime = GetRandomFloat(0.0f, _tParticleAttribute->createTime);

		break;
	}

#pragma endregion 스모그형
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

	// [ 0, 1 ] 범위의 임의 float을 얻는다.
	float fResult = (rand() % 10000) * 0.0001f;

	// [ fLowBound, fHighBound ] 범위의 float을 리턴한다.
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