#pragma once
#include <EngineBase\Transform.h>
#include "ActorComponent.h"

// 설명 : 자신만의 위치까지 가지고 있어야 하는 컴포넌트
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

