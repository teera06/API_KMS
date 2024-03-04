#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

//class AStage2_Map;
class AKirby_Player;
class AKirby_HpBar;
class AMonster_Sir;
class Apengi_Ice;

class Stage3_Level :public ULevel
{
public:
	// constrcuter destructer
	Stage3_Level(); // 디폴트 생성자
	~Stage3_Level(); // 디폴트 소멸자

	// delete Function
	Stage3_Level(const Stage3_Level& _Other) = delete; // 디폴트 복사 생성자
	Stage3_Level(Stage3_Level&& _Other) noexcept = delete; 
	Stage3_Level& operator=(const Stage3_Level& _Other) = delete; // 디폴트 대입 연산자
	Stage3_Level& operator=(Stage3_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	UEngineSoundPlayer BGMPlayer;

	//AStage1_MAP* NewMap = nullptr;
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;
};

