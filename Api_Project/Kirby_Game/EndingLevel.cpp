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
	SetCameraPos({ 0,50 }); // ī�޶� ��ġ ����
	SpawnActor<AEndActor>()->SetActorLocation(windowscale.Half2D()); // ������â �߰��������� TitleActor ��ġ Set
}

void UEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	//GEngine->DestroyLevel("EndingLevelBoss_Level"); // Level ����
}
