#pragma once
#include <EngineCore\Actor.h>

class AFire : public AActor
{
public:
	// constrcuter destructer
	AFire(); // 디폴트 생성자
	~AFire(); // 디폴트 소멸자

	// delete Function
	AFire(const AFire& _Other) = delete; // 디폴트 복사 생성자
	AFire(AFire&& _Other) noexcept = delete; 
	AFire& operator=(const AFire& _Other) = delete; // 디폴트 대입 연산자
	AFire& operator=(AFire&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
};

