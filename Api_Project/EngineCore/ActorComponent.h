#pragma once
#include "TickObject.h"

// 전방 선언
class AActor;
// 설명 : 액터에게 달린 부가기능이라는 개념만 존재하는 컴포넌트
//        나는 액터에게 속한 기능이다.
class UActorComponent : public UTickObject
{
	friend AActor; // AActor에게 private까지 공개

public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	AActor* GetOwner() // Get
	{
		return Owner;
	}

protected:

private:
	AActor* Owner = nullptr;

	void SetOwner(AActor* _Owner) // Set
	{
		Owner = _Owner;
	}


};

