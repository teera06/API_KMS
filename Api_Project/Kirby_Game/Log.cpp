#include "Log.h"
#include <EnginePlatform\EngineInput.h> // 마우스 왼쪽 버튼 누를 경우 레벨 체인지
#include "ModeEnum.h"

ALog::ALog()
{
}

ALog::~ALog()
{
}

void ALog::BeginPlay()
{
	AActor::BeginPlay();

	LogRenderer = CreateImageRenderer(ERenderOrder::Log); // 이미지 랜더 생성
	LogRenderer->SetImage("Log.png"); // 이미지 Set
	LogRenderer->SetTransform({ {0,0}, {windowScale} }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 

	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

void ALog::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		Destroy(0.0f);
	}
}
