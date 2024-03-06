#pragma once
// 상속
#include <EngineCore/Actor.h>

#include "ModeEnum.h"
#include "ActorCommon.h"

#include "Kirby_Player.h"
#include "SubBoss.h"

class BossHpBar : public AActor, public UActorCommon // ActorCommon(중력)
{
public:
	// constrcuter destructer
	BossHpBar(); // 디폴트 생성자
	~BossHpBar(); // 디폴트 소멸자

	// delete Function
	BossHpBar(const BossHpBar& _Other) = delete; // 디폴트 복사 생성자
	BossHpBar(BossHpBar&& _Other) noexcept = delete; 
	BossHpBar& operator=(const BossHpBar& _Other) = delete; // 디폴트 대입 연산자
	BossHpBar& operator=(BossHpBar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* HpRenderer = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* HpAddRenderer = nullptr; // 커비 랜더링 (이미지)
	
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer();
	ASubBoss* SubBoss = ASubBoss::GetMainSubBoss();

	FVector Move = FVector::Zero;
};

