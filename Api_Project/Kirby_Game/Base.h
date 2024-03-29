#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"


class ABase : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ABase(); // 디폴트 생성자
	~ABase(); // 디폴트 소멸자

	// delete Function
	ABase(const ABase& _Other) = delete; // 디폴트 복사 생성자
	ABase(ABase&& _Other) noexcept = delete; 
	ABase& operator=(const ABase& _Other) = delete; // 디폴트 대입 연산자
	ABase& operator=(ABase&& _Other) noexcept = delete;

	

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* BaseRenderer = nullptr;
	UCollision* BaseCollision = nullptr;

	float Power = 600.0f;
	void Collisiongather(float _DeltaTime);
	
};

