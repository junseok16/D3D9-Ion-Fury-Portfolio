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
	FVector3 position;	// ������ ��ġ ����
	FVector3 normal;	// ������ ���� ����
	FVector2 uv;		// ������ �ؽ�ó ��ǥ
};

struct NormalIndex
{
	uint32 _0, _1, _2;	// �ﰢ���� �ε���
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
	uint32 _0, _1, _2;	// �ﰢ���� �ε���
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

// 11.03 ��ƼŬ �ý����� ���� �߰� - �ڵ��� -

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
	float interval; // ����
	float acceleration; // ���� ���ӵ�
	float particleSpeed; // ���� �ӵ�
	float lifeTime;	// ������Ÿ��
	float createTime; // ���� �ð�
	float age; // ����
	float spreadDegreeXZ; // x,z ���� ����
	float spreadDegreeY; // y ���� ����
	D3DXCOLOR color;
	D3DXCOLOR colorFade;
	bool isAlive;
};

#pragma endregion