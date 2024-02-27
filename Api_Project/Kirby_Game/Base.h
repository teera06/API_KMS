#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"


class ABase : public AActor, public UActorCommon
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

	

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* BaseRenderer = nullptr;
	UCollision* BaseCollision = nullptr;

	
	
};

