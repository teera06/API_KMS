#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AMonster_Base : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	AMonster_Base(); // 디폴트 생성자
	~AMonster_Base(); // 디폴트 소멸자

	// delete Function
	AMonster_Base(const AMonster_Base& _Other) = delete; // 디폴트 복사 생성자
	AMonster_Base(AMonster_Base&& _Other) noexcept = delete; 
	AMonster_Base& operator=(const AMonster_Base& _Other) = delete; // 디폴트 대입 연산자
	AMonster_Base& operator=(AMonster_Base&& _Other) noexcept = delete;

	void IceState();
protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision=nullptr;

	AKirby_Player* Player = AKirby_Player::GetMainPlayer();

	FVector Dir = FVector::Right;
	void AniCreate();
	
	void BaseMove(float _DeltaTime);

};

