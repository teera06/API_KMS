#include "Stage2_Level.h"


#include "Stage2_Map.h"
#include "Kirby_Player.h" 
// 리소스 (이미지, 사운드) 로드하기 위해 필요한 헤더
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage2_Level::UStage2_Level()
{
}

UStage2_Level::~UStage2_Level()
{
}

void UStage2_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // 현재 파일 경로

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("Stage"); // 폴더 이동
	NewPath.Move("stage2");
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

	SetCameraPos({ 0,550 }); // 카메라 위치 설정

	// 맵 생성
	AStage2_Map* Map = SpawnActor<AStage2_Map>();
	Map->SetMapImage("stage2_map.png");
	//Map->SetMapImage("stage2_map.png");
	Map->SetColMapImage("cor2_map.png");
	Map->SwitchDebug();

	// 커비와 커비 상태창 Actor 생성
	SpawnActor<AKirby_Player>()->SetActorLocation({ 500,1000 });
	//SpawnActor<AKirby_HpBar>();
}

void UStage2_Level::Tick(float _DeltaTime)
{

}
