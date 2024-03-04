#include "Stage2_Level.h"


#include "Stage2_Map.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"
#include "Monster_Base.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"

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

	// 이미지 컷팅 -> 커비 관련 이미지
	UEngineResourcesManager::GetInst().CuttingImage("Sir_Right.png", 10, 10);
	UEngineResourcesManager::GetInst().CuttingImage("Sir_Left.png", 10, 10);
	UEngineResourcesManager::GetInst().CuttingImage("SirMonster_Right.png", 5, 5);
	UEngineResourcesManager::GetInst().CuttingImage("SirMonster_Left.png", 5, 5);
}

void UStage2_Level::Tick(float _DeltaTime)
{

}

void UStage2_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,550 }); // 카메라 위치 설정

	// 맵 생성
	NewMap = SpawnActor<AStage2_Map>();
	//NewMap->SetMapImage("stage2_map.png");
	NewMap->SetMapImage("stage2_map.png");
	NewMap->SetColMapImage("cor2_map.png");
	NewMap->SwitchDebug();

	// 커비와 커비 상태창 Actor 생성
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 500,1200 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	for (int i = 0; i < 2; i++)
	{
		NewBase[i] = SpawnActor<AMonster_Base>();
		NewBase[i]->SetActorLocation({ 800 + i * 1000,1000 });
	}

	NewBase[2] = SpawnActor<AMonster_Base>();
	NewBase[2]->SetActorLocation({ 2800,1000 });

	NewBase[3] = SpawnActor<AMonster_Base>();
	NewBase[3]->SetActorLocation({ 5000,1000 });


	for (int i = 0; i < Firesize; i++)
	{
		NewFire[i] = SpawnActor<AMonster_Fire>();
		NewFire[i]->SetActorLocation({ 1000 + i * 1000,600 });
	}

	NewSir= SpawnActor<AMonster_Sir>();
	NewSir->SetActorLocation({1000,1000 });
}

void UStage2_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("Stage2_Level");
}
