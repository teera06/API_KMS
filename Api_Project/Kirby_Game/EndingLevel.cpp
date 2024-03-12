#include "EndingLevel.h"

#include "TitleLevel.h"
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
	if (true == UEngineInput::IsDown('Q'))
	{
		GEngine->ChangeLevel("TitleLevel");
	}
}

void UEndingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,50 }); // 카메라 위치 설정
	SpawnActor<AEndActor>()->SetActorLocation(windowscale.Half2D()); // 윈도우창 중간지점으로 TitleActor 위치 Set
	GEngine->CreateLevel<UTitleLevel>("TitleLevel"); // stage2_Level 다음 레벨 미리 준비
}

void UEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("EndingLevelBoss_Level"); // Level 정리
}
