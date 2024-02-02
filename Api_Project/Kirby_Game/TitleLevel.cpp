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
	// 실행경로가 나와야 한다고 생각합니다.
	UEngineDirectory NewPath; // 현재 파일 경로
	FVector windowscale = GEngine->MainWindow.GetWindowScale();

	// NewPath.Move("ContentsResources");
	NewPath.MoveParent(); // 현재 파일 경로의 상위 폴더로 이동

	NewPath.Move("GameResources"); // 현재 폴더에서 다른 폴더로 이동
	NewPath.Move("Title");


	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
	}

	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // Level 위의 Actor 위치 설정 ;
	
}
