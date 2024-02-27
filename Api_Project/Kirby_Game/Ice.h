#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

class AIce :public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AIce(); // ����Ʈ ������
	~AIce(); // ����Ʈ �Ҹ���

	// delete Function
	AIce(const AIce& _Other) = delete; // ����Ʈ ���� ������
	AIce(AIce&& _Other) noexcept = delete; 
	AIce& operator=(const AIce& _Other) = delete; // ����Ʈ ���� ������
	AIce& operator=(AIce&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* IceRenderer = nullptr;
	UCollision* IceCollision = nullptr;
};

