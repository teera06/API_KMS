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

// ���ӽ���
void Game_Core::BeginPlay()
{
	// "Title Level" + "�� ����ٰ� ������ �����ϴ�";

	//CreateLevel<UTitleLevel>("TitleLevel");
	//CreateLevel<UPlayLevel>("PlayLevel");

	//ChangeLevel("PlayLevel");
}

void Game_Core::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void Game_Core::End()
{
}