#include "Stage1_Level.h"
#include "Stage1_MAP.h"
#include "Kirby_Player.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Kirby_HpBar.h"

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

	//UEngineResourcesManager::GetInst().CuttingImage("Monster_Right.png", 10, 5);
	//UEngineResourcesManager::GetInst().CuttingImage("Monster_Left.png", 10, 5);
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Right.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Left.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Right.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Left.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Ice_Right.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("Ice_Left.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Right.png", 8, 2);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Left.png", 8, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Dee_Left.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Dee_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Left.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("changeHUD.png", 5, 2);

	AStage1_MAP* Map = SpawnActor<AStage1_MAP>();
	Map->SetMapImage("stage1_map.png");
	Map->SetColMapImage("cor_map.png");
	Map->SwitchDebug();

	{
		SpawnActor<AKirby_Player>()->SetActorLocation({ 500,800 });
		SpawnActor<AKirby_HpBar>()->SetActorLocation({180,1050});

		SpawnActor<AMonster_Base>()->SetActorLocation({ 800,700 });
		SpawnActor<AMonster_Base>()->SetActorLocation({ 1400,700 });
		SpawnActor<AMonster_Base>()->SetActorLocation({ 1900,600 });
		
		SpawnActor<Apengi_Ice>()->SetActorLocation({ 1100,800 });
		SpawnActor<Apengi_Ice>()->SetActorLocation({ 1700,800 });
		//SpawnActor<Apengi_Ice>()->SetActorLocation({ 1100,600 });
	}
}

void UStage1_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
