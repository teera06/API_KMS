#pragma once
// 상속
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class SubBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	SubBoss(); // 디폴트 생성자
	~SubBoss(); // 디폴트 소멸자

	// delete Function
	SubBoss(const SubBoss& _Other) = delete; // 디폴트 복사 생성자
	SubBoss(SubBoss&& _Other) noexcept = delete; 
	SubBoss& operator=(const SubBoss& _Other) = delete; // 디폴트 대입 연산자
	SubBoss& operator=(SubBoss&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr;

	void CalDir();

	void GroundUp();
};

