#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h> // 마우스 왼쪽 버튼 누를 경우 레벨 체인지
#include "ModeEnum.h"

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
	Destroy(0.0f);
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();
	
	TitleRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // 이미지 랜더 생성
	TitleRenderer->SetImage("Log.bmp"); // 이미지 Set
	TitleRenderer->SetTransColor({ 255,255,255,0 });
	TitleRenderer->SetTransform({ {0,0}, windowScale }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 
	
	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		Destroy(0.0f);
	}
}
