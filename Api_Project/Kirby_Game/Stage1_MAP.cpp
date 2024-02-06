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
	MapColRenderer->SetActive(false);
	//MapRenderer->SetImage("Stage1map.bmp"); // 이미지 Set
	//MapRenderer->SetTransColor({ 255,255, 255, 0 });
	//MapRenderer->SetTransform({ {0,0}, windowScale }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 
	//MapRenderer->SetImageCuttingTransform({ {0,0}, {461,123} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

void AStage1_MAP::Tick(float _DeltaTime)
{
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
		MapRenderer->SetActive(false);
		MapColRenderer->SetActive(true);
	}
	else
	{
		MapRenderer->SetActive(true);
		MapColRenderer->SetActive(false);
	}
}
