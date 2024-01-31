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

// ���ӽ���
void UGame_Core::BeginPlay() // 
{
	// "Title Level" + "�� ����ٰ� ������ �����ϴ�";
	SetFrame(60); //-> ���α׷��Ӱ� ��ǻ�� �������� ������ų�� �ִ�.
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UStage1_Level>("Stage1_Level");
	ChangeLevel("Stage1_Level");
	
}

void UGame_Core::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void UGame_Core::End()
{
}