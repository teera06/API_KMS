#include "TitleLevel.h"
#include "TitleActor.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

#include <EngineCore/EngineCore.h>

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // 현재 파일 경로
	FVector windowscale = GEngine->MainWindow.GetWindowScale(); // 윈도우창 크기 Get

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("title");

	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true); 

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
	}
	UEngineResourcesManager::GetInst().CuttingImage("Mapback.png", 5, 1);
	
	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // 윈도우창 중간지점으로 TitleActor 위치 Set
	
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('Q'))
	{   
		GEngine->ChangeLevel("Stage1_Level");
	}
}
