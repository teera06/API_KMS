#pragma once
#include <EngineCore\Actor.h>

class ABase : public AActor
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

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* BaseRenderer = nullptr;
	UCollision* BaseCollision = nullptr;

	FVector Dir = FVector::Zero;
	int speed = 5;
	
};

