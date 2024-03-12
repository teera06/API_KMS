#include "TitleLevel.h"
#include "TitleActor.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

#include "Stage1_Level.h"


bool UTitleLevel::LoadCheck = false;

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == LoadCheck)
	{
		LoadCheck = true;
		UEngineDirectory NewPath; // ���� ���� ���
		FVector windowscale = GEngine->MainWindow.GetWindowScale(); // ������â ũ�� Get

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("title");

		// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // ������ ��ü ���
			// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
		}
		UEngineResourcesManager::GetInst().CuttingImage("Mapback.png", 5, 1);
		UEngineResourcesManager::GetInst().CuttingImage("Text.png", 3, 4);
	}
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_RETURN))
	{   
		GEngine->ChangeLevel("Stage1_Level");
	}
}

void UTitleLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,50 }); // ī�޶� ��ġ ����

	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // ������â �߰��������� TitleActor ��ġ Set

	GEngine->CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level ����
}

void UTitleLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("TitleLevel");
}
