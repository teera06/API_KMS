#pragma once
#include <EngineBase\Transform.h> // Level0
#include "ActorComponent.h"

// 설명 : 자신만의 위치까지 가지고 있어야 하는 컴포넌트
//        나는 액터에게 속해있고 거기 나만의 상대적 위치까지 가지고 있어야 한다.
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


	// Actor 위 랜더의 위치 및 크기 설정
	void SetPosition(const FVector& _Value) // 위치
	{
		Transform.SetPosition(_Value);
	}

	void SetScale(const FVector& _Value) // 크기
	{
		Transform.SetScale(_Value); 
	}

	void SetTransform(const FTransform& _Value) // 위치, 크기 Set
	{
		Transform = _Value;
	}

	FTransform GetTransform() // 위치, 크기 Get
	{
		return Transform;
	}


protected:


private:
	FTransform Transform; // Level0

};

