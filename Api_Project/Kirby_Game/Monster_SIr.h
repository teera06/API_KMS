#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AMonster_Sir : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Sir(); // ����Ʈ ������
	~AMonster_Sir(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Sir(const AMonster_Sir& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Sir(AMonster_Sir&& _Other) noexcept = delete; 
	AMonster_Sir& operator=(const AMonster_Sir& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Sir& operator=(AMonster_Sir&& _Other) noexcept = delete;
	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}
	
	void IceState();

	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
	}

	void SetIsDie(const bool& _IsDie)
	{
		IsDie = _IsDie;
	}

	void SetDiePos(const FVector& _DiePos)
	{
		DiePos = _DiePos;
	}

	void SetSirUse(const bool& _SirUse)
	{
		SirUse = _SirUse;
	}
protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* MonsterDieRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Left; // ���� �ʹ� �̵� ����

	FVector IceMove = FVector::Zero; // ���� �̵� 
	FVector DiePos = FVector::Zero; // ���� �̵�
	// �Ϲ� ���� �ൿ ����
	FVector CurLocation = FVector::Zero; // ���� ���� ��ġ ����
	FVector RangeXL = FVector::Zero; // ������ġ ���� ���� �̵� ����
	FVector RangeXR = FVector::Zero; // ������ġ ���� ������ �̵� ����

	float skillcooldowntime = 0.0f;
	float MoveSpeed = 30.0f; // ���� ���ǵ�
	float RangeX = 100.0f; // �̵� ����
	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�

	int WallX = 0; // ���� �浹�Ҷ� X�� ����
	
	bool BaseOn = false; // Ŀ�񿡰� ��� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool IsIce = false; // ���� �������� Ȯ��
	bool IsAtt = false;
	bool SirUse = false;
	bool SIrAttackCheck = false;
	bool checkLocation = false; // ���� ��ġ üũ
	bool Iseffect = false;

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����
	void BaseMove(float _DeltaTime); // ���� �⺻ ������

	void AniCreate(); // �ִϸ��̼� ����

	void SirAtt(); // ����
	void IceToMonster(float _DeltaTime); // ���� ���� �ൿ ����
	void Collisiongather(float _DeltaTime);// �ݸ��� ����
	void CalDir(); // ���� ���� ���
	void CalResult(float _DeltaTime); // ���� �̵� �Ǵ�

	void GroundUp();
};

