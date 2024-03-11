#pragma once
#include <EngineCore\Level.h> // ���
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
	UStage3_Level(); // ����Ʈ ������
	~UStage3_Level(); // ����Ʈ �Ҹ���

	// delete Function
	UStage3_Level(const UStage3_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage3_Level(UStage3_Level&& _Other) noexcept = delete; 
	UStage3_Level& operator=(const UStage3_Level& _Other) = delete; // ����Ʈ ���� ������
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

