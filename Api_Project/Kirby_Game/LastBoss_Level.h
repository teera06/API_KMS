#pragma once
#include <EngineCore\Level.h> // ���
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
	ULastBoss_Level(); // ����Ʈ ������
	~ULastBoss_Level(); // ����Ʈ �Ҹ���

	// delete Function
	ULastBoss_Level(const ULastBoss_Level& _Other) = delete; // ����Ʈ ���� ������
	ULastBoss_Level(ULastBoss_Level&& _Other) noexcept = delete; 
	ULastBoss_Level& operator=(const ULastBoss_Level& _Other) = delete; // ����Ʈ ���� ������
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

