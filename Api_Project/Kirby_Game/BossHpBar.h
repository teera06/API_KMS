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

