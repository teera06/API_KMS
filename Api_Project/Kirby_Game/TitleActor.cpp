#include "TitleActor.h"

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
	
	// 애니메이션 생성 및 실행
	// 배경 애니메이션
	TitleRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true);
	TitleRenderer->ChangeAnimation("Mapback");

	// Ready 애니메이션
	StartRenderer->CreateAnimation("Ready", "Text.png", 0, 10, 0.5f, false);
	StartRenderer->ChangeAnimation("Ready");
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
