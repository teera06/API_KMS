#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class ABullet : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ABullet(); // 디폴트 생성자
	~ABullet(); // 디폴트 소멸자

	// delete Function
	ABullet(const ABullet& _Other) = delete; // 디폴트 복사 생성자
	ABullet(ABullet&& _Other) noexcept = delete; 
	ABullet& operator=(const ABullet& _Other) = delete; // 디폴트 대입 연산자
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	UImageRenderer* bulletRenderer = nullptr;
	UCollision* bulletCollision = nullptr;

	float Speed = 500.0f;
	void AniCreate(); // 애니메이션 관리

	void SkillDir(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
};

