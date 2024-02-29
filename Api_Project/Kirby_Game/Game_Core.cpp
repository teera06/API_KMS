#include "Game_Core.h"

// Level 생성에 필요한 헤더
#include "TitleLevel.h"
#include "Stage1_Level.h"
#include "Stage2_Level.h"



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

	MainWindow.SetWindowPosition({ positionX,positionY }); // 윈도우창이 뜨는 위치 Set
	MainWindow.SetWindowScale({ windowX, windowY}); // 윈도우창 크기 Set

	//SetFrame(60); //-> 프로그래머가 컴퓨터 프레임을 고정시킬수 있다.

	// EngineCore에서 std::map<std::string, ULevel*> AllLevel; map으로 관리
	CreateLevel<UTitleLevel>("TitleLevel"); // 타이틀 Level 생성
	CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level 생성
	
	ChangeLevel("Stage1_Level"); // 레벨 변경
	//CreateLevel<UStage2_Level>("Stage2_Level"); // stage1_Level 생성
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