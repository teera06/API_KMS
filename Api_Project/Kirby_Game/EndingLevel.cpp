#include "EndingLevel.h"

#include "TitleLevel.h"
#include "EndActor.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

bool UEndingLevel::LoadCheck = false;

UEndingLevel::UEndingLevel()
{
}

UEndingLevel::~UEndingLevel()
{
}

void UEndingLevel::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == LoadCheck)
	{
		LoadCheck = true;
		UEngineDirectory NewPath; // ���� ���� ���

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("end"); // ���� �̵�
		

		// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
		// png, bmp ���� 
		// true -> ���� ���� �����ȿ� �̹����� ����Լ��� üũ

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // ������ ��ü ���
			// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
		}
	}
	
}

void UEndingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('Q'))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}

void UEndingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,50 }); // ī�޶� ��ġ ����
	SpawnActor<AEndActor>()->SetActorLocation(windowscale.Half2D()); // ������â �߰��������� TitleActor ��ġ Set
	GEngine->CreateLevel<UTitleLevel>("TitleLevel"); // stage2_Level ���� ���� �̸� �غ�
}

void UEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("Ending_Level"); // Level ����
}
