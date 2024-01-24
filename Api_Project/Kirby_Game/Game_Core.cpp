#include "Game_Core.h"
//#include "Player.h"
//#include "TitleLevel.h"
//#include "PlayLevel.h"

Game_Core::Game_Core()
	: EngineCore()
{
}

Game_Core::~Game_Core()
{
}

// 게임시작
void Game_Core::BeginPlay()
{
	// "Title Level" + "을 만들다가 에러가 났습니다";

	//CreateLevel<UTitleLevel>("TitleLevel");
	//CreateLevel<UPlayLevel>("PlayLevel");

	//ChangeLevel("PlayLevel");
}

void Game_Core::Tick(float _DeltaTime)
{
	// 플레이어 움직여야 한다.
}

void Game_Core::End()
{
}