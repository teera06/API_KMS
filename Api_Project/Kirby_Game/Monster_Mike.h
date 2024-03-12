#pragma once

#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer


class AMonster_Mike : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Mike(); // ����Ʈ ������
	~AMonster_Mike(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Mike(const AMonster_Mike& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Mike(AMonster_Mike&& _Other) noexcept = delete; 
	AMonster_Mike& operator=(const AMonster_Mike& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Mike& operator=(AMonster_Mike&& _Other) noexcept = delete;

	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
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

	FVector DiePos = FVector::Zero; // ���� �̵�

	// �Ϲ� ���� �ൿ ����
	FVector CurLocation = FVector::Zero; // ���� ���� ��ġ ����
	FVector RangeXL = FVector::Zero; // ������ġ ���� ���� �̵� ����
	FVector RangeXR = FVector::Zero; // ������ġ ���� ������ �̵� ����

	float MoveSpeed = 30.0f; // ���� ���ǵ�
	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�

	float RangeX = 100.0f; // �̵� ����

	int WallX = 0; // ���� �浹�Ҷ� X�� ����

	bool BaseOn = false; // Ŀ�񿡰� ��� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool checkLocation = false; // ���� ��ġ üũ

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����
	void BaseMove(float _DeltaTime); // ���� �⺻ ������

	void AniCreate(); // �ִϸ��̼� ����

	void Collisiongather(float _DeltaTime);
	void CalDir();
	void CalResult(float _DeltaTime);

	void GroundUp();

};

