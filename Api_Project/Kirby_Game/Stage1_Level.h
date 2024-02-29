#pragma once
#include <EngineCore\Level.h> // ���
#include <EnginePlatform\EngineSound.h>

class AKirby_Player;
class AKirby_HpBar;
class AMonster_Base;
class Apengi_Ice;
class AMonster_Fire;
class AStage1_MAP;

class UStage1_Level:public ULevel
{
public:
	// constrcuter destructer
	UStage1_Level(); // ����Ʈ ������
	~UStage1_Level(); // ����Ʈ �Ҹ���

	// delete Function
	UStage1_Level(const UStage1_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage1_Level(UStage1_Level&& _Other) noexcept = delete; 
	UStage1_Level& operator=(const UStage1_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage1_Level& operator=(UStage1_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	UEngineSoundPlayer BGMPlayer;

	AStage1_MAP* NewMap = nullptr;
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;
	
	AMonster_Base* NewBase = nullptr;
	Apengi_Ice* NewIce = nullptr;
	AMonster_Fire* NewFire = nullptr;

	const int Basesize = 4;
	const int Icesize = 3;
	const int Firesize=3;

};

