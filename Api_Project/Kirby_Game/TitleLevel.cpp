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

	// �̹���, ���� �ε�� ����ǰ� �ѹ� �� ����
	if (false == LoadCheck)
	{
		LoadCheck = true;
		UEngineDirectory NewPath; // ���� ���� ���

		NewPath.MoveToSearchChild("GameResources"); // GameResources ������ ã�� ������ ���� ������ ��� �̵� 
		NewPath.Move("title"); // GameResources ���� title ������ ��� �̵�

		// �̹��� �ε�
		// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // ������ ��ü ���
			// �̱���  GetInst�� ���
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
		}
		// �� �̹����� ������ ���� ��ŭ ����
		UEngineResourcesManager::GetInst().CuttingImage("Mapback.png", 5, 1);
		UEngineResourcesManager::GetInst().CuttingImage("Text.png", 3, 4);


		// ���� �ε�
		std::list<UEngineFile> SoundList = NewPath.AllFile({ ".wav", ".mp3" }, true);

		for (UEngineFile& File : SoundList)
		{
			UEngineSound::Load(File.GetFullPath());
		}
	}
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_RETURN))
	{   
		GEngine->ChangeLevel("Stage1_Level");
	}

	if (true == UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->MainWindow.Off();
	}
}

void UTitleLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	BGMPlayer = UEngineSound::SoundPlay("titleSound.mp3");
	BGMPlayer.SetVolume(0.7f);
	BGMPlayer.Loop();

	SetCameraPos({ 0,50 }); // ī�޶� ��ġ ����

	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // ������â �߰��������� TitleActor ��ġ Set

	GEngine->CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level ����
}

void UTitleLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	BGMPlayer.Off();
	GEngine->DestroyLevel("TitleLevel");
}
