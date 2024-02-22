#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

class AAllStar : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	AAllStar(); // 디폴트 생성자
	~AAllStar(); // 디폴트 소멸자

	// delete Function
	AAllStar(const AAllStar& _Other) = delete; // 디폴트 복사 생성자
	AAllStar(AAllStar&& _Other) noexcept = delete;
	AAllStar& operator=(const AAllStar& _Other) = delete; // 디폴트 대입 연산자
	AAllStar& operator=(AAllStar&& _Other) noexcept = delete;

	
protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	float Speed = 500.0f;
	UImageRenderer* AllStarRenderer = nullptr;
	UCollision* AllStarCollision = nullptr;
};
