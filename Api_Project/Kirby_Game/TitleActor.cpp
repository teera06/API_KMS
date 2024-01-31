#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h> // 마우스 왼쪽 버튼 누를 경우 레벨 체인지
#include <EngineCore/EngineCore.h> // Level change에 사용

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();
	
	TitleRenderer = CreateImageRenderer(0); // 이미지 랜더 생성
	TitleRenderer->SetImage("test.png"); // 이미지 Set
	SetActorLocation({ 500, 500 }); // Level 위의 Actor 위치 설정 
	TitleRenderer->SetTransform({ {0,0}, {500, 500} }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 
	TitleRenderer->SetImageCuttingTransform({ {0,0}, {649, 311} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == EngineInput::IsDown(VK_LBUTTON))
	{
		GEngine->ChangeLevel("Stage1_Level");
		Destroy(0.0f);
	}
}
