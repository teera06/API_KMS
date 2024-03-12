#include "EndActor.h"
#include <EnginePlatform\EngineInput.h> // 마우스 왼쪽 버튼 누를 경우 레벨 체인지
#include "ModeEnum.h"
AEndActor::AEndActor()
{
}

AEndActor::~AEndActor()
{
}

void AEndActor::BeginPlay()
{
	AActor::BeginPlay();

	EndRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // 이미지 랜더 생성
	EndRenderer->SetImage("Mapback.png"); // 이미지 Set
	EndRenderer->SetTransform({ {0,0}, {1900,1100} }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 

	//LogRenderer = CreateImageRenderer(ERenderOrder::Log); // 이미지 랜더 생성
	//LogRenderer->SetImage("Log.png"); // 이미지 Set
	//LogRenderer->SetTransform({ { 0,0 }, windowScale });
	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드

	EndRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true); // 오른쪽 서 있기
	EndRenderer->ChangeAnimation("Mapback");
}

void AEndActor::Tick(float _DeltaTime)
{
}
