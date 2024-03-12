#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

class ALast_Map;
class AKirby_Player;
class AKirby_HpBar;
class AMainBoss;
class ABossHpBar;

class ULastBoss_Level :public ULevel
{
public:
	// constrcuter destructer
	ULastBoss_Level(); // 디폴트 생성자
	~ULastBoss_Level(); // 디폴트 소멸자

	// delete Function
	ULastBoss_Level(const ULastBoss_Level& _Other) = delete; // 디폴트 복사 생성자
	ULastBoss_Level(ULastBoss_Level&& _Other) noexcept = delete; 
	ULastBoss_Level& operator=(const ULastBoss_Level& _Other) = delete; // 디폴트 대입 연산자
	ULastBoss_Level& operator=(ULastBoss_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	UEngineSoundPlayer BGMPlayer;

	ALast_Map* NewMap = nullptr;
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;

	AMainBoss* NewMainBoss = nullptr;
	ABossHpBar* NewBossHpBar = nullptr;

	bool EventCheck = false;
	bool AniEnd = false;
	bool LevelChange = false;

	static bool LoadCheck;
};

