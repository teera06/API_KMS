#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

class AAllStar : public AActor, public ActorCommon
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

	
protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	float Speed = 500.0f;
	UImageRenderer* AllStarRenderer = nullptr;
	UCollision* AllStarCollision = nullptr;
};
