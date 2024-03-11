#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

class AIceBox : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AIceBox(); // 디폴트 생성자
	~AIceBox(); // 디폴트 소멸자

	// delete Function
	AIceBox(const AIceBox& _Other) = delete; // 디폴트 복사 생성자
	AIceBox(AIceBox&& _Other) noexcept = delete; 
	AIceBox& operator=(const AIceBox& _Other) = delete; // 디폴트 대입 연산자
	AIceBox& operator=(AIceBox&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	// 몬스터 랜더링, 콜리전
	UImageRenderer* Renderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* Collision = nullptr;

	void GroundUp();
};

