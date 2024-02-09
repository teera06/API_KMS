#include "AllStar.h"
#include "ModeEnum.h"

AAllStar::AAllStar()
{
}

AAllStar::~AAllStar()
{
}

void AAllStar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(Dir * Speed * _DeltaTime);
}

void AAllStar::BeginPlay()
{
	AActor::BeginPlay();
	AllStarRenderer = CreateImageRenderer(RenderOrder::Base);
	AllStarRenderer->SetImage("Fire.png");
	AllStarRenderer->SetTransform({ {0,0}, {100, 100} });
	AllStarRenderer->SetActive(true, 0.3f);
	//FireRenderer->CreateAnimation("Attack", "Player_Right.png", 26, 32, 0.1f, true); -> บา 
}
