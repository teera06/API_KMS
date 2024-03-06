#pragma once
// ���
#include <EngineCore/Actor.h>

#include "ModeEnum.h"
#include "ActorCommon.h"

#include "Kirby_Player.h"
#include "SubBoss.h"

class BossHpBar : public AActor, public UActorCommon // ActorCommon(�߷�)
{
public:
	// constrcuter destructer
	BossHpBar(); // ����Ʈ ������
	~BossHpBar(); // ����Ʈ �Ҹ���

	// delete Function
	BossHpBar(const BossHpBar& _Other) = delete; // ����Ʈ ���� ������
	BossHpBar(BossHpBar&& _Other) noexcept = delete; 
	BossHpBar& operator=(const BossHpBar& _Other) = delete; // ����Ʈ ���� ������
	BossHpBar& operator=(BossHpBar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* HpRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* HpAddRenderer = nullptr; // Ŀ�� ������ (�̹���)
	
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer();
	ASubBoss* SubBoss = ASubBoss::GetMainSubBoss();

	FVector Move = FVector::Zero;
};

