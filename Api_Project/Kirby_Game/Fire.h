#pragma once
#include <EngineCore\Actor.h>

class AFire : public AActor
{
public:
	// constrcuter destructer
	AFire(); // ����Ʈ ������
	~AFire(); // ����Ʈ �Ҹ���

	// delete Function
	AFire(const AFire& _Other) = delete; // ����Ʈ ���� ������
	AFire(AFire&& _Other) noexcept = delete; 
	AFire& operator=(const AFire& _Other) = delete; // ����Ʈ ���� ������
	AFire& operator=(AFire&& _Other) noexcept = delete;

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

	int GetKirbyFireAtt()
	{
		return Att;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	FVector Dir = FVector::Zero;
	float Speed = 300.0f;
	int Att = 50;
};

