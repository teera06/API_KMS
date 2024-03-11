#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

class AStage3_Map;
class AKirby_Player;
class AKirby_HpBar;
class AMonster_Sir;
class Apengi_Ice;
class AIceBox;

class UStage3_Level :public ULevel
{
public:
	// constrcuter destructer
	UStage3_Level(); // 디폴트 생성자
	~UStage3_Level(); // 디폴트 소멸자

	// delete Function
	UStage3_Level(const UStage3_Level& _Other) = delete; // 디폴트 복사 생성자
	UStage3_Level(UStage3_Level&& _Other) noexcept = delete; 
	UStage3_Level& operator=(const UStage3_Level& _Other) = delete; // 디폴트 대입 연산자
	UStage3_Level& operator=(UStage3_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	UEngineSoundPlayer BGMPlayer;

	AStage3_Map* NewMap = nullptr;
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;

	AIceBox* NewIceBox[3] = { nullptr,nullptr,nullptr };
};

