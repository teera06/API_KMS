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
	MainWindow.SetWindowScale({ 1200, 800}); // ������â ũ�� Set

	UEngineDirectory NewPath; // ���� ���� ���

	NewPath.MoveParent(); // ���� ���� ����� ����(�θ�) ������ �̵�

	// Ŀ���� �⺻ ������ �̹����� ��� ������������ ����ϹǷ� �ھ�� �ε�
	NewPath.Move("GameResources"); // ���� �������� �ٸ� ������ �̵�
	NewPath.Move("kirby_resources"); // ��� �̵�
	NewPath.Move("kirby_Base"); // ��� �̵�


	// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		//std::string FullPath = File.GetFullPath(); // ������ ��ü ���
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath()); // �ε� -> Map(Iamges)
	}
	
	// WindowImage std::vector<UImageInfo> Infos; ���� ���� �̹��� ������, ��ġ ����
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Right.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Left.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Right.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Left.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Right.png", 8, 2);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Left.png", 8, 2);

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