#pragma once
// ���
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class SubBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	SubBoss(); // ����Ʈ ������
	~SubBoss(); // ����Ʈ �Ҹ���

	// delete Function
	SubBoss(const SubBoss& _Other) = delete; // ����Ʈ ���� ������
	SubBoss(SubBoss&& _Other) noexcept = delete; 
	SubBoss& operator=(const SubBoss& _Other) = delete; // ����Ʈ ���� ������
	SubBoss& operator=(SubBoss&& _Other) noexcept = delete;

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Left; // ���� �ʹ� �̵� ����
	FVector MovePos = FVector::Zero;

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����

	void AniCreate(); // �ִϸ��̼� ����

	void IceToMonster(float _DeltaTime);

	void CalDir(float _DeltaTime);
	void IceAtt();

	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);


	void GroundUp();

	bool BaseOn = false; // Ŀ�񿡰� ��� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool IsIce = false; // ���� �������� Ȯ��
	bool IsAtt = false;
	float skillcooldowntime = 0.0f;

	int WallX = 0; // ���� �浹�Ҷ� X�� ����

	float MoveSpeed = 50.0f; // ���� ���ǵ�
	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�
	const float sight = 250.0f; // ���� �þ�
	const float AttRange = 150.0f; // ���� ���� ����
};

