#pragma once

/************************
	���� ����ü
************************/
enum class EWindowMode
{
	FULL_SCREEN,
	WINDOWED,
	ENUM_END
};

enum class ETextureType
{
	COLOR,
	TEXTURE,
	CUBE_TEXTURE,
	ENUM_END
};

enum class ERenderType
{
	NON_ALPHA,
	ALPHA_TEST,
	ALPHA_BLEND,
	ALPHA_BLEND_ORTHOGONAL,
	ORTHOGONAL,
	USER_INTERFACE,
	ENUM_END
};

enum class EResourceType
{
	TEXTURE,
	SOUND,
	ENUM_END
};


/************************
	������Ʈ ����ü
************************/
enum class EPrimitiveType
{
	MESH,
	COLLIDER,
	LANDSCAPE,
	ENUM_END
};

enum class EMeshType
{
	NONE,
	RECTANGLE,
	CUBE,
	ENUM_END
};

enum class EAnimationType
{
	DESIGNATED_TIME,
	LOOP,
	ENUM_END
};

enum class ECollisionLayerType
{
	PLAYER,
	MONSTER,
	GROUND,
	WALL,
	INTERACTION,
	ITEM,
	ITEMOBJECT,
	PROJECTILE,
	ENUM_END
};

enum class EColliderType
{
	NONE,
	RECT,
	CUBE,
	SPHERE,
	ENUM_END
};

enum class EUserInterfaceType
{
	DYNAMIC,
	STATIC,
	ENUM_END
};

enum class EMobilityType
{
	DYNAMIC,
	STATIC,
	ENUM_END
};

enum class EProjectionType
{
	ORTHOGONAL,
	PERSPECTIVE,
};

enum class ECameraViewType
{
	FREE,
	FIRST_PERSON,
	THIRD_PERSON,
	SIDE,
	TOP_DOWN,
	QUARTER,
	ENUM_END,
};

enum class ECompositeType
{
	SEQUENCE,
	SELECTOR,
	PARALLEL,
};

enum class EBTNodeType
{
	COMPOSITE,
	TASK,
	DECORATOR,
	ENUM_END
};

enum class EBTNodeResult
{
	SUCCEEDED,
	FAILED,
	IN_PROGRESS,
	ENUM_END
};

enum class ETaskType
{
	WAIT,
	MOVE_TO,
	PLAY_SOUND,
	RUN_BEHAVIOR,
	PLAY_ANIMATION,
};

enum class EParticleType
{
	STRAITGHT, // ����
	SPRAY, // �л�
	ERUPTION, // ����
	FALLEN, // �߶�
	RAIN, // ��
	SMOKE, // ����
	ENUM_END
};

enum class EDistanceModel
{
	Linear,			// ���� ����
	Logarithmic,	// ������ ���� 
	LogReverse,		// ������ ����
	Inverse,		// ������
	ENUM_END
};

/************************
	�Է� ����ü
************************/
enum class EMouseState
{
	DOWN,
	PRESSED,
	UP,
	RELEASED,
	ENUM_END
};

enum class EKeyState
{
	DOWN,
	PRESSED,
	UP,
	RELEASED,
	ENUM_END
};

enum class EMouseButtonType
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	SCROLL_WHEEL_BUTTON,
	ENUM_END
};

enum class EAxisType
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	ENUM_END
};

/************************
	Ŭ���̾�Ʈ ����ü
************************/
enum class EItemType
{
	WEAPON,
	BULLET,
	RECOVERY,
	SKILL,
	CARDKEY,
	ENUM_END
};

enum class EWeaponType
{
	ELECTRIFRYER,	// �����, ������ 10
	LOVERBOY,		// ����, ź�� 6/90, ��Ŭ���� �ڵ� ����(�ִ� 3�� ����), ��Ŭ�� ������ 2�߾� ���
	DISPERSER,		// ����(��ź�߻��), ź�� 6/48
	PENETRATOR,		// SMG, ź�� 40(80)/320, ���� ��տ� �� �� ����...! ����ź�̶� �� ����, 4�� Ŭ���� ����̳� �����̳� ���� ����
	CHAINGUN,		// �����
	BOWLINGBOMBS,	// ����ź, ������ �˾Ƽ� �� ã�� ������, ���� ��ã���� ���߰� �ٽ� �ֿ� �� ����. ��Ŭ���� ���� �ٿ��� ���� �ð� ���� ������ ����, ���� ����ġ�� ���� ����
	IONBOW,			// ����, ź�� 15/75, ���� ȿ�� ����, ��Ŭ���� ���� �������� ���� �߻�, 
	CLUSTERPUCK,	// ����, ��Ŭ���� ���� ���߷� ���� ������ ���� ���� ����, ���� �� ���� ���� �� �ִ�, ���� ��ġ ����
	ENUM_END
};

enum class ERecoveryType
{
	HEALTHPACK,
	SYRINGE,
	ARMOR,
	ARMORPIECE,
	CARDKEY,
	ENUM_END
};

enum class ESkillType
{
	MEDKIT,				// ȸ�� 35��
	RADAR,				// ���̴�
	ACCELBOOST,			// �̼� ����
	ENUM_END
};

enum class EMonsterType
{
	MECHSECT,
	DEACON,
	CULTIST,
	PUSTULE,
	ENUM_END,
};

enum class ESoundType 
{ 
	EFFECT,		// ����Ʈ ����	
	VOICE,		// ���� ����
	BGM,		// bgm ����
	MAXCHANNEL, // �ִ� ���
	ITEM,
	// ����
	MOVE,
	FIRE,
	SMASH,
	DAMAGE,
	WARNING,

	ENUM_END	// �ִ� ä��
};

enum class EMonsterState
{ 
	IDLE = 0,
	WALK = 1,
	CHASE = 2,
	ATTACK = 3,
	ATTACKED = 4,
	SHOCK = 5,
	DEAD = 99,
};

enum class EWarmechPhase
{
	READY,
	PHASE_0,
	PHASE_1,
	PHASE_2,
	DEAD,
	ENUM_END
};

enum class EFireType
{
	STRAIGHT,
	ROUND,
	PARABOLA,
	ENUM_END,
};

// ���� �߰� �� ���� ����
enum class EGateState
{
	OPENED = 0,
	CLOSED = 1,
	STOPPED = 2
};