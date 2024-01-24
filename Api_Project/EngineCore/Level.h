#pragma once
#include "NameObject.h"
#include <map>
#include <list>

// 전방선언
class AActor;
// 설명 : U는 그냥 엔진 속해있다는 것을 의미.
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

	//  가상함수
	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};


	// 액터 생성 -> 동적할당 및 자료구조에 정리
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
	std::map<int, std::list<AActor*>> AllActor; // 엑터(ex) 플레이어, 몬스터) 관리

	void ActorInit(AActor* _NewActor);

};

