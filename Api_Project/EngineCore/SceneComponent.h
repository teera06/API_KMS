#pragma once
#include <EngineBase\Transform.h>
#include "ActorComponent.h"

// ���� : �ڽŸ��� ��ġ���� ������ �־�� �ϴ� ������Ʈ
class USceneComponent : public UActorComponent
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	void SetScale(const FVector& _Scale)
	{
		Transform.SetScale(_Scale);
	}

	FTransform GetTransform()
	{
		return Transform;
	}

protected:


private:
	FTransform Transform;

};

