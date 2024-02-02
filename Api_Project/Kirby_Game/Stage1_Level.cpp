#include "Stage1_Level.h"
#include "Stage1_MAP.h"
#include "Kirby_Player.h"
#include "Monster_Base.h"


#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile
#include <EngineCore/EngineCore.h>

UStage1_Level::UStage1_Level()
{
}

UStage1_Level::~UStage1_Level()
{
}

void UStage1_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // 현재 파일 경로
	FVector windowScale = GEngine->MainWindow.GetWindowScale();

	// NewPath.Move("ContentsResources");
	NewPath.MoveParent(); // 현재 파일 경로의 상위 폴더로 이동

	NewPath.Move("GameResources"); // 현재 폴더에서 다른 폴더로 이동
	NewPath.Move("Stage1"); // 
	
	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
	}
	SpawnActor<AStage1_MAP>()->SetActorLocation(windowScale.Half2D());
	SpawnActor<AKirby_Player>()->SetActorLocation({140,530});


	// SpawnActor<Player>();

	// 할일은 
	// 플레이어
	// 배경
	// 몬스터
	// 등등등을 코드로 여기서 다 만들어야 한다.
}
