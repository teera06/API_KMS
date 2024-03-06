#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AHammer : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AHammer(); // 디폴트 생성자
	~AHammer(); // 디폴트 소멸자

	// delete Function
	AHammer(const AHammer& _Other) = delete; // 디폴트 복사 생성자
	AHammer(AHammer&& _Other) noexcept = delete; 
	AHammer& operator=(const AHammer& _Other) = delete; // 디폴트 대입 연산자
	AHammer& operator=(AHammer&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	// 몬스터 랜더링, 콜리전
	UImageRenderer* Renderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* Collision = nullptr;

	void GroundUp();
};

