#include "Stage1_MAP.h"

AStage1_MAP::AStage1_MAP()
{
}

AStage1_MAP::~AStage1_MAP()
{
}

void AStage1_MAP::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(-9); // 이미지 랜더 생성
	MapRenderer->SetImage("Stage1map.bmp"); // 이미지 Set
	MapRenderer->SetTransColor({ 255,255, 255, 0 });
	MapRenderer->SetTransform({ {0,0}, windowScale }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 
	MapRenderer->SetImageCuttingTransform({ {0,0}, windowScale.Half2D()}); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

void AStage1_MAP::Tick(float _DeltaTime)
{
}
