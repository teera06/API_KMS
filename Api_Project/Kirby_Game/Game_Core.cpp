#include "Game_Core.h"
#include "Kirby_Player.h"
#include "TitleLevel.h"
#include "Stage1_Level.h"

Game_Core::Game_Core()
	: EngineCore()
{
}

Game_Core::~Game_Core()
{
}

// ���ӽ���
void Game_Core::BeginPlay() // 
{
	// "Title Level" + "�� ����ٰ� ������ �����ϴ�";
	SetFrame(60); //-> ���α׷��Ӱ� ��ǻ�� �������� ������ų�� �ִ�.
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UStage1_Level>("Stage1_Level");

	ChangeLevel("Stage1_Level");
}

void Game_Core::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void Game_Core::End()
{
}