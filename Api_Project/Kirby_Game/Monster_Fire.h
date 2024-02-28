#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMonster_Fire : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Fire(); // ����Ʈ ������
	~AMonster_Fire(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Fire(const AMonster_Fire& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Fire(AMonster_Fire&& _Other) noexcept = delete; 
	AMonster_Fire& operator=(const AMonster_Fire& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Fire& operator=(AMonster_Fire&& _Other) noexcept = delete;

	void IceState();

	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
	}

	bool GetBaseOnOff() const
	{
		return BaseOn;
	}

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	void SetIsDie(const bool& _IsDie)
	{
		IsDie = _IsDie;
	}

	void SetDiePos(const FVector& _DiePos)
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
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Left; // ���� �ʹ� �̵� ����

	FVector IceMove = FVector::Zero; // ���� �̵� 
	FVector DiePos = FVector::Zero; // ���� �̵�
	FVector MovePos = FVector::Zero;
	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����
	void BaseMove(float _DeltaTime); // ���� �⺻ ������

	void AniCreate(); // �ִϸ��̼� ����

	void IceToMonster(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalDir(float _DeltaTime);
	void CalResult(float _DeltaTime);

	void GroundUp();

	bool BaseOn = false; // Ŀ�񿡰� ���� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool IsIce = false; // ���� �������� Ȯ��
	bool checkLocation = false; // ���� ��ġ üũ
	bool IsAtt = false;

	int WallX = 0; // ���� �浹�Ҷ� X�� ����

	float MoveSpeed = 30.0f; // ���� ���ǵ�
	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�

	// �Ϲ� ���� �ൿ ����
	FVector CurLocation = FVector::Zero; // ���� ���� ��ġ ����
	FVector RangeXL = FVector::Zero; // ������ġ ���� ���� �̵� ����
	FVector RangeXR = FVector::Zero; // ������ġ ���� ������ �̵� ����
	float RangeX = 100.0f; // �̵� ����

	const float sight = 250.0f; // ���� �þ�
	const float AttRange = 150.0f; // ���� ���� ����
};
