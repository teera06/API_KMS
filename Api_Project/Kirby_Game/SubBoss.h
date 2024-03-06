#pragma once
// ���
#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class ASubBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ASubBoss(); // ����Ʈ ������
	~ASubBoss(); // ����Ʈ �Ҹ���

	// delete Function
	ASubBoss(const ASubBoss& _Other) = delete; // ����Ʈ ���� ������
	ASubBoss(ASubBoss&& _Other) noexcept = delete; 
	ASubBoss& operator=(const ASubBoss& _Other) = delete; // ����Ʈ ���� ������
	ASubBoss& operator=(ASubBoss&& _Other) noexcept = delete;

	static ASubBoss* GetMainSubBoss(); // ���ͳ� ����â�� �÷��̾ ���� ������ �˾ƾ� �� �� ���

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	int GetHp() const
	{ 
		return Hp;
	}

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	static ASubBoss* MainSubBoss;

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	UImageRenderer* AttRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* AttCollision = nullptr;

	FVector StartDir = FVector::Left; // ���� �ʹ� �̵� ����
	FVector MovePos = FVector::Zero;

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����

	void AniCreate(); // �ִϸ��̼� ����

	void CalDir(float _DeltaTime);
	void Att1(float _DeltaTime);
	void Att2();

	void AttCollisiongather(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);

	void GroundUp();

	bool BaseOn = false; // Ŀ�񿡰� ��� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool IsIce = false; // ���� �������� Ȯ��
	bool IsAtt = false;

	int WallX = 0; // ���� �浹�Ҷ� X�� ����
	int RandomAtt = 0;
	int Hp = 100;

	float skillcooldowntime = 3.0f;
	float MoveSpeed = 50.0f; // ���� ���ǵ�
	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�
	const float sight = 250.0f; // ���� �þ�
};

