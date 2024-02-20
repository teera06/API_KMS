#include "Stage1_Level.h"
#include "Stage1_MAP.h"
#include "Kirby_Player.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"

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

	UEngineResourcesManager::GetInst().CuttingImage("Monster_Right.png", 10, 5);
	UEngineResourcesManager::GetInst().CuttingImage("Monster_Left.png", 10, 5);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Left.png", 5, 2);

	AStage1_MAP* Map = SpawnActor<AStage1_MAP>();
	Map->SetMapImage("stage1_map.png");
	//Map->SetMapImage("to.png");
	Map->SetColMapImage("cor_map.png");
	Map->SwitchDebug();

	SpawnActor<AKirby_Player>()->SetActorLocation({ 500,800 });;

	for (int i = 1; i <= 4; i++)
	{
		AMonster_Base* NewMonster = SpawnActor<AMonster_Base>();
		NewMonster->SetActorLocation({ 800 + i * 100,800 });
	}
	SpawnActor<Apengi_Ice>()->SetActorLocation({ 800 ,800 });
	for (int i = 1; i <= 3; i++)
	{
		SpawnActor<Apengi_Ice>()->SetActorLocation({ 1200+i*200,800 });
	}
}

void UStage1_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
