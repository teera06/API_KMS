#include "Stage2_Map.h"

#include "ModeEnum.h" // Enum 모음집

#include "ActorCommon.h" // ActorCommon::ColMapImage = Image; -> 픽셀 충돌할 맵 이미지 설정

AStage2_Map::AStage2_Map()
{
}

AStage2_Map::~AStage2_Map()
{
}

void AStage2_Map::SetMapImage(std::string_view _MapImageName)
{
	MapRenderer->SetImage(_MapImageName); // 이미지 Set
	UWindowImage* Image = MapRenderer->GetImage(); // Set한 이미지 값을 받고
	FVector ImageScale = Image->GetScale(); // 이미지 크기를 저장
	MapRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
	// 이미지의 X축 Y축 절반의 위치에 이미지 크기만 크기만큼 랜더링
}

void AStage2_Map::SetColMapImage(std::string_view _MapImageName)
{
	MapColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapColRenderer->GetImage();
	UActorCommon::ColMapImage = Image; // 픽셀 충돌할 맵 설정
	FVector ImageScale = Image->GetScale();
	MapColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void AStage2_Map::SwitchDebug()
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

void AStage2_Map::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(ERenderOrder::Stage2_Map); // 이미지 랜더 생성
	MapColRenderer = CreateImageRenderer(ERenderOrder::Stage2_Map); // 이미지 랜더 생성
	MapRenderer->ActiveOff();
}

void AStage2_Map::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}
