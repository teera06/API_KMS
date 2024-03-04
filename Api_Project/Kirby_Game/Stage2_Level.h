#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

class AStage2_Map;
class AKirby_Player;
class AKirby_HpBar;
class AMonster_Base;
class AMonster_Fire;
class AMonster_Sir;

class UStage2_Level :public ULevel
{
public:
	// constrcuter destructer
	UStage2_Level(); // 디폴트 생성자
	~UStage2_Level(); // 디폴트 소멸자

	// delete Function
	UStage2_Level(const UStage2_Level& _Other) = delete; // 디폴트 복사 생성자
	UStage2_Level(UStage2_Level&& _Other) noexcept = delete; 
	UStage2_Level& operator=(const UStage2_Level& _Other) = delete; // 디폴트 대입 연산자
	UStage2_Level& operator=(UStage2_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	AStage2_Map* NewMap = nullptr;
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;

	const int Firesize = 4;
	const int Sirsize = 3;

	AMonster_Base* NewBase=nullptr;
	AMonster_Fire* NewFire[6] = { nullptr,nullptr,nullptr,nullptr, nullptr };
	AMonster_Sir* NewSir[4] = { nullptr ,nullptr,nullptr};
};

