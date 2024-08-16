#pragma once
#include "Actor.h"

class CRectangleMeshComponent;

class CItemActor : public CActor
{
public:
	explicit CItemActor() = default;
	virtual ~CItemActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	// 충돌했을 경우 작동시길 함수 상속시키기

public:
	// 아이템 타입 가지고 있음
	// 아이템 타입별로 하위 종류가 있음
	// 무기 : 전기봉, 권총, 샷건(유탄발사기), 소총, 기관총, 수류탄, 석궁, 지뢰? 한번 먹으면 총알만 없을뿐 계속 쓸 수 있음. 싱글톤으로 만들어도 될듯?
	// 무기와 무기 아이템은 다른것
	// 지뢰의 경우 부딪히면 터짐. 벽에다 설치 가능. 쏘거나 몬스터 일정거리에 들어오면 터짐

	// 총알 : 전기봉 제외 무기와 동일

	// 아이템과 플레이어 충돌시 아이템 타입 확인, 타입 확인 후 충돌시 함수 실행

	// 플레이어와 상호작용
	// 무기 아이템 = 무기 타입 확인, 보유하고 있는 경우 충돌하면 탄창만큼 총알 증가(수류탄, 지뢰? 제외), 보유하지 않는 경우 무기 획득
	// 무기를 갖고 있지 않을 때에도 총알 획득시 보유량은 증가. 불타입 써서 무기 사용만 true false 하는거도 괜찮을듯?
	// 힐팩 = 체력 회복. 힐팩은 최대체력일 경우 충돌 무시. 
	// 아드레날린 = 아드레날린의 경우 최대체력 무시. 천천히 최대체력까지 낮아짐.
	// 아머 코인 = 방어도 1씩 올라감
	// 아머팩 = 방어도 한번에 올려줌
	
	// 레이더, 회복키트 = 플레이어가 소지. 갯수만 증가시켜주고 소모하면서 작동, 플레이어 능력??

	// 총알은 무기와 상호작용
	// 총알 = 무기 타입 확인, 최대량 이상일 경우 충돌 무시, 최대량 이하일 경우 최대량까지만 올려줌. 하나만 비어도 사라지고 최대치까지만 올라감
	// 총알과 플레이어가 충돌시 총알 타입에 맞춰서 무기의 탄 보유량 증가. 원본 게임 하단의 총알 UI는 장전수와 보유량 합쳐져 있는 상태
	// 무기를 갖고 있지 않을 때에도 총알 보유량은 증가

	// 아이템 컴포넌트 제작
	// 아이템 엑터에서 무기, 회복계열, 소모아이템 계열, 총알로 세분화
	// 무기 액터 - 클라이언트에서 세분화? 전기봉, 권총, 샷건(유탄발사기), 소총, 기관총, 수류탄, 석궁, 지뢰
	// 회복계열 액터 - 힐팩, 아머팩, 아드레날린, 아머코인 세분화, 피해를 입을때 몸통부분만 방어구가 데미지 받는듯? 
	// 총알 액터 - 권총, 샷건(유탄발사기), 소총, 기관총, 수류탄, 석궁, 지뢰
	// 능력 액터는 플레이어 능력인거 같아서 베이스로만 만들어도 될 거 같음
	 
	// 아이템 액터
	// GetItemType() { return EItemType; }
	 
	// 무기 아이템 엑터
	// void SetWeaponEnable(WeaponEnable) { WeaponType이 같은 Weapon의 WeaponEnable true로 활성화 } 

	// 총알 액터
	// void SetBullet(WeaponBullet, BulletNumber) { WeaponType이 같은 Weapon의 Bullet 보유량에 BulletNumber 더해주기 }
	// void CollisionInteraction(SetBullet(WeaponBullet, BulletNumber));

	// 회복계열 액터
	// void SetPoint(PlayerHp or Ap, PointNumber) { Hp or Ap가 같은 플레이어의 멤버변수에 PointNumber만큼 더해주기 }
	
	// 능력 액터
	// void CollisionInteraction(PlayerSkill) { PlayerSkill++; }

	// 플레이어나 총의 멤버변수가 변해야 하므로 함수를 플레이어나 총이 가지고 있어야 할 것 같다

	// 아이템 큐브 형식임. 어떻게 만들지 고민해야할듯?
};

