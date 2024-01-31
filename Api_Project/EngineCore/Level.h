#pragma once
#include <EngineBase\NameObject.h>
#include <map>
#include <list>


// 역할 : Actor 생성 및 관리
// 전방선언 : 이러이러한 클래스가 있을거다.
class AActor;
class UEngineCore;
class UImageRenderer;
// 설명 : U는 그냥 엔진 속해있다는 것을 의미.
class ULevel : public UNameObject
{
	friend UEngineCore;
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

	// Actor 생성 ex) 플레이어, 몬스터 등등 
	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType(); // 동적 할당
		ActorInit(NewActor); // Actor가 생성된 Level Set
		AllActor[_Order].push_back(NewActor); // 그려지는 순서에 맞게 Map에 넣어줌
		return NewActor;
	}



protected:

private:
	std::map<int, std::list<AActor*>> AllActor; // Map과 리스트로 Actor 관리

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);

	std::map<int, std::list<UImageRenderer*>> Renderers;
};

