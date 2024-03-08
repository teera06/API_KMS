#pragma once
// ���
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMonster_Base : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Base(); // ����Ʈ ������
	~AMonster_Base(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Base(const AMonster_Base& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Base(AMonster_Base&& _Other) noexcept = delete;
	AMonster_Base& operator=(const AMonster_Base& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Base& operator=(AMonster_Base&& _Other) noexcept = delete;

	UImageRenderer* GetMonsterRenderer() // Get ����
	{
		return MonsterRenderer;
	}

	void IceState(); // ���̽� ������ ������ ��

	void SetBaseOnOff(const bool& _BaseOn) // ���̽� ���� ������ �� �� Ȯ�� Set
	{
		BaseOn = _BaseOn; // ��� ���� �������� true
	}

	void SetIsDie(const bool& _IsDie) // ���� ���� bool
	{
		IsDie = _IsDie;
	}

	void SetDiePos(const FVector& _DiePos) // ���Ͱ� �����鼭 �̵��ϴ� ��ġ Set
	{
		DiePos = _DiePos;
	}
protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr; // ���� �ݸ���

	FVector StartDir = FVector::Right; // ���� �ʹ� �̵� ����

	FVector IceMove = FVector::Zero; // ���� �̵� 
	FVector DiePos = FVector::Zero; // ���� �̵�
	// �Ϲ� ���� �ൿ ����
	FVector CurLocation = FVector::Zero; // ���� ���� ��ġ ����
	FVector RangeXL = FVector::Zero; // ������ġ ���� ���� �̵� ����
	FVector RangeXR = FVector::Zero; // ������ġ ���� ������ �̵� ����

	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�
	float MoveSpeed = 30.0f; // ���� ���ǵ�
	float RangeX = 100.0f; // �̵� ����
	
	int WallX = 0; // ���� �浹�Ҷ� X�� ����

	bool BaseOn = false; // Ŀ�񿡰� ��� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool IsIce = false; // ���� �������� Ȯ��
	bool checkLocation = false; // ���� ��ġ üũ

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����
	void BaseMove(float _DeltaTime); // ���� �⺻ ������

	void AniCreate(); // �ִϸ��̼� ����

	void IceToMonster(float _DeltaTime); // ���� ������ �� �浹 ����
	void Collisiongather(float _DeltaTime); // ���� ���� �����϶� �浹 ����
	void CalDir(); // �÷��̾� ��ġ ���
	void CalResult(float _DeltaTime); // ���� ������ ���

	void GroundUp(); // �� ���� �ذ�
};

