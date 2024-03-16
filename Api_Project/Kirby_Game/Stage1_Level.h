#pragma once
#include <EnginePlatform\EngineSound.h>
#include <EngineCore\Level.h> // 상속

// 전방 선언 
class AKirby_Player; // 커비
class AKirby_HpBar; // 커비 HP바
class AMonster_Base; // 기본 몬스터
class Apengi_Ice; // 아이스 몬스터
class AMonster_Fire; // 불 몬스터
class AStage1_MAP; // 맵1

class UStage1_Level:public ULevel
{
public:
	// constrcuter destructer
	UStage1_Level(); // 디폴트 생성자
	~UStage1_Level(); // 디폴트 소멸자

	// delete Function
	UStage1_Level(const UStage1_Level& _Other) = delete; // 디폴트 복사 생성자
	UStage1_Level(UStage1_Level&& _Other) noexcept = delete; 
	UStage1_Level& operator=(const UStage1_Level& _Other) = delete; // 디폴트 대입 연산자
	UStage1_Level& operator=(UStage1_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	// 사운드
	UEngineSoundPlayer BGMPlayer;

	// 액터 관리
	AStage1_MAP* NewMap = nullptr;
	AKirby_Player* NewPlayer = nullptr;
	AKirby_HpBar* NewHpBar = nullptr;
	
	AMonster_Base* NewBase[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
	Apengi_Ice* NewIce[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
	AMonster_Fire* NewFire[3] = { nullptr,nullptr,nullptr};

	// 몬스터 수 
	const int Basesize = 4;
	const int Icesize = 4;

	static bool LoadCheck;
};

