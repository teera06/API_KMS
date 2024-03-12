#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h> // 마우스 왼쪽 버튼 누를 경우 레벨 체인지
#include "ModeEnum.h"

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();

	TitleRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // 이미지 랜더 생성
	TitleRenderer->SetImage("Mapback.png"); // 이미지 Set
	TitleRenderer->SetTransform({ {0,0}, {1900,1100} }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 

	LogRenderer = CreateImageRenderer(ERenderOrder::Log); // 이미지 랜더 생성
	LogRenderer->SetImage("Log.png"); // 이미지 Set
	LogRenderer->SetTransform({ { 0,50 }, windowScale });

	StartRenderer = CreateImageRenderer(ERenderOrder::Log); // 이미지 랜더 생성
	StartRenderer->SetImage("Text.png"); // 이미지 Set
	StartRenderer->SetTransform({ { 200,250 }, {64*10, 64*8} });
	
	TitleRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true); // 오른쪽 서 있기
	TitleRenderer->ChangeAnimation("Mapback");

	StartRenderer->CreateAnimation("Ready", "Text.png", 0, 10, 0.5f, false); // 오른쪽 서 있기
	StartRenderer->ChangeAnimation("Ready");
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
