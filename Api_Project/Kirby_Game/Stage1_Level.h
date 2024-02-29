#pragma once
#include <EngineCore\Level.h> // ���
#include <EnginePlatform\EngineSound.h>

class AKirby_Player;
class AKirby_HpBar;
class AMonster_Base;
class Apengi_Ice;
class AMonster_Fire;

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
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;
	
	std::vector<AMonster_Base*> NewBaseMonster;
	AMonster_Base* NewBase = nullptr;

	std::vector<Apengi_Ice*> NewIceMonster;
	Apengi_Ice* NewIce = nullptr;

	std::vector<AMonster_Fire*> NewFireMonster;
	AMonster_Fire* NewFire = nullptr;
};

