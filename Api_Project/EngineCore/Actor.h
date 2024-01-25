#pragma once
#include <EngineBase\FTransform.h>
#include "TickObject.h"
#include "NameObject.h"

class ULevel;

// 설명 : A가 붙은 오브젝트는 화면에 위치가 존재해야한다.
class AActor : public UNameObject, public UTickObject
{
	friend ULevel;

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	//----------------------------------------------------

	FVector GetActorLocation() //Actor의 위치 Get
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value) // Actor의 위치 Set
	{
		Transform.SetPosition(_Value);
	}

	void SetActorScale(FVector _Value) // Actor의 크기 Set
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform() // Actor의 크기 Get
	{
		return Transform;
	}

	ULevel* GetWorld() // Level(World) Get
	{
		return World;
	}

protected:

private:
	ULevel* World; // Actor는 Level 위에서 움직인다.
	FTransform Transform; 

	void SetWorld(ULevel* _Value) // 해당 Actor의 Level Set
	{
		World = _Value;
	}
};

