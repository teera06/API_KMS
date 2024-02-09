#pragma once
#include <EngineCore\Actor.h>

class AAllStar : public AActor
{
public:
	// constrcuter destructer
	AAllStar(); // ����Ʈ ������
	~AAllStar(); // ����Ʈ �Ҹ���

	// delete Function
	AAllStar(const AAllStar& _Other) = delete; // ����Ʈ ���� ������
	AAllStar(AAllStar&& _Other) noexcept = delete;
	AAllStar& operator=(const AAllStar& _Other) = delete; // ����Ʈ ���� ������
	AAllStar& operator=(AAllStar&& _Other) noexcept = delete;

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
	UImageRenderer* AllStarRenderer = nullptr;
};
