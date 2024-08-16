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

	// �浹���� ��� �۵��ñ� �Լ� ��ӽ�Ű��

public:
	// ������ Ÿ�� ������ ����
	// ������ Ÿ�Ժ��� ���� ������ ����
	// ���� : �����, ����, ����(��ź�߻��), ����, �����, ����ź, ����, ����? �ѹ� ������ �Ѿ˸� ������ ��� �� �� ����. �̱������� ���� �ɵ�?
	// ����� ���� �������� �ٸ���
	// ������ ��� �ε����� ����. ������ ��ġ ����. ��ų� ���� �����Ÿ��� ������ ����

	// �Ѿ� : ����� ���� ����� ����

	// �����۰� �÷��̾� �浹�� ������ Ÿ�� Ȯ��, Ÿ�� Ȯ�� �� �浹�� �Լ� ����

	// �÷��̾�� ��ȣ�ۿ�
	// ���� ������ = ���� Ÿ�� Ȯ��, �����ϰ� �ִ� ��� �浹�ϸ� źâ��ŭ �Ѿ� ����(����ź, ����? ����), �������� �ʴ� ��� ���� ȹ��
	// ���⸦ ���� ���� ���� ������ �Ѿ� ȹ��� �������� ����. ��Ÿ�� �Ἥ ���� ��븸 true false �ϴ°ŵ� ��������?
	// ���� = ü�� ȸ��. ������ �ִ�ü���� ��� �浹 ����. 
	// �Ƶ巹���� = �Ƶ巹������ ��� �ִ�ü�� ����. õõ�� �ִ�ü�±��� ������.
	// �Ƹ� ���� = �� 1�� �ö�
	// �Ƹ��� = �� �ѹ��� �÷���
	
	// ���̴�, ȸ��ŰƮ = �÷��̾ ����. ������ ���������ְ� �Ҹ��ϸ鼭 �۵�, �÷��̾� �ɷ�??

	// �Ѿ��� ����� ��ȣ�ۿ�
	// �Ѿ� = ���� Ÿ�� Ȯ��, �ִ뷮 �̻��� ��� �浹 ����, �ִ뷮 ������ ��� �ִ뷮������ �÷���. �ϳ��� �� ������� �ִ�ġ������ �ö�
	// �Ѿ˰� �÷��̾ �浹�� �Ѿ� Ÿ�Կ� ���缭 ������ ź ������ ����. ���� ���� �ϴ��� �Ѿ� UI�� �������� ������ ������ �ִ� ����
	// ���⸦ ���� ���� ���� ������ �Ѿ� �������� ����

	// ������ ������Ʈ ����
	// ������ ���Ϳ��� ����, ȸ���迭, �Ҹ������ �迭, �Ѿ˷� ����ȭ
	// ���� ���� - Ŭ���̾�Ʈ���� ����ȭ? �����, ����, ����(��ź�߻��), ����, �����, ����ź, ����, ����
	// ȸ���迭 ���� - ����, �Ƹ���, �Ƶ巹����, �Ƹ����� ����ȭ, ���ظ� ������ ����κи� ���� ������ �޴µ�? 
	// �Ѿ� ���� - ����, ����(��ź�߻��), ����, �����, ����ź, ����, ����
	// �ɷ� ���ʹ� �÷��̾� �ɷ��ΰ� ���Ƽ� ���̽��θ� ���� �� �� ����
	 
	// ������ ����
	// GetItemType() { return EItemType; }
	 
	// ���� ������ ����
	// void SetWeaponEnable(WeaponEnable) { WeaponType�� ���� Weapon�� WeaponEnable true�� Ȱ��ȭ } 

	// �Ѿ� ����
	// void SetBullet(WeaponBullet, BulletNumber) { WeaponType�� ���� Weapon�� Bullet �������� BulletNumber �����ֱ� }
	// void CollisionInteraction(SetBullet(WeaponBullet, BulletNumber));

	// ȸ���迭 ����
	// void SetPoint(PlayerHp or Ap, PointNumber) { Hp or Ap�� ���� �÷��̾��� ��������� PointNumber��ŭ �����ֱ� }
	
	// �ɷ� ����
	// void CollisionInteraction(PlayerSkill) { PlayerSkill++; }

	// �÷��̾ ���� ��������� ���ؾ� �ϹǷ� �Լ��� �÷��̾ ���� ������ �־�� �� �� ����

	// ������ ť�� ������. ��� ������ ����ؾ��ҵ�?
};

