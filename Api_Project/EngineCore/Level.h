#pragma once
#include "NameObject.h"
#include <map>
#include <list>

// ���漱��
class AActor;
// ���� : U�� �׳� ���� �����ִٴ� ���� �ǹ�.
class ULevel : public UNameObject
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	//  �����Լ�
	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};


	// ���� ���� -> �����Ҵ� �� �ڷᱸ���� ����
	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

	void ActorTick(float _DeltaTime);

protected:

private:
	std::map<int, std::list<AActor*>> AllActor; // ����(ex) �÷��̾�, ����) ����

	void ActorInit(AActor* _NewActor);

};

