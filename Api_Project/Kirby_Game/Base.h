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
	FVector Dir = FVector::Zero;
	FVector test = { 50.0f,0.0f};
};

