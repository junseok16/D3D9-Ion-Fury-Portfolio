#pragma once

/************************
	엔진 열거체
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
	컴포넌트 열거체
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
	STRAITGHT, // 직선
	SPRAY, // 분사
	ERUPTION, // 분출
	FALLEN, // 추락
	RAIN, // 비
	SMOKE, // 연기
	ENUM_END
};

enum class EDistanceModel
{
	Linear,			// 선형 감쇠
	Logarithmic,	// 지수형 감쇠 
	LogReverse,		// 역지수 감쇠
	Inverse,		// 역감쇠
	ENUM_END
};

/************************
	입력 열거체
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
	클라이언트 열거체
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
	ELECTRIFRYER,	// 전기봉, 데미지 10
	LOVERBOY,		// 권총, 탄수 6/90, 우클릭시 자동 조준(최대 3명 조준), 우클릭 해제시 2발씩 사격
	DISPERSER,		// 샷건(유탄발사기), 탄수 6/48
	PENETRATOR,		// SMG, 탄수 40(80)/320, 무려 양손에 들 수 있음...! 소이탄이라 불 붙음, 4번 클릭시 양손이냐 단일이냐 결정 가능
	CHAINGUN,		// 기관총
	BOWLINGBOMBS,	// 수류탄, 던지면 알아서 적 찾아 굴러감, 적을 못찾으면 멈추고 다시 주울 수 있음. 우클릭시 불을 붙여서 일정 시간 내에 무조건 터짐, 적과 마주치면 빨리 터짐
	IONBOW,			// 석궁, 탄수 15/75, 감전 효과 있음, 우클릭은 여러 방향으로 동시 발사, 
	CLUSTERPUCK,	// 지뢰, 우클릭은 파편 폭발로 낮은 데미지 넓은 범위 피해, 금이 간 벽을 뚫을 수 있다, 벽에 설치 가능
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
	MEDKIT,				// 회복 35퍼
	RADAR,				// 레이더
	ACCELBOOST,			// 이속 증가
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
	EFFECT,		// 이펙트 사운드	
	VOICE,		// 음성 사운드
	BGM,		// bgm 사운드
	MAXCHANNEL, // 최대 경로
	ITEM,
	// 보스
	MOVE,
	FIRE,
	SMASH,
	DAMAGE,
	WARNING,

	ENUM_END	// 최대 채널
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

// 동준 추가 문 관련 상태
enum class EGateState
{
	OPENED = 0,
	CLOSED = 1,
	STOPPED = 2
};