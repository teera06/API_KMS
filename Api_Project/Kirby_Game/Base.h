#pragma once
#include <EngineCore\Actor.h>

class ABase : public AActor
{
public:
	// constrcuter destructer
	ABase(); // ����Ʈ ������
	~ABase(); // ����Ʈ �Ҹ���

	// delete Function
	ABase(const ABase& _Other) = delete; // ����Ʈ ���� ������
	ABase(ABase&& _Other) noexcept = delete; 
	ABase& operator=(const ABase& _Other) = delete; // ����Ʈ ���� ������
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

