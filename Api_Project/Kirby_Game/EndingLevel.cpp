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
		UEngineDirectory NewPath; // 현재 파일 경로

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("end"); // 폴더 이동
		

		// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
		// png, bmp 파일 
		// true -> 폴더 안의 폴더안에 이미지도 재귀함수로 체크

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
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
	SetCameraPos({ 0,50 }); // 카메라 위치 설정
	NewEndActor = SpawnActor<AEndActor>();
	NewEndActor->SetActorLocation(windowscale.Half2D()); // 윈도우창 중간지점으로 TitleActor 위치 Set
	GEngine->CreateLevel<UTitleLevel>("TitleLevel"); // stage2_Level 다음 레벨 미리 준비
}

void UEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	BGMPlayer.Off();
	GEngine->DestroyLevel("Ending_Level"); // Level 정리
}
