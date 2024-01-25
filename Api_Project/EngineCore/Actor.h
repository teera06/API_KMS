#pragma once
#include <EngineBase\FTransform.h>
#include "TickObject.h"
#include "NameObject.h"

class ULevel;

// ���� : A�� ���� ������Ʈ�� ȭ�鿡 ��ġ�� �����ؾ��Ѵ�.
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

	FVector GetActorLocation() //Actor�� ��ġ Get
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value) // Actor�� ��ġ Set
	{
		Transform.SetPosition(_Value);
	}

	void SetActorScale(FVector _Value) // Actor�� ũ�� Set
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform() // Actor�� ũ�� Get
	{
		return Transform;
	}

	ULevel* GetWorld() // Level(World) Get
	{
		return World;
	}

protected:

private:
	ULevel* World; // Actor�� Level ������ �����δ�.
	FTransform Transform; 

	void SetWorld(ULevel* _Value) // �ش� Actor�� Level Set
	{
		World = _Value;
	}
};

