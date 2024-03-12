#include "EndingLevel.h"
#include "EndActor.h"


UEndingLevel::UEndingLevel()
{
}

UEndingLevel::~UEndingLevel()
{
}

void UEndingLevel::BeginPlay()
{
	ULevel::BeginPlay();
	
}

void UEndingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UEndingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SpawnActor<AEndActor>()->SetActorLocation(windowscale.Half2D()); // 윈도우창 중간지점으로 TitleActor 위치 Set
}

void UEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	//GEngine->DestroyLevel("EndingLevelBoss_Level"); // Level 정리
}
