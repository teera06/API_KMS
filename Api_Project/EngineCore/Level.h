#pragma once
#include "NameObject.h"
#include <map>
#include <list>

// 전방 선언
class AActor; // 엑터 관리
class EngineCore; // 엔진 사용
class UImageRenderer; // 이미지 관리 
// 설명 : U는 그냥 엔진 속해있다는 것을 의미.
class ULevel : public UNameObject
{
	friend EngineCore;
	friend UImageRenderer;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

	// Actor 관리
	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}



protected:

private:
	std::map<int, std::list<AActor*>> AllActor; // 액터 관리

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime); // 
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);

	std::map<int, std::list<UImageRenderer*>> Renderers; // 이미지 관리
};

