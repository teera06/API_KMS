#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

class AIce :public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AIce(); // 디폴트 생성자
	~AIce(); // 디폴트 소멸자

	// delete Function
	AIce(const AIce& _Other) = delete; // 디폴트 복사 생성자
	AIce(AIce&& _Other) noexcept = delete; 
	AIce& operator=(const AIce& _Other) = delete; // 디폴트 대입 연산자
	AIce& operator=(AIce&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* IceRenderer = nullptr;
	UCollision* IceCollision = nullptr;
};

