#pragma once
// ���
#include <EngineCore/Actor.h>

#include "ModeEnum.h"
#include "ActorCommon.h"

#include "Kirby_Player.h"
#include "SubBoss.h"

class ABossHpBar : public AActor, public UActorCommon // ActorCommon(�߷�)
{
public:
	// constrcuter destructer
	ABossHpBar(); // ����Ʈ ������
	~ABossHpBar(); // ����Ʈ �Ҹ���

	// delete Function
	ABossHpBar(const ABossHpBar& _Other) = delete; // ����Ʈ ���� ������
	ABossHpBar(ABossHpBar&& _Other) noexcept = delete; 
	ABossHpBar& operator=(const ABossHpBar& _Other) = delete; // ����Ʈ ���� ������
	ABossHpBar& operator=(ABossHpBar&& _Other) noexcept = delete;

	int GetHp() const
	{
		return Hp;
	}

	void SetHp(const int& _Hp)
	{
		Hp = _Hp;
	}

	void AddHP(const int& _Value)
	{
		Hp += _Value;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* HpRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* HpAddRenderer = nullptr; // Ŀ�� ������ (�̹���)

	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // �������� Ȯ�ο�
	ASubBoss* SubBoss = ASubBoss::GetMainSubBoss();

	FVector Move = FVector::Zero;

	int Hp = 100;
};

