#include "Game_Core.h"

// Level 생성에 필요한 헤더
#include "TitleLevel.h"

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
	MainWindow.SetWindowTitle("Kirby Star"); // 윈도우창 타이틀 Set

	// EngineCore에서 std::map<std::string, ULevel*> AllLevel; map으로 관리
	CreateLevel<UTitleLevel>("TitleLevel"); // 타이틀 Level 생성
	ChangeLevel("TitleLevel"); // 레벨 변경
}

void UGame_Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void UGame_Core::End()
{
	UEngineCore::End();
}