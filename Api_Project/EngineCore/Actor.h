#pragma once
#include <EngineBase\Transform.h>
#include "TickObject.h"
#include "NameObject.h"
#include "ImageRenderer.h"
#include "Level.h"

// ���漱��
class ULevel; 
class UActorComponent;
class UImageRenderer; // �̹��� ����

// ���� : A�� ���� ������Ʈ�� ȭ�鿡 ��ġ�� �����ؾ��Ѵ�.
// Level->SpawnActor�� ���ؼ� �����
// ������ �ڿ������� �ڽ��� �����Ͽ� �ΰ� ������ Tick�� �������ش�.
class AActor : public UNameObject, public UTickObject
{
	friend ULevel; // Level�� Actor�� ���� ���� �ϱ����� ���

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	FVector GetActorLocation() // Actor ��ġ Get
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value) // Actor ��ġ Set
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value) // Actor ��ġ �̵�
	{
		Transform.AddPosition(_Value);
	}

	void SetActorScale(FVector _Value) // Actor ũ�� Set
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform() // Actor ��ġ, ũ�� Get
	{
		return Transform;
	}

	ULevel* GetWorld() // Actor�� �����ϴ� Level Get
	{
		return World;
	}

	UImageRenderer* CreateImageRenderer(int Order = 0); // �̹��� ���� �����

protected:

private:
	std::list<UImageRenderer*> Renderers; // list�� �̹��� ����

	ULevel* World = nullptr;
	FTransform Transform = FTransform(); // Actor�� ��ġ ũ�� ����

	void SetWorld(ULevel* _Value) // Actor�� �����ϴ� Level Set
	{
		World = _Value;
	}
};

