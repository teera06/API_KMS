#include "Game_Core.h"
#include "Kirby_Player.h"
#include "TitleLevel.h"
#include "Stage1_Level.h"


UGame_Core::UGame_Core()
	: UEngineCore()
{
}

UGame_Core::~UGame_Core()
{
}

// 게임시작
void UGame_Core::BeginPlay() // 
{

	MainWindow.SetWindowScale({ 1080,810 });
	UEngineCore::BeginPlay();
	// "Title Level" + "을 만들다가 에러가 났습니다";

	// 기본 커비 리소스만 여기다가 로드

	SetFrame(60); //-> 프로그래머가 컴퓨터 프레임을 고정시킬수 있다.
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UStage1_Level>("Stage1_Level");
	ChangeLevel("TitleLevel");
	
}

void UGame_Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// 플레이어 움직여야 한다.
}

void UGame_Core::End()
{
	UEngineCore::End();
}