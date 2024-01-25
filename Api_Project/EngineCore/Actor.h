#pragma once
#include <EngineBase\FTransform.h>
// 같은 레벨2
#include "TickObject.h" // 상속
#include "NameObject.h" // 상속
#include "Level.h" // 전방 선언

class ULevel; // 전방 선언

// 설명 : A가 붙은 오브젝트는 화면에 위치가 존재해야한다.
// Level->SpawnActor를 통해서 만들면
// 레벨이 자연스럽게 자신의 관리하에 두고 언제나 Tick을 실행해준다.
class AActor : public UNameObject, public UTickObject // 상속
{
	friend ULevel; //Level한테는 본인의 private까지 전부 제공

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

	FVector GetActorLocation() // Actor의 위치 Get
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value) // Actor의 위치 Set
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value) //Actor의 위치 변화
	{
		Transform.AddPosition(_Value);
	}

	void SetActorScale(FVector _Value) //Actor의 크기 값 Set
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform() // 위치 크기값 반환
	{
		return Transform;
	}

	ULevel* GetWorld() // 레벨 반환
	{
		return World;
	}

protected:

private:
	ULevel* World; // Actor는 Level위에 그려진다.
	FTransform Transform; // Actor의 위치 크기 

	void SetWorld(ULevel* _Value) // Actor가 존재해야하는 Level을 받는다. 
	{
		World = _Value;
	}
};

