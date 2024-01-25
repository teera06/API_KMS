#pragma once
#include <EngineBase\FTransform.h>
// ���� ����2
#include "TickObject.h" // ���
#include "NameObject.h" // ���
#include "Level.h" // ���� ����

class ULevel; // ���� ����

// ���� : A�� ���� ������Ʈ�� ȭ�鿡 ��ġ�� �����ؾ��Ѵ�.
// Level->SpawnActor�� ���ؼ� �����
// ������ �ڿ������� �ڽ��� �����Ͽ� �ΰ� ������ Tick�� �������ش�.
class AActor : public UNameObject, public UTickObject // ���
{
	friend ULevel; //Level���״� ������ private���� ���� ����

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

	FVector GetActorLocation() // Actor�� ��ġ Get
	{
		return Transform.GetPosition();
	}

	void SetActorLocation(FVector _Value) // Actor�� ��ġ Set
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value) //Actor�� ��ġ ��ȭ
	{
		Transform.AddPosition(_Value);
	}

	void SetActorScale(FVector _Value) //Actor�� ũ�� �� Set
	{
		Transform.SetScale(_Value);
	}

	FTransform GetTransform() // ��ġ ũ�Ⱚ ��ȯ
	{
		return Transform;
	}

	ULevel* GetWorld() // ���� ��ȯ
	{
		return World;
	}

protected:

private:
	ULevel* World; // Actor�� Level���� �׷�����.
	FTransform Transform; // Actor�� ��ġ ũ�� 

	void SetWorld(ULevel* _Value) // Actor�� �����ؾ��ϴ� Level�� �޴´�. 
	{
		World = _Value;
	}
};

