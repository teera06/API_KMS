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

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	FVector MovePos = FVector::Zero;

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����

	void AniCreate(); // �ִϸ��̼� ����

	void CalDir(float _DeltaTime);
	//void Att1(float _DeltaTime);
	//void Att2();

	//void AttCollisiongather(float _DeltaTime);
	//void Collisiongather(float _DeltaTime);
	//void CalResult(float _DeltaTime);
	//void hitEvent();

	void GroundUp();

	bool Ishit = false; // ���� ���� ���� Ȯ��
	bool IsAtt = false;

	int WallX = 0; // ���� �浹�Ҷ� X�� ����
	int RandomAtt = 0;
	int Hp = 100;

	float skillcooldowntime = 3.0f;
	float MoveSpeed = 50.0f; // ���� ���ǵ�
};
