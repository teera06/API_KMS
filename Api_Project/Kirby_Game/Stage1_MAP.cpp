#include "Stage1_MAP.h"
#include "ModeEnum.h"
#include "ActorCommon.h"

AStage1_MAP::AStage1_MAP()
{
}

AStage1_MAP::~AStage1_MAP()
{
}

void AStage1_MAP::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(RenderOrder::Stage1_Map); // 이미지 랜더 생성
	MapColRenderer = CreateImageRenderer(RenderOrder::Stage1_Map); // 이미지 랜더 생성
	MapRenderer->ActiveOff();
}

void AStage1_MAP::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}

void AStage1_MAP::SetMapImage(std::string_view _MapImageName)
{
	MapRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapRenderer->GetImage();
	FVector ImageScale = Image->GetScale();
	MapRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
	
	
}

void AStage1_MAP::SetColMapImage(std::string_view _MapImageName)
{
	MapColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapColRenderer->GetImage();
	ActorCommon::ColMapImage = Image;
	FVector ImageScale = Image->GetScale();
	MapColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void AStage1_MAP::SwitchDebug()
{
	if (true == MapRenderer->IsActive())
	{
		MapRenderer->ActiveOff();
		MapColRenderer->ActiveOn();
	}
	else
	{
		MapRenderer->ActiveOn();
		MapColRenderer->ActiveOff();
	}
}
