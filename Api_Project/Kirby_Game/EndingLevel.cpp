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

	time1 -= _DeltaTime;
	time2 -= _DeltaTime;
	time3 -= _DeltaTime;
	time4 -= _DeltaTime;
	if (time1 < 0 && false==text1check)
	{
		text1check = true;
		NewEndActor->Gettext1Renderer()->ActiveOn();
	}

	if (time2 < 0 && false == text2check)
	{
		text2check = true;
		NewEndActor->Gettext1Renderer()->ActiveOff();
		NewEndActor->Gettext2Renderer()->ActiveOn();
	}

	if (time3 < 0)
	{
		NewEndActor->Gettext2Renderer()->ActiveOff();
		NewEndActor->GetKirbyRenderer()->AddPosition(FVector::Right * 200.0f * _DeltaTime);
	}

	if (time4 < 0 && false == check4)
	{
		check4 = true;
		NewEndActor->GetKirbyRenderer()->ActiveOff();
		GEngine->ChangeLevel("TitleLevel");
	}


	if (true == UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}

void UEndingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	BGMPlayer = UEngineSound::SoundPlay("titleSound.mp3");
	BGMPlayer.SetVolume(0.7f);
	BGMPlayer.Loop();
	SetCameraPos({ 0,50 }); // ī�޶� ��ġ ����
	NewEndActor = SpawnActor<AEndActor>();
	NewEndActor->SetActorLocation(windowscale.Half2D()); // ������â �߰��������� TitleActor ��ġ Set
	GEngine->CreateLevel<UTitleLevel>("TitleLevel"); // stage2_Level ���� ���� �̸� �غ�
}

void UEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	BGMPlayer.Off();
	GEngine->DestroyLevel("Ending_Level"); // Level ����
}
