#pragma once
// 상속
#include <EngineCore/Actor.h>

#include "ModeEnum.h"
#include "ActorCommon.h"

#include "Kirby_Player.h"
#include "SubBoss.h"

class ABossHpBar : public AActor, public UActorCommon // ActorCommon(중력)
{
public:
	// constrcuter destructer
	ABossHpBar(); // 디폴트 생성자
	~ABossHpBar(); // 디폴트 소멸자

	// delete Function
	ABossHpBar(const ABossHpBar& _Other) = delete; // 디폴트 복사 생성자
	ABossHpBar(ABossHpBar&& _Other) noexcept = delete; 
	ABossHpBar& operator=(const ABossHpBar& _Other) = delete; // 디폴트 대입 연산자
	ABossHpBar& operator=(ABossHpBar&& _Other) noexcept = delete;

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

