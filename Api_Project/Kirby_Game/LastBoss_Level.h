#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

class AKirby_Player;
class AKirby_HpBar;

class LastBoss_Level :public ULevel
{
public:
	// constrcuter destructer
	LastBoss_Level(); // 디폴트 생성자
	~LastBoss_Level(); // 디폴트 소멸자

	// delete Function
	LastBoss_Level(const LastBoss_Level& _Other) = delete; // 디폴트 복사 생성자
	LastBoss_Level(LastBoss_Level&& _Other) noexcept = delete; 
	LastBoss_Level& operator=(const LastBoss_Level& _Other) = delete; // 디폴트 대입 연산자
	LastBoss_Level& operator=(LastBoss_Level&& _Other) noexcept = delete;

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

