#pragma once
#include <EngineBase\Transform.h>
#include "TickObject.h"
#include "NameObject.h"
#include "ImageRenderer.h"
#include "Level.h"

// 전방선언
class ULevel; 
class UActorComponent;
class UImageRenderer; // 이미지 랜더

// 설명 : A가 붙은 오브젝트는 화면에 위치가 존재해야한다.
// Level->SpawnActor를 통해서 만들면
// 레벨이 자연스럽게 자신의 관리하에 두고 언제나 Tick을 실행해준다.
class AActor : public UNameObject, public UTickObject
{
	friend ULevel; // Level이 Actor를 쉽게 관리 하기위해 사용

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	FVector GetActorLocation() // Actor 위치 Get
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value) // Actor 위치 Set
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value) // Actor 위치 이동
	{
		Transform.AddPosition(_Value);
	}

	void SetActorScale(FVector _Value) // Actor 크기 Set
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform() // Actor 위치, 크기 Get
	{
		return Transform;
	}

	ULevel* GetWorld() // Actor가 존재하는 Level Get
	{
		return World;
	}

	UImageRenderer* CreateImageRenderer(int Order = 0); // 이미지 랜더 만들기

protected:

private:
	std::list<UImageRenderer*> Renderers; // list로 이미지 관리

	ULevel* World = nullptr;
	FTransform Transform = FTransform(); // Actor의 위치 크기 관리

	void SetWorld(ULevel* _Value) // Actor가 존재하는 Level Set
	{
		World = _Value;
	}
};

