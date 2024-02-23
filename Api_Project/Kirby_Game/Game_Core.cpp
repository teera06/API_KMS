#include "Game_Core.h"
#include "Kirby_Player.h"
#include "TitleLevel.h"
#include "Stage1_Level.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UGame_Core::UGame_Core()
	: UEngineCore()
{
}

UGame_Core::~UGame_Core()
{
}

// 게임시작
void UGame_Core::BeginPlay()  
{
	UEngineCore::BeginPlay();

	MainWindow.SetWindowPosition({ 200,100 }); // 윈도우창이 뜨는 위치 Set
	MainWindow.SetWindowScale({ 1000, 700}); // 윈도우창 크기 Set

	SetFrame(60); //-> 프로그래머가 컴퓨터 프레임을 고정시킬수 있다.

	// EngineCore에서 std::map<std::string, ULevel*> AllLevel; map으로 관리
	CreateLevel<UTitleLevel>("TitleLevel"); // 타이틀 레벨
	CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level
	
	ChangeLevel("TitleLevel"); // 레벨 변경
}

void UGame_Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// 플레이어 움직여야 한다.
	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void UGame_Core::End()
{
	UEngineCore::End();
}