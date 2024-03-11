#pragma once

#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMainBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMainBoss(); // ����Ʈ ������
	~AMainBoss(); // ����Ʈ �Ҹ���

	// delete Function
	AMainBoss(const AMainBoss& _Other) = delete; // ����Ʈ ���� ������
	AMainBoss(AMainBoss&& _Other) noexcept = delete; 
	AMainBoss& operator=(const AMainBoss& _Other) = delete; // ����Ʈ ���� ������
	AMainBoss& operator=(AMainBoss&& _Other) noexcept = delete;
	
	static AMainBoss* GetMainBoss(); // ���ͳ� ����â�� �÷��̾ ���� ������ �˾ƾ� �� �� ���

	UCollision* GetMonsterCollision()
	{
		return MonsterCollision;
	}

	int GetHp() const
	{
		return Hp;
	}

	void AddHP(const int& _Value)
	{
		Hp += _Value;
	}

	void SetIshit(const bool& _Ishit)
	{
		Ishit = _Ishit;
	}

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* Att2Renderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	UCollision* Att1Collision = nullptr;
	UCollision* Att3Collision = nullptr;
	
	static AMainBoss* MainBoss;

	FVector MovePos = FVector::Zero;
	FVector JumpVector = FVector::Up*750.0f;

	float skillcooldowntime = 3.0f;
	float MoveSpeed = 50.0f; // ���� ���ǵ�

	int WallX = 0; // ���� �浹�Ҷ� X�� ����
	int RandomAtt = 0;
	int Hp = 100;


	bool Ishit = false; 
	bool IsAtt = false;
	bool IsBullet = false;
	bool IsIce = false;
	bool Att1Ready = false;
	bool Att3Delay = false;
	bool Att2Delay = false;
	bool Att4Ready = false;

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����

	void AniCreate(); // �ִϸ��̼� ����

	void CalDir(float _DeltaTime);
	void Att1(float _DeltaTime);
	void Att2();
	void Att3(float _DeltaTime);
	void Att4(float _DeltaTime);

	void Att1Collisiongather(float _DeltaTime);
	void Att3Collisiongather(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);
	void hitEvent();

	void GroundUp();
};

