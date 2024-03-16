#pragma once

// Level1
#include <EnginePlatform\EngineSound.h>
// Level2
#include <EngineCore/EngineCore.h> // GEngine -> 윈도우 창 크기 확인
#include <EngineCore/Level.h> // 레벨 상속

class UTitleLevel : public ULevel
{
public:
	// constrcuter destructer
	UTitleLevel(); // 디폴트 생성자
	~UTitleLevel(); // 디폴트 소멸자

	// delete Function
	UTitleLevel(const UTitleLevel& _Other) = delete; // 디폴트 복사 생성자
	UTitleLevel(UTitleLevel&& _Other) noexcept = delete; 
	UTitleLevel& operator=(const UTitleLevel& _Other) = delete; // 디폴트 대입 연산자
	UTitleLevel& operator=(UTitleLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel)override; // 레벨이 시작할 때
	void LevelEnd(ULevel* _NextLevel) override; // 레벨이 종료될 때
private:
	UEngineSoundPlayer BGMPlayer; // 사운드 재생
	FVector windowscale = GEngine->MainWindow.GetWindowScale(); // 윈도우창 크기 Get

	static bool LoadCheck; // 이미지, 사운드 최초 로드 확인 용 bool
};

