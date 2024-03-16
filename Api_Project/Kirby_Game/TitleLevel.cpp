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

	// 이미지, 사운드 로드는 실행되고 한번 만 실행
	if (false == LoadCheck)
	{
		LoadCheck = true;
		UEngineDirectory NewPath; // 현재 파일 경로

		NewPath.MoveToSearchChild("GameResources"); // GameResources 폴더를 찾을 때까지 상위 폴더로 경로 이동 
		NewPath.Move("title"); // GameResources 안의 title 폴더로 경로 이동

		// 이미지 로드
		// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
			// 싱글톤  GetInst를 사용
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
		}
		// 한 이미지를 정해진 간격 만큼 컷팅
		UEngineResourcesManager::GetInst().CuttingImage("Mapback.png", 5, 1);
		UEngineResourcesManager::GetInst().CuttingImage("Text.png", 3, 4);


		// 사운드 로드
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

	SetCameraPos({ 0,50 }); // 카메라 위치 설정

	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // 윈도우창 중간지점으로 TitleActor 위치 Set

	GEngine->CreateLevel<UStage1_Level>("Stage1_Level"); // stage1_Level 생성
}

void UTitleLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	BGMPlayer.Off();
	GEngine->DestroyLevel("TitleLevel");
}
