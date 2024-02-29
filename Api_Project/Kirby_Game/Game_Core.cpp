#include "Game_Core.h"

// Level ������ �ʿ��� ���
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

// ���ӽ���
void UGame_Core::BeginPlay()  
{
	UEngineCore::BeginPlay();

	MainWindow.SetWindowPosition({ positionX,positionY }); // ������â�� �ߴ� ��ġ Set
	MainWindow.SetWindowScale({ windowX, windowY}); // ������â ũ�� Set

	//SetFrame(60); //-> ���α׷��Ӱ� ��ǻ�� �������� ������ų�� �ִ�.

	// EngineCore���� std::map<std::string, ULevel*> AllLevel; map���� ����
	CreateLevel<UTitleLevel>("TitleLevel"); // Ÿ��Ʋ Level ����
	CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level ����
	
	ChangeLevel("Stage1_Level"); // ���� ����
	//CreateLevel<UStage2_Level>("Stage2_Level"); // stage1_Level ����
}

void UGame_Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// �÷��̾� �������� �Ѵ�.
	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void UGame_Core::End()
{
	UEngineCore::End();
}