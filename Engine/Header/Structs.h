#pragma once
#include "Types.h"

#pragma region Position, Color Vertex

struct ColorVertex
{
	FVector3 position;
	uint32 color;
};

struct ColorIndex
{
	uint32 _0, _1, _2;
};

#define COLOR_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0)

#pragma endregion

#pragma region Position, UV Texture Vertex

struct TextureVertex
{
	FVector3 position;
	FVector3 normal;
	FVector2 uv;
};

struct TextureIndex
{
	uint32 _0, _1, _2;
};

#define TEXTURE_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#pragma endregion

#pragma region Position, Normal, UV Texture Vertex

struct NormalVertex
{
	FVector3 position;	// 정점의 위치 벡터
	FVector3 normal;	// 정점의 법선 벡터
	FVector2 uv;		// 정점의 텍스처 좌표
};

struct NormalIndex
{
	uint32 _0, _1, _2;	// 삼각형의 인덱스
};

#define NORMAL_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#pragma endregion

#pragma region Cube(Position ,UV Texture)

struct CubeTextureVertex
{
	FVector3 position;
	FVector3 normal;
	FVector3 uv;
};

struct CubeTextureIndex
{
	uint32 _0, _1, _2;	// 삼각형의 인덱스
};

#define CUBE_TEXTURE_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0))

#pragma endregion

#pragma region Player Information

struct PlayerInfo
{
	FVector3 position;
	FMatrix forword;
	float Hp;
};

#pragma endregion

// 11.03 파티클 시스템을 위해 추가 - 박동연 -

#pragma region Particle

struct ParticleVertex
{
	FVector3 position;
	uint32 color;
};

struct ParticleIndex
{
	uint32 _0, _1, _2;
};

#define PARTICLE_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct ParticleAttribute
{
	FVector3 position;
	FVector3 velocity;
	float interval; // 간격
	float acceleration; // 진행 가속도
	float particleSpeed; // 진행 속도
	float lifeTime;	// 라이프타임
	float createTime; // 생성 시간
	float age; // 나이
	float spreadDegreeXZ; // x,z 퍼짐 정도
	float spreadDegreeY; // y 퍼짐 정도
	D3DXCOLOR color;
	D3DXCOLOR colorFade;
	bool isAlive;
};

#pragma endregion