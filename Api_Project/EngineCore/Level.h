#pragma once
#include <EngineBase\NameObject.h>
#include <map>
#include <list>


// ���� : Actor ���� �� ����
// ���漱�� : �̷��̷��� Ŭ������ �����Ŵ�.
class AActor;
class UEngineCore;
class UImageRenderer;
// ���� : U�� �׳� ���� �����ִٴ� ���� �ǹ�.
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

	// Actor ���� ex) �÷��̾�, ���� ��� 
	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType(); // ���� �Ҵ�
		ActorInit(NewActor); // Actor�� ������ Level Set
		AllActor[_Order].push_back(NewActor); // �׷����� ������ �°� Map�� �־���
		return NewActor;
	}



protected:

private:
	std::map<int, std::list<AActor*>> AllActor; // Map�� ����Ʈ�� Actor ����

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);

	std::map<int, std::list<UImageRenderer*>> Renderers;
};

