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

// ���ӽ���
void UGame_Core::BeginPlay()  
{
	UEngineCore::BeginPlay();

	MainWindow.SetWindowPosition({ 200,100 }); // ������â�� �ߴ� ��ġ Set
	MainWindow.SetWindowScale({ 1000, 700}); // ������â ũ�� Set

	SetFrame(60); //-> ���α׷��Ӱ� ��ǻ�� �������� ������ų�� �ִ�.

	// EngineCore���� std::map<std::string, ULevel*> AllLevel; map���� ����
	CreateLevel<UTitleLevel>("TitleLevel"); // Ÿ��Ʋ ����
	CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level
	
	ChangeLevel("TitleLevel"); // ���� ����
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